#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>

#include "bsp.h"
#include "switching.h"
#include "timing.h"

#define EXPANDER_REG_OUTPUT0 0x2
#define EXPANDER_REG_OUTPUT1 0x3
#define EXPANDER_REG_CONFIG0 0x6
#define EXPANDER_REG_CONFIG1 0x7

#define EXPANDER_ADDRESS(chip) (0x20 | chip)

#define SWITCHING_TIME 4
#define DEBOUNCE_TIME 3

typedef struct
{
    uint8_t chip;
    uint8_t port;
    uint8_t pin;
    uint8_t comPin;
    uint8_t pcbIndex;
    uint8_t index;
} channel_gpio_t;

static channel_gpio_t g_channels[16] = {
    { .chip = 0x4, .port = 0, .pin = 1 << 0, .comPin = 1 << 4, .pcbIndex = 9,  .index = 0},
    { .chip = 0x4, .port = 0, .pin = 1 << 1, .comPin = 1 << 4, .pcbIndex = 10, .index = 1},
    { .chip = 0x4, .port = 0, .pin = 1 << 2, .comPin = 1 << 4, .pcbIndex = 11, .index = 2},
    { .chip = 0x4, .port = 0, .pin = 1 << 3, .comPin = 1 << 4, .pcbIndex = 12, .index = 3},

    { .chip = 0x4, .port = 1, .pin = 1 << 4, .comPin = 1 << 3, .pcbIndex = 13, .index = 4},
    { .chip = 0x4, .port = 1, .pin = 1 << 5, .comPin = 1 << 3, .pcbIndex = 14, .index = 5},
    { .chip = 0x4, .port = 1, .pin = 1 << 6, .comPin = 1 << 3, .pcbIndex = 15, .index = 6},
    { .chip = 0x4, .port = 1, .pin = 1 << 7, .comPin = 1 << 3, .pcbIndex = 16, .index = 7},

    { .chip = 0x0, .port = 0, .pin = 1 << 0, .comPin = 1 << 4, .pcbIndex = 5, .index = 8},
    { .chip = 0x0, .port = 0, .pin = 1 << 1, .comPin = 1 << 4, .pcbIndex = 6, .index = 9},
    { .chip = 0x0, .port = 0, .pin = 1 << 2, .comPin = 1 << 4, .pcbIndex = 7, .index = 10},
    { .chip = 0x0, .port = 0, .pin = 1 << 3, .comPin = 1 << 4, .pcbIndex = 8, .index = 11},

    { .chip = 0x0, .port = 1, .pin = 1 << 4, .comPin = 1 << 3, .pcbIndex = 1, .index = 12},
    { .chip = 0x0, .port = 1, .pin = 1 << 5, .comPin = 1 << 3, .pcbIndex = 2, .index = 13},
    { .chip = 0x0, .port = 1, .pin = 1 << 6, .comPin = 1 << 3, .pcbIndex = 3, .index = 14},
    { .chip = 0x0, .port = 1, .pin = 1 << 7, .comPin = 1 << 3, .pcbIndex = 4, .index = 15}
};

static channel_gpio_t g_combineSwitch = {
    .chip = 0x4, .port = 1, .pin = 2, .comPin = 1, .pcbIndex = 0, .index = 0
};

static uint8_t g_fwireEnabled = 0;
static uint8_t g_mbbEnabled = 0;
static channel_gpio_t *g_closedChannel = 0;

static void switchingGpioSetMode(int subaddress, int port, uint8_t inputPins)
{
    uint8_t reg = port ? EXPANDER_REG_CONFIG1 : EXPANDER_REG_CONFIG0;
    uint8_t address = EXPANDER_ADDRESS(subaddress);

    uint8_t writeBuf[2] = { reg, inputPins };
    i2c_transfer7(I2C1, address, writeBuf, sizeof(writeBuf), 0, 0);
}

