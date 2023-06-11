#include "util.h"
#include <utility.h>
#include "unistd.h"

static inline void main_init(void);
static inline void main_destroy(void);

int main() {
    main_init();
    LOG_TRACE("Test");
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