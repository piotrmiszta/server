#ifndef SERVER_DEFS_H_
#define SERVER_DEFS_H_
#include <netinet/in.h>

typedef struct ServerS {
    struct sockaddr_in address;
    int sock;
}ServerS;

typedef struct ServerConnectionS{
    int sock;
    struct sockaddr address;
    socklen_t addr_len;
}ServerConnectionS;

#endif //SERVER_DEFS_H_
