#include <utility.h>
#include "unistd.h"
#include "server_boot.h"
#include <signal.h>
#include <stdlib.h>
#define VALGRIND
static inline void main_init(void);
static inline void main_destroy(void);

static ServerS server;

static void sigint_handler(int sig);

int main() {
    struct sigaction act = {0};
    act.sa_handler = sigint_handler;
    sigaction(SIGINT, &act, NULL);
    main_init();
    server_boot(&server);

    #ifdef VALGRIND
    sleep(10);
    sigint_handler(SIGINT);
    #else
    while(1) {}
    #endif
}

static inline void main_init(void) {
    LoggerParams param = {
        .author = "Piotr Miszta",
        .contact = "miszta.piotr.pm@gmail.com",
        .filename = "log.log",
        .version = 1.00,
    };
    logger_init(&param);
}

static void sigint_handler(int sig) {
    assert(sig == SIGINT);
    LOG_INFO(   "Detected Ctrl-C, closing server, deallcate all memory ...\n"
                "---------------------------------------------------------\n");
    server_close(&server);
    logger_close();
    exit(0);
}

static inline void main_destroy(void) {
    logger_close();
}
