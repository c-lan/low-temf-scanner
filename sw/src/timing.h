#pragma once

#include <stdint.h>

typedef void (*handler_t)(void);

void timingInit(void);
void* timingAsyncDelay(uint32_t ms, handler_t callback);
void timingAsyncCancel(void *delay);
void timingSleep(uint32_t ms);
void timingPollCallbacks(void);
