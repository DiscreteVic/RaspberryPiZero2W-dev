
#include "bcm2835.h"

void setWordRegister(uint32_t addr, uint32_t value){
    *((volatile uint32_t*)addr) = (uint32_t)value;
}

uint32_t getWordRegister(uint32_t addr){
    return *((volatile uint32_t*)addr);
}

void configUART(){
	uint32_t r;
    // UART1
    // Enable UART
	r = getWordRegister(AUXENB_REG);
	r |= 1;
	setWordRegister(AUXENB_REG, r);
    // Set 8-bits data
	setWordRegister(AUX_MU_LCR_REG, 3);

    // Disable interrupts
	setWordRegister(AUX_MU_IER_REG, 0);

    // Clear port
	setWordRegister(AUX_MU_IIR_REG, 0x6);

    // Set Baudrate -> 115200 bps
	setWordRegister(AUX_MU_BAUD, 270);

    // Configure GPIO to UART
	r = getWordRegister(GPFSEL1);
	    // Reset GPIO pins
	r &= !((7<<12)|(7<<15));
	    // Set ALT5
	r |= (2 <<12)|(2<<15);
	setWordRegister(GPFSEL1, r);

    // Enable Port
	r = getWordRegister(AUX_MU_CNTL_REG);
	r |= 0x3;
	setWordRegister(AUX_MU_CNTL_REG, r);
}

void sendByteUART(uint8_t b) {

    // Check if TX is available
	while ((getWordRegister(AUX_MU_LSR_REG) & 0x20) == 0);
    // Send
	setWordRegister(AUX_MU_IO_REG, (uint32_t)b);

}

uint8_t receiveByteUART(){

	uint8_t r;

    // Check if data is available
	while ((getWordRegister(AUX_MU_LSR_REG) & 0x1) == 0);

	r = (uint8_t)getWordRegister(AUX_MU_IO_REG);

	return r;

}