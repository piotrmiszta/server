#ifndef MESSAGES_REQ_TYPES_H_
#define MESSAGES_REQ_TYPES_H_
#include <stdint.h>

/**
 *  @struct ReqAuthPayloadS 
*/
typedef struct{
    char login[20]; /**< sha1 login hash always 20 bits size */
    char pass[20];  /**< sha1 pass hash */
}ReqAuthPayloadS;

/** 
 * @struct ReqFilePayloadS 
 * @brief Structure is used as payload to MESSAGE_REQUEST_TYPE_FILE_INFO request type
*/
typedef struct{
    uint16_t filename_size;     /**< size of filename */
    char filename[];            /**< flexible array with filename */
}ReqFilePayloadS;



#endif //MESSAGES_REQ_TYPES_H_
