#include "client_connection.h"
#include <utility.h>
#include <threads.h>
#include <unistd.h>

int client_connection_start_thread(void* arg) {
    while(1) {
        LOG_DEBUG("Client thread");
        sleep(1);
    }
    return 0;
}