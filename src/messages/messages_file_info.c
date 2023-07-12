#include "messages_file_info.h"
#include "server_defs.h"

static MessageS* messages_handle_file_info_req_file_desc(const ReqFileInfoPayloadS* payload, const ClientIdentityS* client_info);

MessageS* messages_handle_file_info_req(const MessageS* msg_in) {
    /* recv payload */
    MessageS* msg_out = NULL;
    ReqFileInfoPayloadS payload;
    messages_get_payload(msg_in, &payload);
    switch (payload.opt) {
    case :
        /* code */
        break;
    
    default:
        break;
    }
    return msg_out;
}

static MessageS* messages_handle_file_info_req_file_desc(const ReqFileInfoPayloadS* payload, const ClientIdentityS* client_info) {
    /*TODO: need to check syscalls to show info about file*/
    return NULL;
}
