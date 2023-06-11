#include "server_listen.h"
#include "server_defs.h"
#include <utility.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdbool.h>
#include "error_codes.h"
#include <stdlib.h>
#define SERVER_LISTEN_MAX  5   /** @def Max server listen */
static bool server_listen_run = 1;

static inline int server_listen_listen(ServerS* server_param);

int server_listen_start_thread(void* arg) {
    ServerS* server_param = arg;
    while(server_listen_run) {
        server_listen_listen(server_param);
    }
    return 0;
}

static inline int server_listen_listen(ServerS* server_param) {
    LOG_DEBUG("Server listen ...");
    int res = listen(server_param->sock, SERVER_LISTEN_MAX);
    if(res < 0 && (server_listen_run == true)) {
        LOG_ERROR("Error when listening error: %d", res);
        return ELIST;
    }
    else if (res < 0 && (server_listen_run == false)) {
        LOG_INFO("Closing server listen thread");
        return SUCCESS;
    }
    else {
        /* ACCEPT CONNECTION */
        /* alloc struct for info about new client */
        ServerConnectionS* client_info = calloc(1 , sizeof(ServerConnectionS));
        assert_ss(client_info);
        /* accept new client */
        client_info->sock = accept(server_param->sock,
            &client_info->address,
            &client_info->addr_len);
        /* check connection */
        if(client_info->sock <= 0) {
            if(server_listen_run) {
                LOG_ERROR("Can't accept new client, error: %d", client_info->sock);
                free(client_info);
                return EACCT;
            }
            else {

                LOG_INFO("Closing server listen thread");
                free(client_info);
                return SUCCESS;
            }
        }
        else {
            LOG_DEBUG("Connection accepted socket: %d", client_info->sock);
            free(client_info); // this is temporary solution for valgrind
            return SUCCESS;
        }
    }
}

void server_listen_end_thread(int sock) {
    // need to destroy socket so this function need to get sock
    server_listen_run = 0;
    shutdown(sock, 2);
}
