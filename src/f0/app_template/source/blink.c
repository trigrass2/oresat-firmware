#include "blink.h"

/* Example blinker thread */
THD_WORKING_AREA(blink_wa, 0x200);
THD_FUNCTION(blink, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED, PAL_MODE_OUTPUT_PUSHPULL);

    while (!chThdShouldTerminateX())
    {
        palToggleLine(LINE_LED);
        chThdSleepMilliseconds(100);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
