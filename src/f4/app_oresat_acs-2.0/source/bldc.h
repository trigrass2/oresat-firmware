#ifndef _BLDCMotor_H_
#define _BLDCMotor_H_

#include "ch.h"
#include "hal.h"

#include "sin_lut.h"
#include <unistd.h>

#define THREAD_SIZE	(1<<7)

/**
 *
 */
//#define SCALE			100
#define STEPS			LUT_SIZE 
//#define STRETCH		1
#define SKIP      1

/// encoder has 14 bits of precision
#define ENCODER_MAX 1<<14
/// chunk amount is the number of times through
/// the LUT for 1 revolution of the reaction wheel
//#define CHUNK_AMOUNT 6
/// chunk size is the number
//#define CHUNK_SIZE 2730

#define PWM_TIMER_FREQ	48e6 /// Hz
#define PWM_FREQ				15e3 /// periods per sec
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

/// PWM signals
#define PWM_U			0U
#define PWM_V			1U
#define PWM_W			2U

#define ADC_GRP_NUM_CHANNELS  1
#define ADC_GRP_BUF_DEPTH     8 

/**
 * @brief The structure that defines and characterizes
 * a motor and how it's being control
 *
 */
typedef struct{
	uint16_t count;		/// period counter
	uint16_t steps;		/// number of steps in lut 
  uint16_t skip;
	dutycycle_t u;    /// PWM signal
	dutycycle_t v;    /// PWM signal
	dutycycle_t w;    /// PWM signal
	uint32_t phase_shift;		/// should be by 120 degrees 
  //uint16_t current_sin_u, next_sin_u,
  //         current_sin_v, next_sin_v,
  //         current_sin_w, next_sin_w;
	uint16_t position;				// motor position from encoder
	dutycycle_t const *pSinLut; // pointer to the sin lut
	uint16_t spi_rxbuf[2]; // receive buffer
	thread_t *p_spi_thread;
  bool isOpenLoop;
  bool isStarted;
  adcsample_t samples[ADC_GRP_NUM_CHANNELS * ADC_GRP_BUF_DEPTH]; // ADC conversion storage array
} BLDCMotor;

/**
 * @brief Control structure used to configure the SPI driver
 *
 * GPIOA_SPI1_NSS is the pin used to initially select the SPI slave.
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
	GPIOA_SPI1_NSS,                                       // Chip select port.
	SPI_CR1_BR_0|SPI_CR1_BR_1|SPI_CR1_BR_2|SPI_CR1_CPHA,  // SPI Ctrl Reg 1 mask.
	SPI_CR2_DS_0|SPI_CR2_DS_1|SPI_CR2_DS_2|SPI_CR2_DS_3,  // SPI Ctrl Reg 2 mask.
};
//*/

extern THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
extern THD_FUNCTION(spiThread,arg);

extern void bldcInit(BLDCMotor *pMotor);
extern void bldcStart(BLDCMotor *pMotor);
extern void bldcStop(BLDCMotor *pMotor);
extern void bldcSetDC(uint8_t channel,uint16_t dc);
extern void bldcExit(BLDCMotor *pMotor);

#endif
