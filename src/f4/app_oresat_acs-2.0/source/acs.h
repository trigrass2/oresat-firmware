#ifndef _ACS_H_
#define _ACS_H_

#include "ch.h"
#include "hal.h"
#include "stdint.h"

#define ACS_THREAD_SIZE	(1<<7)
#define CAN_BUF_SIZE		8

typedef enum{
	STATUS_SUCCESS=0,
	STATUS_FAILURE
}STATUS;

typedef struct{
	uint8_t last_state,
					curr_state, 
					next_state;
}ACS_STATE;

typedef struct{
	uint8_t command[CAN_BUF_SIZE];
	uint8_t status[CAN_BUF_SIZE];
}CAN_BUFFER;

typedef struct{
	ACS_STATE acs_state;
	CAN_BUFFER can_buf;
}ACS;

extern THD_WORKING_AREA(waACS_Thread,ACS_THREAD_SIZE);
extern THD_FUNCTION(ACS_Thread, arg);

extern STATUS acs_init(ACS *acs);

#endif
