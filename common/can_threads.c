/*
 * CAN Subsystem Threads
 */

//Project headers
#include "can_threads.h"
#include "CO_driver.h"

/*
 * Receiver thread.
 */
THD_WORKING_AREA(can_rx_wa, 128);
THD_FUNCTION(can_rx, p) {
    event_listener_t    can_el;
    CO_CANrxMsg_t       rcvMsg;             /* Received message */
    uint8_t             index;              /* index of received message */
    uint32_t            rcvMsgIdent;        /* identifier of the received message */
    CO_CANrx_t          *buffer = NULL;     /* receive message buffer from CO_CANmodule_t object. */
    bool_t              msgMatched = false;
    CO_CANmodule_t      *CANmodule = p;
    CANDriver           *candev = (CANDriver *)CANmodule->CANbaseAddress;

    // Set thread name
    chRegSetThreadName("receiver");
    // Register RX event
    chEvtRegister(&candev->rxfull_event, &can_el, 0);

    // Start RX Loop
    while (!chThdShouldTerminateX()) {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0) {
            /* No activity, continue and check if thread should terminate */
            continue;
        }

        while (canReceiveTimeout(candev, CAN_ANY_MAILBOX, &rcvMsg.rxFrame, TIME_IMMEDIATE) == MSG_OK) {
            /* Process message.*/
            rcvMsgIdent = rcvMsg.SID | (rcvMsg.RTR << 11);
            if(CANmodule->useCANrxFilters){
                /* CAN module filters are used. Message with known 11-bit identifier has */
                /* been received */
                index = rcvMsg.FMI;  /* Get index of the received message */
                if(index < CANmodule->rxSize){
                    buffer = &CANmodule->rxArray[index];
                    msgMatched = true;
                }
            }
            else{
                /* CAN module filters are not used, message with any standard 11-bit identifier */
                /* has been received. Search rxArray form CANmodule for the same CAN-ID. */
                buffer = &CANmodule->rxArray[0];
                for(index = CANmodule->rxSize; index > 0U; index--){
                    if(((rcvMsgIdent ^ buffer->ident) & buffer->mask) == 0U){
                        msgMatched = true;
                        break;
                    }
                    buffer++;
                }
            }

            /* Call specific function, which will process the message */
            if(msgMatched && (buffer != NULL) && (buffer->pFunct != NULL)){
                buffer->pFunct(buffer->object, &rcvMsg);
            }

        }
    }

    //Unregister RX event before terminating thread
    chEvtUnregister(&candev->rxfull_event, &can_el);
    chThdExit(MSG_OK);
}

/*
 * Transmitter thread.
 */
THD_WORKING_AREA(can_tx_wa, 128);
THD_FUNCTION(can_tx, p) {
    event_listener_t    can_el;

    CO_CANmodule_t      *CANmodule = p;
    CANDriver           *candev = (CANDriver *)CANmodule->CANbaseAddress;

    // Set thread name
    chRegSetThreadName("transmitter");
    // Register TX event
    chEvtRegister(&candev->txempty_event, &can_el, 0);

    // Start TX Loop
    while (!chThdShouldTerminateX()) {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0) {
            /* No activity, continue and check if thread should terminate */
            continue;
        }

        /* First CAN message (bootup) was sent successfully */
        CANmodule->firstCANtxMessage = false;
        /* clear flag from previous message */
        CANmodule->bufferInhibitFlag = false;
        /* Are there any new messages waiting to be sent */
        if(CANmodule->CANtxCount > 0U){
            uint16_t i;             /* index of transmitting message */

            /* first buffer */
            CO_CANtx_t *buffer = &CANmodule->txArray[0];
            /* search through whole array of pointers to transmit message buffers. */
            for(i = CANmodule->txSize; i > 0U; i--){
                /* if message buffer is full, send it. */
                if(buffer->bufferFull){
                    buffer->bufferFull = false;
                    CANmodule->CANtxCount--;

                    /* Copy message to CAN buffer */
                    CANmodule->bufferInhibitFlag = buffer->syncFlag;
                    CO_CANsend(CANmodule, buffer);
                    break;                      /* exit for loop */
                }
                buffer++;
            }/* end of for loop */

            /* Clear counter if no more messages */
            if(i == 0U){
                CANmodule->CANtxCount = 0U;
            }
        }
    }

    //Unregister TX event before terminating thread
    chEvtUnregister(&candev->rxfull_event, &can_el);
    chThdExit(MSG_OK);
}
