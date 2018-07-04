#include "acs.h"

extern STATUS acs_init(ACS *acs){
	(void)acs;	
	return STATUS_SUCCESS;
}	
	
THD_WORKING_AREA(waACS_Thread, ACS_THREAD_SIZE);
THD_FUNCTION(ACS_Thread, arg){
  (void)arg;

  chRegSetThreadName("acs_thread");

  while (!chThdShouldTerminateX()){
//    palClearLine(LINE_LED_GREEN);
		palClearPad(GPIOA, GPIOA_LED_GREEN);
    chThdSleepMilliseconds(500);
    //palSetLine(LINE_LED_GREEN);
		palSetPad(GPIOA, GPIOA_LED_GREEN);
    chThdSleepMilliseconds(500);
  }
}
