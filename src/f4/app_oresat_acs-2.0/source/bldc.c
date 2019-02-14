#include "bldc.h"
#include "acs_common.h"

/**
 * @brief Currently not used.
 *
 */
/*
static void adcerrorcallback(ADCDriver *adcp, adcerror_t err)
{
  (void)adcp;
  (void)err;
}
//*/

/**
 * TODO: combine this with a timer to not spam interrupts so much?
 * @brief ADC conversion group, used to configure the ADC driver
 * Mode:        Continuous, 1 sample of 1 channel, SW triggered.
 * Channels:    A0 
 * Slowest sample rate possible, as putting it too high can lock other systems out.
 */
/*
static const ADCConversionGroup adcgrpcfg = {
  TRUE,
  ADC_GRP_NUM_CHANNELS,
  NULL,
  adcerrorcallback,
  ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,      // CFGRR1 
  ADC_TR(0, 0),                              // TR 
  ADC_SMPR_SMP_239P5,                        // SMPR 
  ADC_CHSELR_CHSEL0                          // CHSELR 
};
//*/

/*
static const ADCConversionGroup adcgrpcfg = 
{
  TRUE,
  ADC_GRP_NUM_CHANNELS,
  NULL,
  adcerrorcallback,
  0,                        // CR1
  ADC_CR2_SWSTART,          // CR2
  ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3),
  0,                        // SMPR2 
  0,                        // SQR1 
  0,                        // SQR2
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11)
};
//*/

/*
static const SPIConfig spicfg = {
	false,             // circular buffer.
	NULL,              // operation complete callback callback pointer
	GPIOA,                                                // Chip select line.
	GPIOA_SPI3_NSS,                                       // Chip select port.
	SPI_CR1_BR_0|SPI_CR1_BR_1|SPI_CR1_BR_2|SPI_CR1_CPHA,  // SPI Ctrl Reg 1 mask.
	SPI_CR2_DS_0|SPI_CR2_DS_1|SPI_CR2_DS_2|SPI_CR2_DS_3,  // SPI Ctrl Reg 2 mask.
};
//*/

/*
static const SPIConfig spicfg = {
	false,             // circular buffer.
	NULL,              // operation complete callback callback pointer
	GPIOA,                                                // Chip select line.
	GPIOA_SPI3_NSS,                                       // Chip select port.
	SPI_CR1_BR_1|SPI_CR1_BR_2,  // SPI Ctrl Reg 1 mask.
	0
};
//*/

//*
static const SPIConfig spicfg = {
	false,             // circular buffer.
	NULL,              // operation complete callback callback pointer
	GPIOA,                                                // Chip select line.
	GPIOA_SPI3_NSS,                                       // Chip select port.
	0,
	0
};
//*/

/**
 * @brief Handles the SPI transaction, getting the position from the encoder
 *
 */
/*
THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg)
{
  chRegSetThreadName("spiThread");
  
  BLDCMotor *pMotor = (BLDCMotor *)arg;

  spiStart(&SPID3,&spicfg);            	// Start driver.
  spiAcquireBus(&SPID3);                // Gain ownership of bus.

  while(!chThdShouldTerminateX()) 
  {
		pMotor->spiRxBuffer[0] = 0;
		spiSelect(&SPID3);                  // Select slave.

		while(SPID3.state != SPI_READY) 
    { 
      // do nothing 
    }   
		
    spiReceive(&SPID3, 1, pMotor->spiRxBuffer); // Receive 1 frame (16 bits).
		spiUnselect(&SPID3);                // Unselect slave.

		pMotor->position = 0x3FFF & pMotor->spiRxBuffer[0];
    //chprintf(DEBUG_CHP, "%u\n\r",pMotor->spiRxBuffer[0]);
    chprintf(DEBUG_CHP, "%u\n\r",pMotor->position);
  }

	spiReleaseBus(&SPID3);    // Release ownership of bus.
	spiStop(&SPID3);          // Stop driver.
}
//*/
#include "ccportab.h"
CC_ALIGN(32) static uint8_t txbuf[512];
CC_ALIGN(32) static uint8_t rxbuf[512];

THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg)
{
  chRegSetThreadName("spiThread");
  
  BLDCMotor *pMotor = (BLDCMotor *)arg;

//		pMotor->spiRxBuffer[0] = 0;
  //spiReceive(&SPID3, 1, pMotor->spiRxBuffer); // Receive 1 frame (16 bits).
//		pMotor->position = 0x3FFF & pMotor->spiRxBuffer[0];
  //  chprintf(DEBUG_CHP, "%u\n\r",pMotor->position);

  while (true) {
    spiAcquireBus(&SPID3);        /* Acquire ownership of the bus.    */
    //palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_ON);
    spiStart(&SPID3,&spicfg); /* Setup transfer parameters.       */
    spiSelect(&SPID3);            /* Slave Select assertion.          */
    spiExchange(&SPID3, 512,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
		pMotor->position = 0x3FFF & rxbuf[0];
    chprintf(DEBUG_CHP, "%u\n\r",pMotor->position);
    spiUnselect(&SPID3);          /* Slave Select de-assertion.       */
    cacheBufferInvalidate(&txbuf[0],    /* Cache invalidation over the      */
                          sizeof txbuf);/* buffer.                          */
    spiReleaseBus(&SPID3);        /* Ownership release.               */
  }  
}

/**
 * @brief Scales the duty ccycle value from LUT 0 - 100%
 *
 */
/*
static dutycycle_t scale(dutycycle_t duty_cycle)
{
	return ((duty_cycle*pMotor->scale)/100) + ((10000*(pMotor->scale/2))/100);	
}
//*/

/**
 * @brief Periodic callback of the PWM driver
 *
 */

static int count = 0;

static void pwmPeriodCallback(PWMDriver *pwmp) 
{
  (void)pwmp;
  // TODO: WOW! This is boring now...
  if(count == 100)
  {
    count = 0;
  }
  else
  {
    ++count;
  }
}

/**
 * @brief Pwm driver configuration structure.
 * 
 * PWM_TIMER_FREQ is our timer clock in Hz
 *
 * PWM_PERIOD period in ticks
 *
 * Configured with pwmpcb as the periodic callback
 * PWM channels 0,1,2 are all active high, with a complementary output
 * and no channel callback
 *
 */
static PWMConfig pwmRwConfig = 
{
  PWM_TIMER_FREQ,	
  PWM_PERIOD,	
  pwmPeriodCallback,
  {
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
	0,
  0
};

/**
 * @brief Sets up initial values for the BLDCMotor object
 *
 */
extern void bldcInit(BLDCMotor *pMotor)
{
  pMotor->pSinLut = sin_lut;
  pMotor->periodCount = 0;
  pMotor->position = 0;
 // pMotor->u = 0;
 // pMotor->v = pMotor->u + pMotor->phaseShift;
 // pMotor->w = pMotor->v + pMotor->phaseShift;
  pMotor->isOpenLoop = true;
  pMotor->isStarted = false;
	
  //*
	pMotor->pSpiThread=chThdCreateStatic(
		wa_spiThread,
		sizeof(wa_spiThread),
		NORMALPRIO,
		spiThread,
		pMotor
	);
//*/

	//adcStart(&ADCD1, NULL); 
  //adcStartConversion(&ADCD1, &adcgrpcfg, pMotor->samples, ADC_GRP_BUF_DEPTH);


}

/**
 * @brief Enables the three PWM channels, starting to go through the LUT
 *
 */
extern void bldcStart(BLDCMotor *pMotor)
{
	if(pMotor->isStarted)
  {
		return; 
	}

/*
	pMotor->pSpiThread=chThdCreateStatic(
		wa_spiThread,
		sizeof(wa_spiThread),
		NORMALPRIO,
		spiThread,
		pMotor
	);
//*/

	pwmStart(&PWMD1,&pwmRwConfig);
  pwmEnablePeriodicNotification(&PWMD1);
	
	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pMotor->u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pMotor->v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pMotor->w));
//*
  bldcSetDutyCycle(PWM_U,5000);
	bldcSetDutyCycle(PWM_V,5000);
	bldcSetDutyCycle(PWM_W,5000);
//*/  
  pMotor->isStarted = TRUE;
}

/**
 * @brief Stops BLDCMotor control
 *
 */
extern void bldcStop(BLDCMotor *pMotor)
{
	if(!pMotor->isStarted)
  {
		return;
	}
	pwmDisableChannel(&PWMD1,PWM_U);
  pwmDisableChannel(&PWMD1,PWM_V);
  pwmDisableChannel(&PWMD1,PWM_W);
  pwmDisablePeriodicNotification(&PWMD1);
	pwmStop(&PWMD1);
//  chThdTerminate(pMotor->pSpiThread);
	pMotor->isStarted = FALSE;
}

/**
 * @brief Changes duty cycle for a given channel
 *
 */
extern void bldcSetDutyCycle(uint8_t channel, dutycycle_t dc)
{
	pwmEnableChannelI(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,dc)
	);
}

/**
 * @brief Tear down drivers in a sane way.
 *
 */
extern void bldcExit(BLDCMotor *pMotor)
{
	if(pMotor->isStarted)
  {
		bldcStop(pMotor);
	}
  //adcStopConversion(&ADCD1);
  //adcStop(&ADCD1); 
	chThdTerminate(pMotor->pSpiThread);
	chThdWait(pMotor->pSpiThread);
}
