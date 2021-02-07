#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>

#include "timing.h"

typedef struct
{
    uint64_t targetTick;
    handler_t handler;
} async_t;

#define MAX_ASYNC_COUNT 8
static async_t g_async[MAX_ASYNC_COUNT];
static volatile uint64_t g_tickCount;

void sys_tick_handler(void)
{
    g_tickCount++;
}

void timingSleep(uint32_t ms)
{
    uint64_t target = g_tickCount + ms * 8;

    while(g_tickCount < target)
    {
        continue;
    }
}

void timingInit(void)
{
    systick_clear();
    systick_set_frequency(8000, rcc_ahb_frequency);
    systick_counter_enable();
    systick_interrupt_enable();
}

void* timingAsyncDelay(uint32_t ms, handler_t callback)
{
    for(int i = 0; i < MAX_ASYNC_COUNT; i++)
    {
        if(g_async[i].targetTick)
            continue;

        g_async[i].targetTick = g_tickCount + ms * 8;
        g_async[i].handler = callback;

        return &g_async[i];
    }

    return 0;
}

void timingAsyncCancel(void *delay)
{
    if(!delay)
        return;

    async_t *async = (async_t*)delay;
    async->handler = 0;
}

void timingPollCallbacks(void)
{
    for(int i = 0; i < MAX_ASYNC_COUNT; i++)
    {
        if(!g_async[i].handler)
            continue;

        if(g_tickCount >= g_async[i].targetTick)
        {
            g_async[i].handler();
            g_async[i].handler = 0;
        }
    }
}
