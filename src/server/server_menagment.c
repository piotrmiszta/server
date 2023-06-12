#include "server_menagment.h"
#include "server_defs.h"
#include "error_codes.h"
#include "client_connection.h"
#include "util_list.h"
#include <utility.h>
#include <unistd.h> //for sleep remove
#include <stdlib.h>

static bool server_menagment_run = true;
static ListS* client_list = NULL;

static inline int server_menagment_thread_comp(void* client_struct, void* thread_id) {
    thrd_t* _thread_id = thread_id;
    ServerConnectionS* _client_struct = client_struct;
    if( *_thread_id == _client_struct->thread) {
        return 0;
    }
    else {
        return -1;
    }
}

int server_menagment_start_thread(void* arg) {
    LOG_INFO("Thread: server menagment started");
    client_list = util_list_create(free, server_menagment_thread_comp);
    ServerS* server = arg;
    (void) server;
    while(server_menagment_run) {
        /* sleep, after it check connection, if can't send msg, end thread */
        sleep(1);
        LOG_DEBUG("Server menagment thread");
    }
    LOG_INFO("Closing server menagment thread");
    return 0;
}

void server_menagment_end_thread(void) {
    server_menagment_run = 0;
}

int server_menagment_add_client(ServerConnectionS* client) {
    assert_ss(client_list);
    assert_ss(client);
    client->thread_run = true;
    util_list_push_back(client_list, client);
    int res = thrd_create(&client->thread, client_connection_start_thread, client);
    if(res) {
        LOG_ERROR("Can't create new thread for client error: %d", res);
    }
    else {
        LOG_INFO("Successfull created new thread: %d, for client: sock = %d", client->thread, client->sock);
    }
    return SUCCESS;
}