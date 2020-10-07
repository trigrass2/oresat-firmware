/*
   ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/* ChibiOS header files */
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

int t1 = 0xDEADBEEF;
int t2 = 0xCAFEBABE;
char str[9] = "hello";


int main(void)
{
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();

    sdStart(&SD2, NULL);

    while (true)
    {
//        chprintf(&SD2, "T1: %d\n", t1);
//        chprintf(&SD2, "T2: %d\n", t2);
  //      chprintf(&SD2, "STR: %s\n", str);

        //palClearLine(LINE_LED);
        palSetLine(LINE_LED);
        chThdSleepMilliseconds(100);
        palSetLine(LINE_LED);
        chThdSleepMilliseconds(100);
    }

    return 0;
}

