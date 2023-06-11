#include <utility.h>
#include "unistd.h"
#include "server_boot.h"
static inline void main_init(void);
static inline void main_destroy(void);

int main() {
    ServerS server;
    main_init();
    server_boot(&server);
    sleep(2);
    server_close(&server);
    main_destroy();


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

static inline void main_destroy(void) {
    logger_close();
}
