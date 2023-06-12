#include "client_connection.h"
#include "server_defs.h"
#include <utility.h>
#include <threads.h>
#include <unistd.h>

int client_connection_start_thread(void* arg) {
    ServerConnectionS* client = arg;
    while(client->thread_run) {
        LOG_DEBUG("Client thread");
        sleep(1);
    }
    return 0;
}