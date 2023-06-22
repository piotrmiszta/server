#include "client_connection.h"
#include "server_defs.h"
#include "messages.h"
#include "error_codes.h"
#include <utility.h>
#include <threads.h>
#include <unistd.h>

static MessageS* client_connection_parse_msg(MessageS* msg_in);
static MessageS* client_connection_parse_req(MessageS* msg_out);
static MessageS* client_connection_parse_cfm(MessageS* msg_out);
static MessageS* client_connection_parse_rej(MessageS* msg_out);

int client_connection_start_thread(void* arg) {
    ServerConnectionS* client = arg;
    while(client->thread_run) {
        LOG_DEBUG("Client thread iteration");
        MessageS* msg_in = messages_read(client->sock);
        if(!msg_in) {
            LOG_ERROR("Msg is null pointer");
            client->thread_run = false;
            break;
        }
        MessageS* msg_out = client_connection_parse_msg(msg_in);
        if(msg_out) {
            messages_write(client->sock, msg_out);
        }
        messages_free(msg_in);
        messages_free(msg_out);
        sleep(1);
    }
    return 0;
}

MessageS* client_connection_parse_msg(MessageS* msg_in) {
    MessageS* msg_out;
    switch(msg_in->header.msg_type) {
        case MESSAGE_TYPE_REQ:
            LOG_TRACE("Get msg req");
            msg_out = client_connection_parse_req(msg_in);
            break;
        case MESSAGE_TYPE_CFM:
            LOG_TRACE("Get msg cfm");
            msg_out = client_connection_parse_cfm(msg_in);
            break;
        case MESSAGE_TYPE_REJ:
            LOG_TRACE("Get msg rej");
            msg_out = client_connection_parse_rej(msg_in);
            break;
    }
    return msg_out;
}

MessageS* client_connection_parse_req(MessageS* msg_in) {
    MessageS* msg_out = messages_alloc(MSG_SIZE(sizeof(uint16_t)));
    uint16_t test = 100;
    messages_set_payload(msg_out, &test, sizeof(test));
    return msg_out;
}

MessageS* client_connection_parse_cfm(MessageS* msg_in) {
    return NULL;
}

MessageS* client_connection_parse_rej(MessageS* msg_in) {
    return NULL;
}
