#include "ch.h"
#include "hal.h"

// STRB: macro to ensure an assignment compiles to a 'strb'
// (store byte) instruction. This is needed doing single
// byte CRC transactions
// TODO will this always compile to strb?
#define STRB(d, s) *(uint8_t *)&d = s;

unsigned int crc32_single(uint8_t *b, int len);
unsigned int crc32_ongoing(uint8_t *b, int len);
void crcInit(void);
void crcDisable(void);
