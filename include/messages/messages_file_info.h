#ifndef MESSAGES_FILE_INFO_H_
#define MESSAGES_FILE_INFO_H_
#include <stdint.h>
#include "server_defs.h"
#include "messages.h"
enum {
    REQ_FILE_INFO_FILE_DESC = 0, 
    REQ_FILE_INFO_LIST_FILES = 1,
};

enum {
    REJ_FILE_INFO_NOT_PERMISSION = 0,
    REJ_FILE_INFO_NOT_FILE = 1,
    REJ_FILE_INFO_INVALID_PATH = 2,
    REJ_FILE_INFO_INVALID_OPTION = 3,
};

typedef struct{
    uint8_t opt;
    uint32_t path_size;
    char path[];
}ReqFileInfoPayloadS;

typedef struct{
    uint64_t size;          /**< size of file */
    char fileName[50];      /**< file name */
    char owner[50];         /**< owner's login */
    char modified[50];      /**< last modified */
    char path[250];         /**< path to file */
}CfmFileInfoFileDescPayloadS;   // size = 404

typedef struct{
    uint16_t size;
    char files[];
}CfmFileInfoFileListPayloadS;

typedef struct{
    uint8_t opt;
    uint16_t reason;
}RejFileInfoPayloadS;

/**
 * @brief   messages_handle_file_info_req handling file info request
 *          checking permission, file owner's, and file exisit, and created msg_out
 *          based on this information and request option
 * @param   msg_in pointer to MessageS* with payload recaived request message
 * @return  pointer to MessageS to response for request, cfm or rej
*/
MessageS* messages_handle_file_info_req(const MessageS* msg_in, const ClientIdentityS* client_info);

/**
 * @brief handle response for request if it was cfm,
 *          payload is based on option
 * @param msg_in pointer to MessageS with confirmation
 * @param opt option send in request.
 * @return //TODO: will we send next message ?
*/
MessageS* messages_handle_file_info_cfm(const MessageS* msg_in, uint8_t opt);

/**
 * @brief handling rej
 * @param payload pointer to RejFileInfoPayloadS contain info about rejection
*/
MessageS* messages_handle_file_info_rej(const MessageS* msg_in);
#endif //MESSAGES_FILE_INFO_H_
