#include "messages_file_info.h"
#include "server_defs.h"

static MessageS* messages_handle_file_info_req_file_desc(const ReqFileInfoPayloadS* payload, const ClientIdentityS* client_info);
static MessageS* messages_handle_file_info_req_list_files(const ReqFileInfoPayloadS* payload, const ClientIdentityS* client_info);
static MessageS* messages_handle_error(uint8_t opt, const ClientIdentityS* client_info);

MessageS* messages_handle_file_info_req(const MessageS* msg_in, const ClientIdentityS* client_info) {
    /* recv payload */
    MessageS* msg_out = NULL;
    ReqFileInfoPayloadS payload;
    messages_get_payload(msg_in, &payload);
    switch (payload.opt) {
        case REQ_FILE_INFO_FILE_DESC:
            msg_out = messages_handle_file_info_req_file_desc(&payload, client_info);
            break;
        case REQ_FILE_INFO_LIST_FILES:
            msg_out = messages_handle_file_info_req_list_files(&payload, client_info);
            break;
        default:
            /* need to handling error */
            messages_handle_error(payload.opt, client_info);
            break;
    }
    return msg_out;
}

static MessageS* messages_handle_file_info_req_file_desc(const ReqFileInfoPayloadS* payload, const ClientIdentityS* client_info) {
    /*TODO: need to check syscalls to show info about file*/
    return NULL;
}

static MessageS* messages_handle_file_info_req_list_files(const ReqFileInfoPayloadS* payload, const ClientIdentityS* client_info) {
    /* TODO: get list of availble files and send it */
    /* NOTE: temporary solution */
    return NULL;
}

static MessageS* messages_handle_error(uint8_t opt, const ClientIdentityS* client_info) {
    /* TODO:  I think is good when client try to send wrong opt in payload dc him */
    RejFileInfoPayloadS payload;
    payload.opt = opt;
    payload.reason = REJ_FILE_INFO_INVALID_OPTION;
    MessageS* message = messages_alloc(MSG_SIZE(sizeof(payload)));
    messages_set_payload(message, &payload, sizeof(payload));
    return  message;
}
