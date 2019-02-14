#ifndef _BLDCMotor_H_
#define _BLDCMotor_H_

#include "ch.h"
#include "hal.h"

#include "sin_lut.h"
#include <unistd.h>

#define THREAD_SIZE	(1<<7)
#define ENCODER_MAX (1<<14) - 1

/**
 *
 */
#define STEPS			LUT_SIZE 
#define SKIP      1

#define PWM_TIMER_FREQ	1e6  /// Hz
#define PWM_FREQ				10e3 /// periods per sec
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

// TODO: define SAMPLE_RATE
//#define SAMPLE_RATE

/// PWM signals
#define PWM_U			0U
#define PWM_V			1U
#define PWM_W			2U

#define ADC_GRP_NUM_CHANNELS  1
#define ADC_GRP_BUF_DEPTH     8

#define SPI_BUF_SIZE 2

typedef uint16_t dutycycle_t;

/**
 * @brief The structure that defines and characterizes
 * a motor and how it's being control
 */
typedef struct{
	sin_t u;              /// PWM signal
	sin_t v;              /// PWM signal
	sin_t w;              /// PWM signal
	
  sin_t const *pSinLut; /// pointer to the sin lut
  uint16_t periodCount;       /// period counter
  uint16_t position;
	
  bool isOpenLoop; // gross
  bool isStarted;

  // ADC conversion storage array
  adcsample_t samples[ADC_GRP_NUM_CHANNELS * ADC_GRP_BUF_DEPTH]; 
  
  // spy things	
  uint16_t spiRxBuffer[SPI_BUF_SIZE]; // receive buffer
	thread_t *pSpiThread;
} BLDCMotor;

/**
 * @brief Control structure used to configure the SPI driver
 *
 * GPIOA_SPI3_NSS is the pin used to initially select the SPI slave.
 * The mask for SPI Control Register 1 sets the frequency of data transfers
 * and sets the clock polarity.
 * The mask for SPI control Register 2 sets the size of the transfer buffer, 16 bits.
 *
 */
static const SPIConfig spicfg;
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
  0,
  0
};
//*/


extern THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
extern THD_FUNCTION(spiThread,arg);

extern void bldcInit(BLDCMotor *pMotor);
extern void bldcStart(BLDCMotor *pMotor);
extern void bldcStop(BLDCMotor *pMotor);
extern void bldcSetDutyCycle(uint8_t channel, dutycycle_t dc);
extern void bldcExit(BLDCMotor *pMotor);

#endif
