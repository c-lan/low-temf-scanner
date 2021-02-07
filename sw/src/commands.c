#include <scpi/scpi.h>
#include "commands.h"
#include "serial.h"
#include "switching.h"
#include "utils.h"

int scpiError(scpi_t *context, int_fast16_t err);
size_t scpiWrite(scpi_t * context, const char * data, size_t len);
scpi_result_t scpiControl(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t scpiFlush(scpi_t *context);
scpi_result_t scpiReset(scpi_t *context);

static scpi_result_t cmdHandleRouteClose(scpi_t *context);
static scpi_result_t cmdHandleRouteOpenAll(scpi_t *context);
static scpi_result_t cmdHandleRouteCloseStateQ(scpi_t *context);
static scpi_result_t cmdHandleRouteConnectionSequence(scpi_t *context);
static scpi_result_t cmdHandleRouteConnectionSequenceQ(scpi_t *context);
static scpi_result_t cmdHandleRouteChannelFwire(scpi_t *context);
static scpi_result_t cmdHandleRouteChannelFwireQ(scpi_t *context);

static cmd_write_handler_t g_writeHandler = 0;

static const scpi_command_t scpiCommands[] = {
    // Required by SCPI spec
    {.pattern = "*CLS", .callback = SCPI_CoreCls,},
    {.pattern = "*ESE", .callback = SCPI_CoreEse,},
    {.pattern = "*ESE?", .callback = SCPI_CoreEseQ,},
    {.pattern = "*ESR?", .callback = SCPI_CoreEsrQ,},
    {.pattern = "*IDN?", .callback = SCPI_CoreIdnQ,},
    {.pattern = "*OPC", .callback = SCPI_CoreOpc,},
    {.pattern = "*OPC?", .callback = SCPI_CoreOpcQ,},
    {.pattern = "*RST", .callback = SCPI_CoreRst,},
    {.pattern = "*SRE", .callback = SCPI_CoreSre,},
    {.pattern = "*SRE?", .callback = SCPI_CoreSreQ,},
    {.pattern = "*STB?", .callback = SCPI_CoreStbQ,},
    {.pattern = "*TST?", .callback = SCPI_CoreTstQ,},
    {.pattern = "*WAI", .callback = SCPI_CoreWai,},
    {.pattern = "SYSTem:ERRor[:NEXT]?", .callback = SCPI_SystemErrorNextQ,},
    {.pattern = "SYSTem:ERRor:COUNt?", .callback = SCPI_SystemErrorCountQ,},
    {.pattern = "SYSTem:VERSion?", .callback = SCPI_SystemVersionQ,},
    {.pattern = "STATus:QUEStionable[:EVENt]?", .callback = SCPI_StatusQuestionableEventQ,},
    {.pattern = "STATus:QUEStionable:ENABle", .callback = SCPI_StatusQuestionableEnable,},
    {.pattern = "STATus:QUEStionable:ENABle?", .callback = SCPI_StatusQuestionableEnableQ,},
    {.pattern = "STATus:PRESet", .callback = SCPI_StatusPreset,},

    // {.pattern = "INITiate", .callback = cmdHandleInit,},
    // {.pattern = "ABORt", .callback = cmdHandleAbort,},

    // {.pattern = "ROUTe:SCAN", .callback = cmdHandleScan,},
    // {.pattern = "ROUTe:SCAN?", .callback = cmdHandleScanQ,},
    {.pattern = "ROUTe:CLOSe", .callback = cmdHandleRouteClose,},
    {.pattern = "ROUTe:CLOSe:STATe?", .callback = cmdHandleRouteCloseStateQ,},
    {.pattern = "ROUTe:OPEN:ALL", .callback = cmdHandleRouteOpenAll,},

    {.pattern = "ROUTe:CONNection:SEQuence", .callback = cmdHandleRouteConnectionSequence,},
    {.pattern = "ROUTe:CONNection:SEQuence?", .callback = cmdHandleRouteConnectionSequenceQ,},

    {.pattern = "ROUTe:CHANnel:FWIRe", .callback = cmdHandleRouteChannelFwire,},
    {.pattern = "ROUTe:CHANnel:FWIRe?", .callback = cmdHandleRouteChannelFwireQ,},
    // {.pattern = "ROUTe:CHANnel:DELay", .callback = cmdHandleRouteChannelDelay,},
    // {.pattern = "ROUTe:CHANnel:DELay?", .callback = cmdHandleRouteChannelDelayQ,},
    // {.pattern = "ROUTe:CHANnel:ADVance:SOURce", .callback = cmdHandleRouteChannelAdvanceSource,},
    // {.pattern = "ROUTe:CHANnel:ADVance:SOURce?", .callback = cmdHandleRouteChannelAdvanceSourceQ,},
    // {.pattern = "ROUTe:CHANnel:DELay", .callback = cmdHandleRouteChannelDelay,},
    // {.pattern = "ROUTe:CHANnel:DELay?", .callback = cmdHandleRouteChannelDelayQ,},

    // {.pattern = "TRIGger:SOURce", .callback = cmdHandleTriggerSource,},
    // {.pattern = "TRIGger:SOURce?", .callback = cmdHandleTriggerSourceQ,},
    // {.pattern = "TRIGger:TIMer", .callback = cmdHandleTriggerTimer,},
    // {.pattern = "TRIGger:TIMer?", .callback = cmdHandleTriggerTimerQ,},
    // {.pattern = "TRIGger:COUNt", .callback = cmdHandleTriggerCount,},
    // {.pattern = "TRIGger:COUNt?", .callback = cmdHandleTriggerCountQ,},

    // {.pattern = "OUTPut:TRIGger:SOURce", .callback = cmdHandleOutputTriggerSource,},
    // {.pattern = "OUTPut:TRIGger:SOURce?", .callback = cmdHandleOutputTriggerSourceQ,},
    // {.pattern = "OUTPut:TRIGger:STATe", .callback = cmdHandleOutputTriggerState,},
    // {.pattern = "OUTPut:TRIGger:STATe?", .callback = cmdHandleOutputTriggerStateQ,},

    SCPI_CMD_LIST_END
};

int scpiError(scpi_t *context, int_fast16_t err)
{
    (void)context;
    (void)err;

    return 0;
}

size_t scpiWrite(scpi_t * context, const char * data, size_t len)
{
    (void)context;

    g_writeHandler((char*)data, len);

    return len;
}

scpi_result_t scpiControl(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val)
{
    (void)context;
    (void)ctrl;
    (void)val;

    return SCPI_RES_OK;
}

scpi_result_t scpiFlush(scpi_t *context)
{
    (void)context;

    return SCPI_RES_OK;
}

scpi_result_t scpiReset(scpi_t *context)
{
    (void)context;

    return SCPI_RES_OK;
}

#define SCPI_INPUT_BUFFER_LENGTH 256
#define SCPI_ERROR_QUEUE_SIZE 16

static char g_scpiInputBuffer[SCPI_INPUT_BUFFER_LENGTH];
static scpi_error_t g_scpiErrorQueue[SCPI_ERROR_QUEUE_SIZE];
static scpi_t g_scpiContext;

static scpi_interface_t g_scpiInterface = {
    .error = scpiError,
    .write = scpiWrite,
    .control = scpiControl,
    .flush = scpiFlush,
    .reset = scpiReset,
};

void cmdInit(cmd_write_handler_t writeHandler)
{
    g_writeHandler = writeHandler;

    SCPI_Init(
        &g_scpiContext,
        scpiCommands,
        &g_scpiInterface,
        scpi_units_def,
        utilsGetBrand(),
        utilsGetModel(),
        utilsGetSerial(),
        utilsGetVersion(),
        g_scpiInputBuffer,
        SCPI_INPUT_BUFFER_LENGTH,
        g_scpiErrorQueue,
        SCPI_ERROR_QUEUE_SIZE
    );
}

void cmdResetHandler(void)
{
    SCPI_Input(&g_scpiContext, 0, 0);
}

void cmdReadHandler(char *data, int length)
{
    SCPI_Input(&g_scpiContext, data, length);
}

static scpi_result_t cmdHandleRouteClose(scpi_t *context)
{
    uint32_t channel = 0;

    if(!SCPI_ParamUInt32(context, &channel, TRUE))
        return SCPI_RES_ERR;

    if(channel < 1 || channel > SWITCHING_NUM_CHANNELS)
    {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }

    switchingSwitchChannel(channel - 1);
    return SCPI_RES_OK;
}

static scpi_result_t cmdHandleRouteCloseStateQ(scpi_t *context)
{
    int anyClosed = 0;
    int channel = 0;

    switchingGetClosedChannel(&anyClosed, &channel);

    if(!anyClosed)
        SCPI_ResultText(context, "");
    else
        SCPI_ResultUInt8(context, channel + 1);

    return SCPI_RES_OK;
}

static scpi_result_t cmdHandleRouteOpenAll(scpi_t *context)
{
    (void)context;
    switchingOpenCurrent();
    return SCPI_RES_OK;
}

static scpi_result_t cmdHandleRouteConnectionSequence(scpi_t *context)
{
    static scpi_choice_def_t choices[] = {
        {"DEF", 0},
        {"BBM", 0},
        {"MBB", 1},
        SCPI_CHOICE_LIST_END
    };

    int32_t enableMBB = 0;

    if(!SCPI_ParamChoice(context, choices, &enableMBB, TRUE))
        return SCPI_RES_ERR;

    switchingSetMakeBeforeBreak(enableMBB);

    return SCPI_RES_OK;
}

static scpi_result_t cmdHandleRouteConnectionSequenceQ(scpi_t *context)
{
    if(switchingGetMakeBeforeBreak())
        SCPI_ResultText(context, "MBB");
    else
        SCPI_ResultText(context, "BBM");

    return SCPI_RES_OK;
}

static scpi_result_t cmdHandleRouteChannelFwire(scpi_t *context)
{
    scpi_bool_t value = FALSE;

    if(!SCPI_ParamBool(context, &value, TRUE))
        return SCPI_RES_ERR;

    switchingSet4Wire(value);

    return SCPI_RES_OK;
}

static scpi_result_t cmdHandleRouteChannelFwireQ(scpi_t *context)
{
    SCPI_ResultBool(context, switchingGet4Wire());
    return SCPI_RES_OK;
}
