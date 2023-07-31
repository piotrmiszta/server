#include "client_connection.h"
#include "client_connection_handle_cfm.h"
#include "client_connection_handle_rej.h"
#include "client_connection_handle_req.h"
#include "server_defs.h"
#include "messages.h"
#include "error_codes.h"
#include <utility.h>
#include <threads.h>
#include <unistd.h>

static MessageS* client_connection_parse_msg(const MessageS* msg_in, const ClientIdentityS* client_info);

int client_connection_start_thread(void* arg) {
    ServerConnectionS* client = arg;
    ClientIdentityS* client_info = &client->identity;
    int loc_errno; //local errno for checking msg errors, to know when timeout was reached or when client disconnect
    while(client->thread_run) {
        MessageS* msg_in = messages_read(client->sock, &loc_errno);
        if(!msg_in) {
            if(loc_errno == EREAD) {
                LOG_ERROR("Msg is null pointer");
                client->thread_run = false;
                break;
            }
            else {
                //reached timeout
                continue;
            }
        }
        MessageS* msg_out = client_connection_parse_msg(msg_in, client_info);
        if(msg_out) {
            messages_write(client->sock, msg_out);
            messages_free(msg_out);
        }
        messages_free(msg_in);
    }
    return 0;
}

MessageS* client_connection_parse_msg(const MessageS* msg_in, const ClientIdentityS* client_info) {
    MessageS* msg_out = NULL;
    switch(msg_in->header.msg_type) {
        case MESSAGE_TYPE_REQ:
            LOG_TRACE("Recaived message, type: req");
            msg_out = client_connection_handle_req(msg_in, client_info);
            break;
        case MESSAGE_TYPE_CFM:
            LOG_TRACE("Recaived message, type: cfm");
            msg_out = client_connection_handle_cfm(msg_in, client_info);
            break;
        case MESSAGE_TYPE_REJ:
            LOG_TRACE("Recaived message, type: rej");
            msg_out = client_connection_handle_rej(msg_in, client_info);
            break;
    }
    return msg_out;
}
