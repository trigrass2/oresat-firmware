#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "crc.h"
#include <string.h>

// FW update return codes
#define SUCCESS 0
#define ERR_HEADER_READ 1
#define ERR_HEADER_CRC_INVAL 2
#define ERR_SERIAL_READ 3
#define ERR_READ_SIZE 4
#define ERR_REREAD_SIZE 5
#define ERR_FW_CRC_INVAL 6

// default buffer size is size of flash page
#define BUF_SIZE STM32_FLASH_SECTOR_SIZE

// vector section will always take exactly 1 page
#define VECTOR_SECTION_SIZE BUF_SIZE

/* macros for converting raw addresses and flash offsets to flash sector */
// TODO should these have a bounds checking assertion?
#define ADDR_2_FLASH_SECTOR(x) (((x & ~(STM32_FLASH_SECTOR_SIZE - 1)) - FLASH_BASE) / STM32_FLASH_SECTOR_SIZE)
#define OFFSET_2_FLASH_SECTOR(x) ((x & ~(STM32_FLASH_SECTOR_SIZE - 1)) / STM32_FLASH_SECTOR_SIZE)

extern THD_WORKING_AREA(fw_update_wa, 0x4000);
extern THD_FUNCTION(fw_update, arg);

void crcInit(void);
void crcDisable(void);
unsigned int crc32_ongoing(uint8_t *b, int len);
unsigned int crc32_single(uint8_t *b, int len);
int doFWUpdate(void);

typedef struct
{
    unsigned int prog_crc;   // crc32 of fw image program
    unsigned vectors_crc;    // crc32 of fw image vector table
    int prog_size;           // size of fw image program section
    int vectors_size;        // size of fw image vectors section
    unsigned int flags;      // flags about fw image
    unsigned int header_crc; // crc of the above 12 bytes
} fw_header;


