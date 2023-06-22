#ifndef MESSAGES_H_
#define MESSAGES_H_
#include <stdint.h>
#include "messages.h"
#include "error_codes.h"
#include <utility.h>
#include <unistd.h>
#include <sys/socket.h>

typedef uint16_t payload_size_t;
typedef uint16_t request_type_t;
typedef uint8_t message_type_t;

typedef struct MessageS {
    struct MessageHeaderS{
        payload_size_t size;        /** uint16_t */
        request_type_t req_type;    /** uint16_t */
        message_type_t msg_type;    /** uint8_t  */
        uint8_t __padded;           /** uint8_t  */
    } header;
    char payload[];
}MessageS;

typedef enum MessageTypeE{
    MESSAGE_TYPE_REQ = 0,
    MESSAGE_TYPE_CFM,
    MESSAGE_TYPE_REJ,
}MessageTypeE;

typedef enum MessageRequestTypeE{
    MESSAGE_REQUEST_TYPE_AUTH = 0,
}MessageRequestTypeE;

#define PAYLOAD_SIZE_MAX        (1000)
#define MSG_SIZE_MAX            (PAYLOAD_SIZE_MAX + sizeof(MessageS))
#define MSG_SIZE(a)             ((size_t)a + sizeof(MessageS))
MessageS* messages_alloc(uint16_t size);
void messages_free(MessageS* msg);
int messages_set_payload(MessageS* message, void* payload_in, payload_size_t size);
int messages_get_payload(MessageS* message, void* payload_out);

MessageS* messages_read(int sock);
ssize_t messages_write(int sock, MessageS* msg);
#endif // MESSAGES_H_
