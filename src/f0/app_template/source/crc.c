#include "crc.h"

void crcInit()
{
    // enable CRC clock
    // TODO do we need to wait
    // TODO not sure about the arg here
    rccEnableCRC(1); // TODO disable

    // reset CRC unit, init value defaults to 0xffffffff
    CRC->CR |= 0x01;
}

void crcDisable()
{
    // disable the CRC clock
    rccDisableCRC();
}

unsigned int crc32_single(uint8_t *b, int len)
{
    // enable CRC clock
    // TODO do we need to wait
    // TODO not sure about the arg here
    rccEnableCRC(1);

    // reset CRC unit, init value defaults to 0xffffffff
    CRC->CR |= 0x01;

    // write the buffer into the CRC data reg, 1 byte at a time.
    // TODO we could optimize this to write 4 byte words, but
    // then we need to handle unaligned buffers
    for (int i = 0; i < len; i++)
        STRB(CRC->DR, b[i]);

    // the datasheet specifies 1 AHB bus clock cycle of compute time
    // for a single byte CRC calculation, so insert a nop.
    asm("nop");

    // read the CRC from the data register
    unsigned int crc = CRC->DR;

    // disable the CRC clock
    rccDisableCRC();

    return crc;
}

unsigned int crc32_ongoing(uint8_t *b, int len)
{
    // write the buffer into the CRC data reg, 1 byte at a time.
    // TODO we could optimize this to write 4 byte words, but
    // then we need to handle unaligned buffers
    for (int i = 0; i < len; i++)
        STRB(CRC->DR, b[i]);

    // the datasheet specifies 1 AHB bus clock cycle of compute time
    // for a single byte CRC calculation, so insert a nop.
    asm("nop");

    // read the CRC from the data register
    unsigned int crc = CRC->DR;

    return crc;
}
