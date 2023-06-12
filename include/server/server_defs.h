#ifndef SERVER_DEFS_H_
#define SERVER_DEFS_H_
#include <netinet/in.h>
#include <threads.h>
#include <stdbool.h>

typedef struct ServerS {
    struct sockaddr_in address;
    int sock;
}ServerS;

typedef struct ServerConnectionS{
    int sock;
    struct sockaddr address;
    socklen_t addr_len;
    thrd_t thread;
    bool thread_run;
}ServerConnectionS;

#endif //SERVER_DEFS_H_
