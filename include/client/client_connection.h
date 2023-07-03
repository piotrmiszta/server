#ifndef CLIENT_CONNECTION_H_
#define CLIENT_CONNECTION_H_
#include "messages.h"

int client_connection_start_thread(void* arg);
MessageS* client_connection_req(MessageS* in);
MessageS* client_connection_cfm(MessageS* in);
MessageS* client_connection_rej(MessageS* in);


#endif //CLIENT_CONNECTION_H_