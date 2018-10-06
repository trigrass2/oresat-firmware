#include "acs.h"
#include "chprintf.h"

/**
 *	event_lister is used for synchronization between 
 *	the ACS and the CAN thread
 */
event_listener_t el;

/**
 *	@brief ACS initialization function
 */
extern EXIT_STATUS acs_init(ACS *acs){
	(void)acs;
	// need to initialize things
	return STATUS_SUCCESS;
}	

/**
 *	@brief updates current CAN_SM_STATE to the value of next_state
 */
inline static EXIT_STATUS entry_helper(ACS *acs, ACS_VALID_STATE next_state){
/// ******critical section*******
	chSysLock();
	acs->can_buf.status[CAN_SM_STATE] = next_state;
	chSysUnlock();
/// ******end critical section*******
	return STATUS_SUCCESS;
}

/**
 *	@brief updates CAN_SM_PREV_STATE buffer to the value of CAN_SM_STATE
 *	@brief buffer. this relects the change of the current state to previous
 */
inline static EXIT_STATUS exit_helper(ACS *acs){
/// ******critical section*******
	chSysLock();
	acs->can_buf.status[CAN_SM_PREV_STATE] = acs->can_buf.status[CAN_SM_STATE];
	chSysUnlock();
/// ******end critical section*******
	return STATUS_SUCCESS;
}

/**
 *	ST_RDY state transistion functions
 */
static ACS_VALID_STATE entry_rdy(ACS *acs){
	(void)acs;
	entry_helper(acs,ST_RDY);
	return ST_RDY;
}

static ACS_VALID_STATE exit_rdy(ACS *acs){
	(void)acs;
	exit_helper(acs);
	return ST_RDY;
}

/**
 *	ST_RW state transistion functions
 */
static ACS_VALID_STATE entry_rw(ACS *acs){
	(void)acs;
	entry_helper(acs,ST_RW);
	return ST_RW;
}

static ACS_VALID_STATE exit_rw(ACS *acs){
	(void)acs;
	exit_helper(acs);
	return ST_RW;
}

/**
 *	ST_MTQR state transistion functions
 */
static ACS_VALID_STATE entry_mtqr(ACS *acs){
	(void)acs;
	entry_helper(acs,ST_MTQR);
	return ST_MTQR;
}

static ACS_VALID_STATE exit_mtqr(ACS *acs){
	(void)acs;
	exit_helper(acs);
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
	entry_helper(acs,ST_MAX_PWR);
	return ST_MAX_PWR;
}

static ACS_VALID_STATE exit_max_pwr(ACS *acs){
	(void)acs;
	exit_helper(acs);
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
	EXIT_STATUS exit_status;

	for(i = 0;i < FUNC_COUNT;++i){
		if(acs->state.current == func[i].state){
			if(acs->function == func[i].function){
				exit_status = (func[i].fn)(acs);
				if(exit_status != STATUS_SUCCESS){
//					printf("function call error!\n");
            chprintf(DEBUG_CHP,"Function call error: %u \n\r", exit_status);
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
EXIT_STATUS requestFunction(ACS *acs){
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
 *	transitionState
 */
EXIT_STATUS transitionState(ACS *acs){
	ACS_VALID_STATE state = acs->cmd[CAN_CMD_ARG];
	if(state <= ST_NOP || state >= NUM_VALID_STATES){
  chprintf(DEBUG_CHP,"ERROR: %u \n\r", state);
		return STATUS_INVALID_STATE; 
	}
	for (int i = 0;i < TRANS_COUNT;++i){
		if((acs->state.current==trans[i].cur_state)&&(state==trans[i].req_state)){
      chprintf(DEBUG_CHP,"Changing to state: %u \n\r", state);
			acs->fn_exit(acs);
			acs->fn_exit=trans[i].fn_exit;
			acs->state.current = (trans[i].fn_entry)(acs);
			return STATUS_SUCCESS;
		}
	}
	return STATUS_INVALID_TRANSITION;
}

/**
 *	handles events off the CAN bus
 */
EXIT_STATUS handleEvent(ACS *acs){
  chprintf(DEBUG_CHP,"Entered handleEvent...\n\r",0);
	EXIT_STATUS status = STATUS_SUCCESS;
	chEvtWaitAny(ALL_EVENTS);	
  chprintf(DEBUG_CHP,"Received Event: %u \n\r", status);
/// ******critical section*******
	chSysLock();
	for(int i = 0;i < CAN_BUF_SIZE; ++i){
		acs->cmd[i] = acs->can_buf.cmd[i];
		acs->can_buf.cmd[i] = 0x00;
	}
	chSysUnlock();
/// ******end critical section*******
	
  chprintf(DEBUG_CHP,"CMD: %u \n\r", acs->cmd[CAN_CMD_0]);
	switch(acs->cmd[CAN_CMD_0]){
		case CHANGE_STATE:
			status = transitionState(acs);
		/// ******critical section*******
			chSysLock();
			acs->can_buf.status[CAN_SM_STATUS] = status;
			chSysUnlock();
		/// ******end critical section*******
			break;
		case CALL_FUNCTION:
			/* not ready yet
			requestFunction(acs);
			//*/
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
//*
	acs->state.current = entry_rdy(acs);
	acs->fn_exit = exit_rdy;
//*/
/*
	acs->state.current = entry_rw(acs);
	acs->fn_exit = exit_rw;
//*/

  chprintf(DEBUG_CHP,"Entering acs_statemachine...\n\r",0);
	while(!chThdShouldTerminateX()){
		handleEvent(acs);
    chThdSleepMilliseconds(100);
	/* // this is for a sanity check
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
	//*/
	}
	
	return STATUS_SUCCESS;
} 

/**
 *	ACS thread working area and thread *	function.
 */
THD_WORKING_AREA(waCANDBG_Thread,ACS_THREAD_SIZE);
THD_FUNCTION(CANDBG_Thread,acs){
  chRegSetThreadName("can_dbg_thread");
  
  uint8_t ping = 0u;
  while(1){
    chSysLock();
    ((ACS *)acs)->can_buf.status[CAN_STATUS_PING] = ++ping;
    chSysUnlock();
    chThdSleepMilliseconds(5*1000);
  }
}

/**
 *	ACS thread working area and thread *	function.
 */
THD_WORKING_AREA(waACS_Thread,ACS_THREAD_SIZE);
THD_FUNCTION(ACS_Thread,acs){
//	((ACS *)acs)->state.current=1;

  chRegSetThreadName("acs_thread");

	acs_statemachine(acs);
}

