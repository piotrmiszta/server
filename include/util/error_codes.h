#ifndef UTIL_ERRROR_CODES_H_
#define UTIL_ERRROR_CODES_H_
#include <assert.h>

#define SUCCESS     (0)
#define ENARG       (-1) /** @def NULL ARGUEMENT */
#define ESOCK       (-2) /** @def ERROR WHEN CREATING SOCKET */
#define EBIND       (-3) /** @def ERROR WHEN BIND SOCKET */
#define EF_SB       (-4) /** @def ERROR FUNCTION SERVER BOOT */
#define ELIST       (-5) /** @def ERROR WHEN LISTENING */
#define EACCT       (-6) /** @def ERROR WHEN ACCEPTING NEW CLIENT */


#define assert_ss(cond)   assert(cond)

#endif //UTIL_ERRROR_CODES_H_
