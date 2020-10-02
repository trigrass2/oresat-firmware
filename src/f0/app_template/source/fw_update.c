#include "fw_update.h"

// pointers to sections
extern unsigned int __flash1_base__;
extern unsigned int __flash1_end__;
unsigned int flash1_base = (unsigned int)&__flash1_base__;
unsigned int flash1_end = (unsigned int)&__flash1_end__;
extern unsigned int __flash0_base__;
extern unsigned int __flash0_end__;
unsigned int flash0_base = (unsigned int)&__flash0_base__;
unsigned int flash0_end = (unsigned int)&__flash0_end__;

BaseSequentialStream *s = (BaseSequentialStream *)&SD2;
SerialDriver *ser = (SerialDriver *)&SD2;
BaseFlash *efl = (BaseFlash *)&EFLD1;

// FW update thread
THD_WORKING_AREA(fw_update_wa, 0x4000);
THD_FUNCTION(fw_update, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED, PAL_MODE_OUTPUT_PUSHPULL);

    while (1)
    {
        palToggleLine(LINE_LED);
        int err = doFWUpdate();
        if (err != SUCCESS)
            chprintf(s, "doFWUpdate returned error code: %d\n", err);
        else
            chprintf(s, "doFWUpdate suceeded!\n", err);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}

int doFWUpdate()
{
    unsigned int flash1_base_offset = flash1_base - FLASH_BASE;
    unsigned int flash1_end_offset = flash1_end - FLASH_BASE;
    unsigned int image_base_offset = flash1_base_offset;
    uint8_t buf[BUF_SIZE], vectors[BUF_SIZE];
    int n;
    int recv_size;
    fw_header header;
    unsigned int crc_read;

    chprintf(s, "waiting for FW update header\n");
    // wait for FW update header forever
    n = sdReadTimeout(ser, (uint8_t *)&header, sizeof(fw_header), TIME_INFINITE);
    if (n != sizeof(fw_header))
    {
        chprintf(s, "READ ERR: read %d bytes\n", n);
        return ERR_HEADER_READ;
    }

    chprintf(s, "FW Header: [PROG CRC:0x%x; VECT CRC:0x%x; PROG SIZE:%d; VECT SIZE:%d; FLAGS:0x%x; HEADER_CRC:0x%x]\n",
             header.prog_crc, header.vectors_crc, header.prog_size, header.vectors_size, header.flags, header.header_crc);

    // calculate the header crc by crcing the bytes of the header minus the header crc.
    // check it against expected
    unsigned int calc_header_crc = crc32_single((uint8_t *)&header, sizeof(fw_header) - sizeof(unsigned int));
    if (calc_header_crc != header.header_crc)
    {
        chprintf(s, "calculated header crc (%u) does match header crc (%u)\n", calc_header_crc, header.header_crc);
        return ERR_HEADER_CRC_INVAL;
    }

    chprintf(s, "reading vectors section\n");

    // zero the vectors buffer
    memset(vectors, 0, VECTOR_SECTION_SIZE);

    // read vectors section from serial into buffer
    n = sdReadTimeout(ser, vectors, VECTOR_SECTION_SIZE, TIME_MS2I(500));
    if (n < (int)VECTOR_SECTION_SIZE)
    {
        chprintf(s, "error reading vector section, expected %d but for %d\n", VECTOR_SECTION_SIZE, n);
        return ERR_SERIAL_READ;
    }

    // calculate the vectors section crc
    unsigned int vectors_crc = crc32_single(vectors, sizeof(vectors));
    if (vectors_crc != header.vectors_crc)
    {
        chprintf(s, "calculated vectors crc (%u) does match vectors crc (%u)\n", vectors_crc, header.vectors_crc);
        return ERR_FW_CRC_INVAL;
    }

    chprintf(s, "reading program section\n", n);
    for (recv_size = 0; recv_size < header.prog_size;)
    {
        // default to reading BUF_SIZE bytes
        int read_len = BUF_SIZE;

        // if there are less that BUF_SIZE bytes left, only read the remaining bytes
        if ((header.prog_size - recv_size) < (int)BUF_SIZE)
            read_len = header.prog_size - recv_size;

        // zero the buffer
        memset(buf, 0, BUF_SIZE);

        // read from serial into buffer
        n = sdReadTimeout(ser, buf, read_len, TIME_MS2I(500));
        if (n < read_len)
        {
            chprintf(s, "ERROR: expected %d but for %d\n", read_len, n);
            return ERR_SERIAL_READ;
        }

        recv_size += n;

        // TODO check error here
        // erase the page we are about to write
        int sector = OFFSET_2_FLASH_SECTOR(image_base_offset);
        flashStartEraseSector(efl, sector);
        flashWaitErase(efl);

        // write the page
        flashProgram(efl, image_base_offset, sizeof(buf), (uint8_t *)buf);

        image_base_offset += BUF_SIZE;
    }

    chprintf(s, "received image size: %d\n", recv_size);

    // check that the received size matches the header size
    if (recv_size != header.prog_size)
    {
        chprintf(s, "received image size (%d) does not match expected (%d)\n", recv_size, header.prog_size);
        return ERR_READ_SIZE;
    }

    n = 0;

    // initialize the CRC unit for a new, ongoing calculation
    crcInit();

    chprintf(s, "validating new FW image...\n", n);

    // read back the FW image and calculate the CRC
    for (unsigned int offset = flash1_base_offset; offset < flash1_base_offset + header.prog_size; offset += sizeof(buf))
    {
        // default to reading BUF_SIZE bytes
        int read_len = BUF_SIZE;

        // if there are less that BUF_SIZE bytes left in the image, get the correct read length
        if (((flash1_base_offset + header.prog_size) - offset) < BUF_SIZE)
            read_len = (flash1_base_offset + header.prog_size) - offset;

        // TODO check error
        // read the bytes from flash
        flashRead(efl, offset, read_len, (uint8_t *)buf);

        // CRC the bytes we read
        crc_read = crc32_ongoing(buf, read_len);

        n += read_len;
    }

    // disable CRC unit
    crcDisable();

    // check read size
    if (n != header.prog_size)
    {
        chprintf(s, "read len (%d) does not match expected (%d)\n", n, header.prog_size);
        return ERR_REREAD_SIZE;
    }

    // check CRC of read FW image
    if (crc_read != header.prog_crc)
    {
        chprintf(s, "read CRC (%u) does not match expected (%u)\n", crc_read, header.prog_crc);
        return ERR_FW_CRC_INVAL;
    }

    return SUCCESS;
}
