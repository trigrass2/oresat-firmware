#ifndef _ACS_DBG_
#define _ACS_DBG_

#include "chprintf.h" 

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

#endif // end _ACS_COMMON_

