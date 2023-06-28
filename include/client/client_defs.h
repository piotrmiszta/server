#ifndef CLIENT_DEFS_H_
#define CLIENT_DEFS_H_
#include <sha1.h>

#define SHA1_SIZE       20
#define LOGIN_SIZE      SHA1_SIZE
#define PASS_SIZE       SHA1_SIZE

typedef struct ClientAuthS {
    /*login and pass only sha1 */
    char login[LOGIN_SIZE];
    char pass[PASS_SIZE];
}ClientAuthS;


#endif //CLIENT_DEFS_H_
