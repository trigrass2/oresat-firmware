#ifndef _ACS_DBG_
#define _ACS_DBG_

#include "chprintf.h" 
#include "oresat.h"
#include "stdint.h"

//#define DEBUG_OUT 

/**
 *	Serial debugging
 */
#define CH_DBG_SYSTEM_STATE_CHECK TRUE
#define DEBUG_SERIAL SD2
#define DEBUG_CHP ((BaseSequentialStream *) &DEBUG_SERIAL)

inline void dbgSerialOut(char *message, uint32_t arg, uint32_t delay)
{
#ifndef DEBUG_OUT
  (void)message;
  (void)arg;
  (void)delay;
#endif
#ifdef DEBUG_OUT
  chprintf(DEBUG_CHP, message, arg);
	chThdSleepMilliseconds(delay);
#endif
}

/**
 *	Function return status
 */
typedef enum
{
	STATUS_SUCCESS = 0u,
	STATUS_FAILURE,
	STATUS_INVALID_CMD,
	STATUS_INVALID_STATE,
	STATUS_INVALID_TRANSITION
} EXIT_STATUS;

#endif // end _ACS_COMMON_

