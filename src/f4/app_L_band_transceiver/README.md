# C3 L band Transceiver Testing

Testing for the C3 L band transceiver subsystem.  This branch incorporates OreSat's AX5043 transceiver and Si4112 synthesizer evaluation boards to be used as an up/downconverter.  The AX5043 transceiver board is capable of operating in two ranges; 400 to 525 MHz and 800 to 1050 MHz.  It uses a 16.000000 MHz 1 ppm TCXO, and it's SYSCLK output provides the reference to the Si4112.  The Si4112 synthesizer board acts as the local oscillator for the up/downconverter and provides an output range of 685 to 954 MHz.  These boards are used in combination with a mixer, various filters, LNAs, amps, and power boards.