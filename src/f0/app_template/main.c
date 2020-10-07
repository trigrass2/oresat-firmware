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
#include "oresat.h"
#include "blink.h"
#include "fw_update.h"

static worker_t worker1;
static worker_t fw_update_worker;

static oresat_config_t oresat_conf = {
    &CAND1,
    ORESAT_DEFAULT_ID,
    ORESAT_DEFAULT_BITRATE
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* Starting EFL driver.*/
    eflStart(&EFLD1, NULL);

    // start the blinky thread
    //init_worker(&worker1, "Example blinky thread", blink_wa, sizeof(blink_wa), NORMALPRIO, blink, NULL, true);
    //reg_worker(&worker1);

    // start the FW update thread
    init_worker(&fw_update_worker, "FW update thread", fw_update_wa, sizeof(fw_update_wa), NORMALPRIO, fw_update, NULL, true);
    reg_worker(&fw_update_worker);

    /* Start up debug output */
    sdStart(&SD2, NULL);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init();
    app_init();
    oresat_start(&oresat_conf);
    return 0;
}
