#ifndef SERVER_BOOT_H_
#define SERVER_BOOT_H_

#include "error_codes.h"
#include "server_defs.h"

int server_boot(ServerS* server_params);
int server_close(ServerS* server_params);

#endif // SERVER_BOOT_H_
