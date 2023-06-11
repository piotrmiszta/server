#include "server_menagment.h"
#include "server_defs.h"
#include <utility.h>
#include <unistd.h>
#include <stdbool.h>

static bool server_menagment_run = 1;

int server_menagment_start_thread(void* arg) {
    (void) arg;
    while(server_menagment_run) {
        sleep(1);
        LOG_DEBUG("Server menagment thread");
    }
    LOG_INFO("Closing server menagment thread");
    return 0;
}

void server_menagment_end_thread(void) {
    server_menagment_run = 0;
}
