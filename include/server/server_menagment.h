#ifndef SERVER_MENAGMENT_H_
#define SERVER_MENAGMENT_H_
#include "server_defs.h"
int server_menagment_start_thread(void* arg);

void server_menagment_end_thread(void);
int server_menagment_add_client(ServerConnectionS* client);

#endif //SERVER_MENAGMENT_H_
