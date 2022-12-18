

#include "bcm2835.h"

#define BCM2835_SPI0_BASE 0x3F204000

void main(void) {
	

	//BCM2835_configGPIOPin(11,GPIO_FUN_OUT);
	//BCM2835_setGPIOPin(11);
	//BCM2835_soft_waitms(5);
	//BCM2835_clearGPIOPin(11);
    //configUART();

	// BEGIN
		// SET ALT0 PIN
		setWordRegister(GPIO_FUN_SEL_REG, 0x24000000);
		setWordRegister(GPIO_FUN_SEL_REG + 0x4U, 0x00000024);
    	// Set SPI CS
		setWordRegister(BCM2835_SPI0_BASE, 0);

		// Clear RX and RX fifo
		setWordRegister(BCM2835_SPI0_BASE, 0x00000030);

	// SET BIT ORDER

	// SET DATA MODE
		// Mode 0, CPOL & CPHA = 0
		setWordRegister(BCM2835_SPI0_BASE, 0x00000000);
	// SET CLOCK DIVIDER
		setWordRegister(BCM2835_SPI0_BASE+0x8, 0x00000000);
	// CHIP SELECT
		setWordRegister(BCM2835_SPI0_BASE, 0x00000000);
	// SET CHIP SELECT POLARITY
		setWordRegister(BCM2835_SPI0_BASE, 0x00000000);
	// TRANSFER

		// Clear RX and RX fifo
		setWordRegister(BCM2835_SPI0_BASE, 0x00000030);
		// SET TA
		setWordRegister(BCM2835_SPI0_BASE, 0x00000080);
		
		//WRITE FIFO
		setWordRegister(BCM2835_SPI0_BASE+0x4, 0x5A);

		//READ FIFO

		//UNSET TA
		setWordRegister(BCM2835_SPI0_BASE, 0x00000000);






	//setWordRegister(0xA000, 0x00000080);
/*
	sendByteUART('H');
	sendByteUART('o');
	sendByteUART('l');
	sendByteUART('a');
	sendByteUART(' ');
	sendByteUART('M');
	sendByteUART('U');
	sendByteUART('N');
	sendByteUART('D');
	sendByteUART('O');
	sendByteUART('!');
*/
	while (1);

}