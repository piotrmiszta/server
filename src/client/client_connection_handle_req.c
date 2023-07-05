#include "client_connection_handle_req.h"
#include <stdlib.h>
MessageS* client_connection_handle_req(MessageS* in) {
    assert_ss(in);
    assert_ss(in->payload);
    request_type_t req_type = in->header.req_type;
    switch(req_type) {
        case MESSAGE_REQUEST_TYPE_AUTH:
            LOG_TRACE("Authentication request");
            break;
        case MESSAGE_REQUEST_TYPE_FILE_INFO:
            LOG_TRACE("File info request");
            break;
        case MESSAGE_REQUEST_TYPE_FILE:
            LOG_TRACE("File request");
            break;
        default:
            LOG_FATAL("Invalid request id, aborted()");
            abort();    
        }
    return NULL;
}
