
#include <bcm2835_uart.h>

void BCM2835_UART_config(){
	uint32_t r;
    // UART1
    // Enable UART
	r = getWordRegister(BCM2835_AUXENB_REG);
	r |= 1;
	setWordRegister(BCM2835_AUXENB_REG, r);
    // Set 8-bits data
	setWordRegister(BCM2835_AUX_MU_LCR_REG, 3);

    // Disable interrupts
	setWordRegister(BCM2835_AUX_MU_IER_REG, 0);

    // Clear port
	setWordRegister(BCM2835_AUX_MU_IIR_REG, 0x6);

    // Set Baudrate -> 115200 bps
	setWordRegister(BCM2835_AUX_MU_BAUD, 270);

    // Configure GPIO to UART
	r = getWordRegister(BCM2835_GPFSEL1);
	    // Reset GPIO pins
	r &= !((7<<12)|(7<<15));
	    // Set ALT5
	r |= (2 <<12)|(2<<15);
	setWordRegister(BCM2835_GPFSEL1, r);

    // Enable Port
	r = getWordRegister(BCM2835_AUX_MU_CNTL_REG);
	r |= 0x3;
	setWordRegister(BCM2835_AUX_MU_CNTL_REG, r);
}

void BCM2835_UART_sendByte(uint8_t b) {

    // Check if TX is available
	while ((getWordRegister(BCM2835_AUX_MU_LSR_REG) & 0x20) == 0);
    // Send
	setWordRegister(BCM2835_AUX_MU_IO_REG, (uint32_t)b);

}

void BCM2835_UART_printString(uint8_t *arr) {
	uint8_t i;

	for(i = 0; arr[i] != '\0'; i++){
		BCM2835_UART_sendByte(arr[i]);
	}


}

void BCM2835_UARTPrintRegister(uint32_t reg) {
	
	uint8_t i;

	for(i = 32; i > 0; i-=4){
		if(((uint8_t)(reg >> (i-4)) & 0xFU) < 0xAU){
			BCM2835_UART_sendByte(((uint8_t)(reg >> (i-4)) & 0xFU) + 0x30U);
		}
		else{
			BCM2835_UART_sendByte(((uint8_t)(reg >> (i-4)) & 0xFU) + 0x37U);
		}
	}


}

uint8_t BCM2835_UARTReceiveByte(){

	uint8_t r;

    // Check if data is available
	while ((getWordRegister(BCM2835_AUX_MU_LSR_REG) & 0x1) == 0);

	r = (uint8_t)getWordRegister(BCM2835_AUX_MU_IO_REG);

	return r;

}

