#include "blink.h"
#include "chprintf.h"

extern unsigned int __flash1_base__;
extern unsigned int __flash1_end__;
unsigned int flash1_base = (unsigned int)&__flash1_base__;
unsigned int flash1_end = (unsigned int)&__flash1_end__;


BaseSequentialStream* s = (BaseSequentialStream*)&SD2;
BaseFlash* efl = (BaseFlash*)&EFLD1;

/* macros for converting raw addresses and flash offsets to flash sector */
// TODO should these have a bounds checking assertion?
#define ADDR_2_FLASH_SECTOR(x) (((x & ~(STM32_FLASH_SECTOR_SIZE - 1)) - FLASH_BASE) / STM32_FLASH_SECTOR_SIZE)
#define OFFSET_2_FLASH_SECTOR(x) ((x & ~(STM32_FLASH_SECTOR_SIZE - 1)) / STM32_FLASH_SECTOR_SIZE)

/* Example blinker thread */
THD_WORKING_AREA(blink_wa, 0x800);
THD_FUNCTION(blink, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED, PAL_MODE_OUTPUT_PUSHPULL);

    chprintf(s, "\n\n\n");
    chprintf(s, "flash1 base: 0x%x\n", flash1_base);
    chprintf(s, "flash1 end: 0x%x\n", flash1_end);

    #define BUF_SIZE 256
    int buf[BUF_SIZE];
    unsigned int flash1_base_offset = flash1_base - FLASH_BASE;
    unsigned int flash1_end_offset = flash1_end - FLASH_BASE;

    // erase all sectors in flash1
    for (unsigned int sector_addr = flash1_base; sector_addr < flash1_end; sector_addr += STM32_FLASH_SECTOR_SIZE)
    {
        int sector = ADDR_2_FLASH_SECTOR(sector_addr);
        chprintf(s, "erasing sector: %d\n", sector);
        flashStartEraseSector(efl, sector);
        flashWaitErase(efl);
    }

    // program all of flash1 with an incrementing calue
    int val = 0;
    for (unsigned int offset = flash1_base_offset ; offset < flash1_end_offset; offset += sizeof(buf)) 
    {
        // fill up a buffer with our running counter
        for( int i = 0 ; i < BUF_SIZE ; i++) 
            buf[i] = val++;

        chprintf(s, "programming 0x%x...\n", offset);
        flashProgram(efl, offset, sizeof(buf), (uint8_t*)buf);
    }

    // read back and print flash1
    for (unsigned int offset = flash1_base_offset ; offset < flash1_end_offset; offset += sizeof(buf))
    {
        chprintf(s, "reading 0x%x\n", offset);
        palToggleLine(LINE_LED);
        flashRead(efl, offset, sizeof(buf), (uint8_t*)buf);
        
        for(int i = 0 ; i < BUF_SIZE ; i++)
            chprintf(s, "0x%x: 0x%x\n", offset+i, buf[i]);
        
    }

    while (!chThdShouldTerminateX())
    {
        chprintf(s, ".");
        palToggleLine(LINE_LED);
        chThdSleepMilliseconds(1000);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