static void switchingGpioSetOutput(int subaddress, int port, uint8_t pins)
{
    uint8_t reg = port ? EXPANDER_REG_OUTPUT1 : EXPANDER_REG_OUTPUT0;
    uint8_t address = EXPANDER_ADDRESS(subaddress);

    uint8_t writeBuf[2] = { reg, pins };
    i2c_transfer7(I2C1, address, writeBuf, sizeof(writeBuf), 0, 0);
}

static void switchingCloseRelay(channel_gpio_t *channel)
{
    switchingGpioSetOutput(channel->chip, channel->port, channel->pin);
    timingSleep(SWITCHING_TIME);
    switchingGpioSetOutput(channel->chip, channel->port, 0);
}

static void switchingOpenRelay(channel_gpio_t *channel)
{
    switchingGpioSetOutput(channel->chip, channel->port, 0xFF & ~channel->pin);
    timingSleep(SWITCHING_TIME);
    switchingGpioSetOutput(channel->chip, channel->port, 0);
}

void switchingInit()
{
    rcc_periph_clock_enable(RCC_I2C1);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, GPIO8 | GPIO9);

    i2c_reset(I2C1);
    i2c_peripheral_disable(I2C1);
    i2c_set_speed(I2C1, i2c_speed_sm_100k, rcc_apb1_frequency / (1000 * 1000));
    i2c_peripheral_enable(I2C1);

    // Ensure GPIOs are set to out and logic low cleanly
    for(int port = 0; port < 2; port++)
    {
        switchingGpioSetOutput(0x00, port, 0x00);
        switchingGpioSetOutput(0x04, port, 0x00);
        switchingGpioSetMode(0x00, port, 0x00);
        switchingGpioSetMode(0x04, port, 0x00);
    }

    // Reset relay state
    switchingOpenRelay(&g_combineSwitch);
    timingSleep(DEBOUNCE_TIME);

    for(int i = 0; i < SWITCHING_NUM_CHANNELS; i++)
        switchingOpenRelay(&g_channels[i]);

    g_closedChannel = 0;
    g_fwireEnabled = 0;
}

void switchingSwitchChannel(int channelId)
{
    if(channelId >= SWITCHING_NUM_CHANNELS)
        return;

    if(g_fwireEnabled && channelId >= SWITCHING_NUM_CHANNELS / 2)
        channelId = channelId / 2;

    if(g_closedChannel && g_closedChannel->index == channelId)
        return;

    if(!g_mbbEnabled)
    {
        switchingOpenCurrent();
        timingSleep(DEBOUNCE_TIME);
    }

    if(g_fwireEnabled)
        switchingCloseRelay(&g_channels[channelId + 8]);

    switchingCloseRelay(&g_channels[channelId]);

    if(g_mbbEnabled)
    {
        timingSleep(DEBOUNCE_TIME);
        switchingOpenCurrent();
    }

    g_closedChannel = &g_channels[channelId];
}

void switchingOpenCurrent(void)
{
    if(!g_closedChannel)
        return;

    switchingOpenRelay(g_closedChannel);

    if(g_fwireEnabled)
        switchingOpenRelay(&g_channels[g_closedChannel->index + 8]);

    g_closedChannel = 0;
}

void switchingGetClosedChannel(int *isAnyClosed, int *channelId)
{
    *isAnyClosed = g_closedChannel != 0;

    if(g_closedChannel)
        *channelId = g_closedChannel->index;
}

void switchingSetMakeBeforeBreak(int enabled)
{
    g_mbbEnabled = enabled;
}

int switchingGetMakeBeforeBreak(void)
{
    return g_mbbEnabled;
}

void switchingSet4Wire(int enabled)
{
    if(enabled == g_fwireEnabled)
        return;

    switchingOpenCurrent();
    timingSleep(DEBOUNCE_TIME);

    g_fwireEnabled = enabled;

    if(enabled)
        switchingCloseRelay(&g_combineSwitch);
    else
        switchingOpenRelay(&g_combineSwitch);
}

int switchingGet4Wire(void)
{
    return g_fwireEnabled != 0;
}
