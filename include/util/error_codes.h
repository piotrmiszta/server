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
#define SUCCESS     (0)
#define ENARG       (-1) /** @def NULL ARGUEMENT */
#define ESOCK       (-2) /** @def ERROR WHEN CREATING SOCKET */
#define EBIND       (-3) /** @def ERROR WHEN BIND SOCKET */
#define EF_SB       (-4) /** @def ERROR FUNCTION SERVER BOOT */
#define ELIST       (-5) /** @def ERROR WHEN LISTENING */
#define EACCT       (-6) /** @def ERROR WHEN ACCEPTING NEW CLIENT */
#define ESCAD       (-7) /** @def ERRIR WHEN PUSHING CLIENT PARAMS TO LIST */

#define ELARG       (-20) /** @def NULL ARGUEMNT 'LIST' PASSED TO LIST FUNCTION */
#define ELRAN       (-21) /** @def LIST INDEX IS OUT OF RANGE */

#define assert_ss(cond)   assert(cond) /** @brief use it instead of assert() */
#define print_err()       strerror(errno) /** @brief generate string with error msg */
#endif //UTIL_ERRROR_CODES_H_
