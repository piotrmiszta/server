#ifndef SERVER_DEFS_H_
#define SERVER_DEFS_H_
#include <netinet/in.h>
#include <threads.h>
#include <stdbool.h>
/**
 * @file server_defs.h
 * @brief file contains struct declaration used in server connection
 *
*/

/**
 * @struct ServerS
 * @brief   is used to store server socket information
 *
 * @param address   struct sockaddr_in for connection information
 * @param sock      integer that store sock descriptor
*/
typedef struct ServerS {
    struct sockaddr_in address; /** @var */
    int sock;
}ServerS;

/**
 * @struct ServerConnectionS
 * @brief   used to store information and useful variables for each client connected
 *
 * @param sock          integer that store socket desctriptor for client
 * @param address       struct sockaddr that store information about client address
 * @param addr_len      socklen_t store infromation about length of address
 * @param thread        thrd_t store thread descriptor for client thread
 * @param mutex         mtx_t store mutex for sending msg to client,
 *                      only one thread at one time can send information to client
 * @param thread_run    bool used to end client thread
*/
typedef struct ServerConnectionS{
    int sock;
    struct sockaddr address;
    socklen_t addr_len;
    thrd_t thread;
    mtx_t mutex;
    bool thread_run;
}ServerConnectionS;

#endif //SERVER_DEFS_H_
