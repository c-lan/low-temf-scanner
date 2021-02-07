#include <libopencm3/stm32/desig.h>
#include "utils.h"

static char g_serial[16];

const char* utilsGetBrand(void)
{
    return "Takovsky";
}

const char* utilsGetModel(void)
{
    return "Low TEMF 8x4W scanner";
}

const char* utilsGetVersion(void)
{
    return "1.0";
}

const char* utilsGetSerial(void)
{
    if(g_serial[0] == 0)
        desig_get_unique_id_as_string(g_serial, sizeof(g_serial));

    return g_serial;
}
