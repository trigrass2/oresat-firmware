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

/**
 * @brief Handles the SPI transaction, getting the position from the encoder
 *
 */
THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg)
{
  chRegSetThreadName("spiThread");
  
  BLDCMotor *pMotor = (BLDCMotor *)arg;

  spiStart(&SPID1,&spicfg);            	// Start driver.
  spiAcquireBus(&SPID1);                // Gain ownership of bus.

  while(!chThdShouldTerminateX()) 
  {
		pMotor->spiRxBuffer[0] = 0;
		spiSelect(&SPID1);                  // Select slave.

		while(SPID1.state != SPI_READY) 
    { 
      // do nothing 
    }   
		
    spiReceive(&SPID1, 1, pMotor->spiRxBuffer); // Receive 1 frame (16 bits).
		spiUnselect(&SPID1);                // Unselect slave.

		pMotor->position = 0x3FFF & pMotor->spiRxBuffer[0];
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
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
static void pwmPeriodCallback(PWMDriver *pwmp) 
{
  (void)pwmp;
  // TODO: WOW! This is boring now...
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
  pMotor->phaseShift = LUT_SIZE/3;
  pMotor->u = 0;
  pMotor->v = pMotor->u + pMotor->phaseShift;
  pMotor->w = pMotor->v + pMotor->phaseShift;
  pMotor->isOpenLoop = true;
  pMotor->isStarted = false;
	
	//adcStart(&ADCD1, NULL); 
  //adcStartConversion(&ADCD1, &adcgrpcfg, pMotor->samples, ADC_GRP_BUF_DEPTH);

/*
	pMotor->p_spi_thread=chThdCreateStatic(
		wa_spiThread,
		sizeof(wa_spiThread),
		NORMALPRIO,
		spiThread,
		pMotor
	);
//*/

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
	pwmStart(&PWMD1,&pwmRwConfig);
  pwmEnablePeriodicNotification(&PWMD1);
	
	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pMotor->u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pMotor->v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pMotor->w));
	pMotor->isStarted = true;
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
  adcStopConversion(&ADCD1);
  adcStop(&ADCD1); 
	chThdTerminate(pMotor->pSpiThread);
	chThdWait(pMotor->pSpiThread);
}
