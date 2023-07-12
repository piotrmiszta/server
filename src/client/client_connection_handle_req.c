#include "client_connection_handle_req.h"
#include "messages_file_info.h"
#include <stdlib.h>
MessageS* client_connection_handle_req(const MessageS* in) {
    assert_ss(in);
    request_type_t req_type = in->header.req_type;
    MessageS* msg_out = NULL;
    switch(req_type) {
        case MESSAGE_REQUEST_TYPE_AUTH:
            LOG_TRACE("Authentication request");
            break;
        case MESSAGE_REQUEST_TYPE_FILE_INFO:
            LOG_TRACE("File info request");
            msg_out = messages_handle_file_info_req(in);
            break;
        case MESSAGE_REQUEST_TYPE_FILE:
            LOG_TRACE("File request");
            break;
        default:
            LOG_FATAL("Invalid request id, aborted()");
            abort();    
        }
    return msg_out;
}
