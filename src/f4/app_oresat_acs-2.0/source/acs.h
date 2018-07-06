#ifndef _ACS_H_
#define _ACS_H_

#include "ch.h"
#include "hal.h"
#include "stdint.h"

#define ACS_THREAD_SIZE	(1<<7)

/**
 *	CAN definitions
 */
#define CAN_BUF_SIZE		8			/// bytes in buffer
#define CAN_NODE_ID			0x3F	/// max 0x7F

/**
 * Serial debugging
 */
#define DEBUG_SERIAL SD2
#define DEBUG_CHP ((BaseSequentialStream *) &DEBUG_SERIAL)

/**
 *	Function return status
 */
typedef enum{
	STATUS_SUCCESS=0,
	STATUS_FAILURE
}EXIT_STATUS;

typedef enum{
	ST_RDY,		// low power
	ST_RW,
	ST_MTQR,
	ST_MAX_PWR
}ACS_VALID_STATE;

#define MAX_STATES (int)(sizeof(ACS_VALID_STATE))

typedef enum{
	FN_RW_SETDC,
	FN_MTQR_SETDC//,
}ACS_VALID_FUNCTION;

typedef struct ACS ACS;

struct ACS{
	acs_state cur_state;
	acs_function function;
	int (*fn_exit)(ACS *acs);
};

typedef struct{
	acs_state cur_state;
	acs_state req_state;
	int (*fn_entry)(ACS *acs);
	int (*fn_exit)(ACS *acs);
}acs_transition_rule;

typedef struct{
	acs_state state;
	acs_function function;
	int (*fn)(ACS *acs);
}acs_function_rule;

/**
 *	State information struct
 */
typedef struct{
	uint8_t last,current,next;
}ACS_STATE;

/**
 *	CAN buffer structure for command
 *	and status 
 */
typedef struct{
	uint8_t cmd[CAN_BUF_SIZE];
	uint8_t status[CAN_BUF_SIZE];
}CAN_BUFFER;

/**
 * Buffer for receiving commands off the CAN bus
 */
typedef enum{
	CAN_CMD_0=0,
	CAN_CMD_1,
	CAN_CMD_2,
	CAN_CMD_3,
	CAN_CMD_4,
	CAN_CMD_5,
	CAN_CMD_6,
	CAN_CMD_7
}CAN_COMMAND_BUF;

/**
 * Buffer for maintaining and reporting both
 * state and ACS status information
 */
typedef enum{
	CAN_STATE_0=0,
	CAN_STATE_1,
	CAN_STATE_2,
	CAN_STATE_3,
	CAN_STATE_4,
	CAN_STATE_5,
	CAN_STATE_6,
	CAN_STATE_7
}CAN_STATUS_BUF;

/**
 *	ACS: State and control information struct
 */
typedef struct{
	ACS_STATE state;
	CAN_BUFFER can_buf;
}ACS;

extern THD_WORKING_AREA(waACS_Thread,ACS_THREAD_SIZE);
extern THD_FUNCTION(ACS_Thread, arg);

extern EXIT_STATUS acs_init(ACS *acs);

extern acs_transition_rule trans[];
extern acs_function_rule func[];

extern int acs_statemachine(ACS *acs);

#endif
