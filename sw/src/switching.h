#pragma once

#define SWITCHING_NUM_CHANNELS 16

void switchingInit(void);

void switchingSwitchChannel(int channelId);
void switchingOpenCurrent(void);
void switchingGetClosedChannel(int *isAnyClosed, int *channelId);

void switchingSetMakeBeforeBreak(int enabled);
int switchingGetMakeBeforeBreak(void);

void switchingSet4Wire(int enabled);
int switchingGet4Wire(void);
