#pragma once

typedef void (*serial_reset_handler_t)(void);
typedef void (*serial_read_handler_t)(char* data, int length);

void serialInit(serial_reset_handler_t resetHandler, serial_read_handler_t readHandler);
void serialPoll(void);
void serialWrite(char *data, int length);
