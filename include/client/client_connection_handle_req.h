#ifndef CLIENT_CONNECTION_REQ_H_
#define CLIENT_CONNECTION_REQ_H_
#include "messages.h"
#include "server_defs.h"

MessageS* client_connection_handle_req(const MessageS* in, const ClientIdentityS* client_info);

#endif //CLIENT_CONNECTION_REQ_H_

