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

/* Project header files */
//#include "oresat.h"
#include "blink.h"
#include "chprintf.h"

/**
 * @brief App Initialization
 */
// static void app_init(void)
// {

//       /* Read operation.*/                                                      
//   //flash_error_t (*read)(void *instance, flash_offset_t offset,              
//                      //   size_t n, uint8_t *rp);                             
//   /* Program operation.*/                                                   
//  // flash_error_t (*program)(void *instance, flash_offset_t offset,           
//                //            size_t n, const uint8_t *pp);    

//     /* Starting EFL driver.*/
//     eflStart(&EFLD1, NULL);


//     /* App initialization */
//     init_worker(&worker1, "Example blinky thread", blink_wa, sizeof(blink_wa), NORMALPRIO, blink, NULL, true);
//     reg_worker(&worker1);

//     /* Start up debug output */
//     sdStart(&SD2, NULL);
// }
//

static char* str = "HERE";

/**
 * @brief Main Application
 */
int main(void)
{
    halInit();
    chSysInit();

    /* Starting EFL driver.*/
    eflStart(&EFLD1, NULL);

        /* Start up debug output */
    sdStart(&SD2, NULL);
    // Initialize and start
      /* The blinker thread is spawned.*/

    chprintf(&SD2, "VAR: 0x%x\n", &str);
    chprintf(&SD2, "STR: %s\n", str);

    while(1);
    thread_t *tp = chThdCreateStatic(blink_wa, sizeof(blink_wa), NORMALPRIO + 1, blink, NULL);

    while(1);


    return 0;
}
