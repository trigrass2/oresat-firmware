/*
 * CAN Subsystem implementation
 */

#include "ch.h"
#include "hal.h"

#include "can.h"

/*
 * Receiver thread.
 */
static THD_WORKING_AREA(can_rx_wa, 256);
static THD_FUNCTION(can_rx, p)
{
    event_listener_t        el;
    CANRxFrame              rxmsg;

    (void)p;
    // Set thread name
    chRegSetThreadName("receiver");
    // Register RX event
    chEvtRegister(&CAND1.rxfull_event, &el, 0);

    // Configure Status LED (Green)
    palSetLineMode(LINE_LED_GREEN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(LINE_LED_GREEN);

    // Start RX Loop
    while (!chThdShouldTerminateX())
    {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0)
        {
            continue;
        }
        while (canReceive(&CAND1, CAN_ANY_MAILBOX, &rxmsg, TIME_IMMEDIATE) == MSG_OK)
        {
            /* Process message.*/
            palToggleLine(LINE_LED_GREEN);
        }
    }

    //Unregister RX event before terminating thread
    chEvtUnregister(&CAND1.rxfull_event, &el);
}

/*
 * Transmitter thread.
 */
static THD_WORKING_AREA(can_tx_wa, 256);
static THD_FUNCTION(can_tx, p)
{
    CANTxFrame txmsg;

    (void)p;
    chRegSetThreadName("transmitter");
    txmsg.IDE = CAN_IDE_STD;
    txmsg.SID = 0x000;
    txmsg.RTR = CAN_RTR_DATA;
    txmsg.DLC = 8;
    txmsg.data8[0] = 0x00;
    txmsg.data8[1] = 0x01;
    txmsg.data8[2] = 0x02;
    txmsg.data8[3] = 0x03;
    txmsg.data8[4] = 0x04;
    txmsg.data8[5] = 0x05;
    txmsg.data8[6] = 0x06;
    txmsg.data8[7] = 0x07;

    // Start TX Loop
    while (!chThdShouldTerminateX())
    {
        canTransmit(&CAND1, CAN_ANY_MAILBOX, &txmsg, TIME_MS2I(100));
        chThdSleepMilliseconds(500);
    }
}


void can_init(void)
{
    /*
     * Activates CAN driver 1.
     */
    canStart(&CAND1, &cancfg);
}

void can_start(void)
{
    /*
     * Starting the transmitter and receiver threads.
     */
    chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), NORMALPRIO + 7, can_rx, NULL);
    chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), NORMALPRIO + 7, can_tx, NULL);
}