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
#include "shell.h"

/* Project header files */
#include "oresat.h"
#include "command.h"

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* App initialization */
    reg_worker("Command Shell", cmd_wa, sizeof(cmd_wa), NORMALPRIO, cmd, NULL);

    /* Initialize OPD */
    opd_init();

    /* Initialize shell and start serial interface */
    shellInit();
    sdStart(&SD2, NULL);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init(ORESAT_DEFAULT_ID, ORESAT_DEFAULT_BITRATE);
    app_init();
    oresat_start(&CAND1);
    return 0;
}