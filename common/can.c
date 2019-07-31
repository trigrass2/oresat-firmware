/*
 * CAN Subsystem Implementation
 */

#include "oresat.h"
#include "can.h"
#include "can_hw.h"
#include "can_threads.h"

can_node_t node;
can_tpdo_t tpdo[4];
can_rpdo_t rpdo[4];

event_source_t rpdo_event;

void can_init(uint8_t node_id, uint32_t heartbeat) {
    // If node_id is greater than maximum node ID (127), halt
    chDbgAssert(node_id <= 0x7F, "Error: Node ID out of range");

    // Initialize node configuration data
    node.node_id = node_id;
    node.err_code = 0x00;
    node.heartbeat_time = heartbeat;
    node.error_reg = 0x00;

    // Initialize the node heartbeat message
    // CAN ID for heartbeat is 0x700 + Node ID
    node.heartbeat_msg.IDE = CAN_IDE_STD;
    node.heartbeat_msg.SID = CAN_ID_HEARTBEAT + node_id;
    node.heartbeat_msg.RTR = CAN_RTR_DATA;
    node.heartbeat_msg.DLC = 1;
    node.heartbeat_msg.data8[0] = 0x05;

    // Initialize all TPDO and RPDO objects
    for (uint8_t i = 0; i < 4; ++i) {
        canTPDOObjectInit(i, CAN_ID_DEFAULT, 0, 0, 0, NULL);
        canRPDOObjectInit(i, CAN_ID_DEFAULT, 0, NULL);
    }

    chEvtObjectInit(&rpdo_event);

    // Initialize the hardware
    canHWInit(node_id);

    return;
}

void can_start(void) {
    // Start the CAN subsystem threads
    can_start_threads();

    return;
}

// TPDO Initialization
// pdo_num is a zero-based index of TPDO 1-4
// can_id is the CAN Message ID the TPDO is sent with. Set to zero (0) to use default
void canTPDOObjectInit(can_pdo_t pdo_num, can_id_t can_id, uint32_t event_time, uint32_t inhibit_time, uint8_t len, uint8_t *pdata) {
    // Sanity check on parameters
    // If the pdo_num is greater than 3 (TPDO 4), report error
    chDbgAssert(pdo_num <= 3, "Error: Invalid PDO number");
    if (event_time == 0) {
        event_time = DEFAULT_TPDO_TIMEOUT;
    }
    // If the can_id is zero, set the default value (TPDO# base ID + Node ID)
    if (can_id == 0) {
        can_id = CAN_ID_TPDO(pdo_num, node.node_id);
    } else {
        chDbgAssert(can_id > 0x180 && can_id < 0x580, "Error: TPDO CANID out of range");
    }

    // Initialize TPDO configuration data
    chVTObjectInit(&tpdo[pdo_num].event_timer);

    tpdo[pdo_num].event_time = event_time;
    tpdo[pdo_num].inhibit_time = inhibit_time;
    tpdo[pdo_num].pdata = pdata;

    // Initialize TPDO TX Frame
    tpdo[pdo_num].msg.IDE = CAN_IDE_STD;
    tpdo[pdo_num].msg.RTR = CAN_RTR_DATA;
    tpdo[pdo_num].msg.DLC = len;
    tpdo[pdo_num].msg.SID = can_id;

    return;
}

// RPDO Initialization
// pdo_num is a zero-based index of RRDO 1-4
// can_id is the CAN Message ID the RPDO is watching for. Set to zero (0) to use default
void canRPDOObjectInit(can_pdo_t pdo_num, can_id_t can_id, uint8_t len, uint8_t *pdata) {
    // If the pdo_num is greater than 3 (RPDO 4), report error
    chDbgAssert(pdo_num <= 3, "Error: Invalid PDO number");

    // Initialize RPDO configuration data
    rpdo[pdo_num].len = len;
    rpdo[pdo_num].pdata = pdata;

    // If the can_id is zero, set the default value (RPDO# base ID + Node ID)
    if (can_id == CAN_ID_DEFAULT) {
        can_id = ((pdo_num + 2) << 8) + node.node_id;
    }
    chDbgAssert(can_id > 0x180 || can_id < 0x580, "Error: TPDO CANID out of range");
    rpdo[pdo_num].can_id = can_id;
    canFilterAdd(can_id, can_id, CAN_FLT_LIST_MODE);

    return;
}

void can_reset_app(void) {

    return;
}
void can_reset_comms(void) {

    return;
}
