#include "client_connection_req.h"

static MessageS* client_connection_req_info(MessageS* msg_in, ServerConnectionS* client) {
    /* need struct to show this now return uint16_t with 1 */
    uint16_t t = 1;
    MessageS* msg = messages_alloc(MSG_SIZE(sizeof(uint16_t)));
    messages_set_payload(msg, &t, sizeof(t));
    return msg;
}



static MessageS* (*fun[])(MessageS* msg, ServerConnectionS* client) = {
    client_connection_req_info,
};

MessageS* client_connection_req(MessageS* msg_in, ServerConnectionS* client) {
    MessageS* ret = fun[(size_t)msg_in->header.req_type](msg_in, client);
    return ret;
}
