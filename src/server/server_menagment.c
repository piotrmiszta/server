#include "server_menagment.h"
#include "server_defs.h"
#include "error_codes.h"
#include "client_connection.h"
#include "util_list.h"

#include <utility.h>
#include <unistd.h> //for sleep remove
#include <stdlib.h>

/* static global variables */
static bool server_menagment_run = true;
static ListS* client_list = NULL;
/* Static function declaration */
static inline int server_menagment_thread_comp(void* client_struct, void* thread_id);
static inline void server_menagment_thread_free(void* arg);
static inline int server_menagment_close_all_client(void);

int server_menagment_start_thread(void* arg) {
    LOG_INFO("Thread: server menagment started");
    client_list = util_list_create(server_menagment_thread_free, server_menagment_thread_comp);
    ServerS* server = arg;
    (void) server;
    while(server_menagment_run) {
        /* sleep, after it check connection, if can't send msg, end thread */
        sleep(1); //TODO: change to thrd_sleep()
        LOG_DEBUG("Server menagment thread");
    }
    LOG_INFO("Closing server menagment thread");
    /* need to join all client threads */
    server_menagment_close_all_client();
    LOG_INFO("Successful ending all clients threads");
    return 0;
}

void server_menagment_end_thread(void) {
    server_menagment_run = 0;
}

int server_menagment_add_client(ServerConnectionS* client) {
    assert_ss(client_list);
    assert_ss(client);
    client->thread_run = true;
    assert_ss(mtx_init(&client->mutex, mtx_plain) == 0);
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

static inline int server_menagment_close_all_client(void) {
    /* check number of clients */
    size_t nr_clients = util_list_get_size(client_list);
    /* iterate for all clients */
    for(size_t i = 0; i < nr_clients; i++) {
        ServerConnectionS* client = util_list_pop_back(client_list);
        /* lock mutex to be sure that nothing will be send to this client */
        int client_status;
        client->thread_run = false;
        mtx_lock(&client->mutex);
        thrd_join(client->thread, &client_status);
        mtx_unlock(&client->mutex);
        /* destroy this function */
        server_menagment_thread_free(client);
    }
    util_list_destroy(client_list);
    return SUCCESS;
}

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

static inline void server_menagment_thread_free(void* arg) {
    ServerConnectionS* client = arg;
    mtx_destroy(&client->mutex);
    free(client);
}