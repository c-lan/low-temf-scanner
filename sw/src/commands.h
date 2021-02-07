#pragma once

typedef void (*cmd_write_handler_t)(char* data, int length);

void cmdInit(cmd_write_handler_t);
void cmdResetHandler(void);
void cmdReadHandler(char *data, int length);
