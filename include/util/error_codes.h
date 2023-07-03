#ifndef UTIL_ERRROR_CODES_H_
#define UTIL_ERRROR_CODES_H_
#include <assert.h>
#include <errno.h>
#include <string.h>
/**
 * @file    error_codes.h
 * @brief   specify error codes and useful macros that are helpful to check errors
 *
*/
#define SUCCESS     (0)  /** @def SUCCESS*/
#define FAILURE     (-1) /** @def FAILED */

#define ENARG       (-2) /** @def NULL ARGUEMENT */
#define ESOCK       (-3) /** @def ERROR WHEN CREATING SOCKET */
#define EBIND       (-4) /** @def ERROR WHEN BIND SOCKET */
#define EF_SB       (-5) /** @def ERROR FUNCTION SERVER BOOT */
#define ELIST       (-6) /** @def ERROR WHEN LISTENING */
#define EACCT       (-7) /** @def ERROR WHEN ACCEPTING NEW CLIENT */
#define ESCAD       (-8) /** @def ERRoR WHEN PUSHING CLIENT PARAMS TO LIST */

#define EREAD       (-14) /** @def ERROR WHEN TRY TO READ */
#define ERTIMO      (-15) /** @def TIMEOUT REACHED WHEN TRY TO READ */

#define ELARG       (-20) /** @def NULL ARGUEMNT 'LIST' PASSED TO LIST FUNCTION */
#define ELRAN       (-21) /** @def LIST INDEX IS OUT OF RANGE */



#define assert_ss(cond)   assert(cond) /** @brief use it instead of assert() */
#define print_err()       strerror(errno) /** @brief generate string with error msg */
#endif //UTIL_ERRROR_CODES_H_
