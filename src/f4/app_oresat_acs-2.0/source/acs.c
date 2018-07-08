#include "acs.h"

/**
 *	event_lister is used for synchronization between 
 *	the ACS and the CAN thread
 */
event_listener_t el;

/**
 *	ACS initialization function
 */
extern EXIT_STATUS acs_init(ACS *acs){
	(void)acs;
	// need to initialize things
	return STATUS_SUCCESS;
}	

/**
 *	ST_RDY state transistion functions
 */
static ACS_VALID_STATE entry_rdy(ACS *acs){
	(void)acs;
	return ST_RDY;
}

static ACS_VALID_STATE exit_rdy(ACS *acs){
	(void)acs;
	return ST_RDY;
}

/**
 *	ST_RW state transistion functions
 */
static ACS_VALID_STATE entry_rw(ACS *acs){
	(void)acs;
	return ST_RW;
}

static ACS_VALID_STATE exit_rw(ACS *acs){
	(void)acs;
	return ST_RW;
}

/**
 *	ST_MTQR state transistion functions
 */
static ACS_VALID_STATE entry_mtqr(ACS *acs){
	(void)acs;
	return ST_MTQR;
}

static ACS_VALID_STATE exit_mtqr(ACS *acs){
	(void)acs;
	return ST_MTQR;
}

/**
 *	ST_MAX_POWER state transistion functions
 *
 *	TODO: change the name of this to more acurately
 *	reflect it's intent
 */
static ACS_VALID_STATE entry_max_pwr(ACS *acs){
	(void)acs;
	return ST_MAX_PWR;
}

static ACS_VALID_STATE exit_max_pwr(ACS *acs){
	(void)acs;
	return ST_MAX_PWR;
}

/**
 *	Function definitions
 *
 *	These functions are validified using the 
 *	acs_function_rule struct. Functions are 
 *	represented in the struct by pointers
 *	which are associated with a valid state
 *	and valid function name to create a rule 
 *	that allows functions to only be called 
 *	from an allowed state.
 */

/**
 *	Set reaction wheel duty cycle
 */
static EXIT_STATUS fn_rw_setdc(ACS *acs){
	(void)acs;
	return STATUS_SUCCESS;
}

/**
 *	Set magnetorquer duty cycle
 */
static EXIT_STATUS fn_mtqr_setdc(ACS *acs){
	(void)acs;
	return STATUS_SUCCESS;
}

/**
 *	Set magnetorquer duty cycle
 */
acs_function_rule func[] = {
	{ST_RW, 			FN_RW_SETDC,		&fn_rw_setdc},
	{ST_MTQR, 		FN_MTQR_SETDC,	&fn_mtqr_setdc},
	{ST_MAX_PWR, 	FN_RW_SETDC,		&fn_rw_setdc},
	{ST_MAX_PWR, 	FN_MTQR_SETDC,	&fn_mtqr_setdc}
};

#define FUNC_COUNT (int)(sizeof(func)/sizeof(acs_function_rule))

/**
 *
 */
static EXIT_STATUS callFunction(ACS *acs){
	int i;
	ACS_VALID_FUNCTION function;

	for(i = 0;i < FUNC_COUNT;++i){
		if(acs->state.current == func[i].state){
			if((acs->function == func[i].function)){
				function = (func[i].fn)(acs);
				if(function){
//					printf("function call error!\n");
//					TODO: Make this make sense in firmware land
				}
				break;
			}
		}
	}

	return acs->state.current;
}

/**
 *	acs_transition_rule: defines valid state transitions
 *	and associates them with an entry and exit function
 */
acs_transition_rule trans[] = {
	{ST_RDY,			ST_RW,				&entry_rw,				&exit_rdy},
	{ST_RDY,			ST_MTQR,			&entry_mtqr,			&exit_rdy},
	{ST_RDY,			ST_MAX_PWR,		&entry_max_pwr,		&exit_rdy},
	{ST_RW,				ST_MAX_PWR,		&entry_max_pwr,		&exit_rw},
	{ST_MTQR,			ST_MAX_PWR,		&entry_max_pwr,		&exit_mtqr},
	{ST_RW,				ST_RDY,				&entry_rdy,				&exit_rw},
	{ST_MTQR,			ST_RDY,				&entry_rdy,				&exit_mtqr},
	{ST_MAX_PWR,	ST_RDY,				&entry_rdy,				&exit_max_pwr},
	{ST_MAX_PWR,	ST_RW,				&entry_rw,				&exit_max_pwr},
	{ST_MAX_PWR,	ST_MTQR,			&entry_mtqr,			&exit_max_pwr},
};

#define TRANS_COUNT (int)(sizeof(trans)/sizeof(acs_transition_rule))

/**
 *
 */
ACS_VALID_FUNCTION requestFunction(ACS *acs){
	int function =0;
//	char input[3]="";

// *******************************************
// TODO: this whole section need to be ported to CAN input
// for the F4
//	printf("\nrequest function call$ ");
//	scanf(" %s", input);
//	function = atoi(input);
	if(function < FN_RW_SETDC || function >= FUNC_COUNT){
//		printf("error, invalid function call: %d\n",function);
		return STATUS_FAILURE; 
	}
//	printf("function call request %s received\n", function_name[function]);
	acs->function = function;
	callFunction(acs);
	return STATUS_SUCCESS;
}

/**
 *
 */
ACS_VALID_STATE requestTransition(ACS *acs){
	int i,state = 0;

	if((int)state < 0 || state >= NUM_VALID_STATES){
		return STATUS_FAILURE; 
	}
	for (i = 0;i < TRANS_COUNT;++i){
		if((acs->state.current==trans[i].cur_state)&&(state==trans[i].req_state)){
			acs->fn_exit(acs);
			acs->fn_exit=trans[i].fn_exit;
			acs->state.current = (trans[i].fn_entry)(acs);
			break;
		}
	}

	return STATUS_SUCCESS;
}

/**
 *	handles events off the CAN bus
 */
EXIT_STATUS handleEvent(ACS *acs){
//	uint8_t cmd = 0u;

	chEvtWaitAny(ALL_EVENTS);	
// ******critical section*******
	chSysLock();
	for(int i=0;i<CAN_BUF_SIZE;++i){
		acs->cmd[i]=acs->can_buf.cmd[i];
		acs->can_buf.cmd[i]=0x00;
	}
	chSysUnlock();
// ******end critical section*******
	
	switch(acs->cmd[CAN_CMD_0]){
		case CHANGE_STATE:
			requestTransition(acs);
			break;
		case CALL_FUNCTION:
			requestFunction(acs);
			break;
		default:
			return STATUS_INVALID_CMD;
	}

	return STATUS_SUCCESS;
}

/**
 *	ACS statemachine entry
 */
extern EXIT_STATUS acs_statemachine(ACS *acs){
	acs->state.current = entry_rdy(acs);
	acs->fn_exit = exit_rdy;

	while(!chThdShouldTerminateX()){
		handleEvent(acs);
    chThdSleepMilliseconds(100);
	}
	
	return STATUS_SUCCESS;
} 

/**
 *
 */
THD_WORKING_AREA(waACS_Thread,ACS_THREAD_SIZE);
THD_FUNCTION(ACS_Thread,acs){
//	((ACS *)acs)->state.current=1;

  chRegSetThreadName("acs_thread");

	acs_statemachine(acs);
/*
  while (!chThdShouldTerminateX()){
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
  }
//*/
}
