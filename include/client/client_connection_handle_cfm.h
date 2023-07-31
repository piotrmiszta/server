#ifndef CLIENT_CONNECTION_CFM_H_
#define CLIENT_CONNECTION_CFM_H_
#include "messages.h"

MessageS* client_connection_handle_cfm(const MessageS* in, const ClientIdentityS* client_info);

#endif //CLIENT_CONNECTION_CFM_H_
