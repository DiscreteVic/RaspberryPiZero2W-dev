

#define PERIPHERAL_PHYSICAL_BASE    0x3F000000U //
#define PERIPHERAL_BUS_BASE         0x7E000000U

#define PERIPHERALS_BASE_ADDR       PERIPHERAL_PHYSICAL_BASE

#define AUX_BASE_ADDR               PERIPHERALS_BASE_ADDR + 0x00215000U
#define AUXENB_REG			        AUX_BASE_ADDR + 0x04U
#define AUX_MU_IO_REG	            AUX_BASE_ADDR + 0x40U
#define AUX_MU_IER_REG	            AUX_BASE_ADDR + 0x44U
#define AUX_MU_IIR_REG	            AUX_BASE_ADDR + 0x48U
#define AUX_MU_LCR_REG	            AUX_BASE_ADDR + 0x4CU
#define AUX_MU_MCR_REG	            AUX_BASE_ADDR + 0x50U
#define AUX_MU_LSR_REG	            AUX_BASE_ADDR + 0x54U
#define AUX_MU_MSR_REG	            AUX_BASE_ADDR + 0x58U
#define AUX_MU_CNTL_REG             AUX_BASE_ADDR + 0x60U
#define AUX_MU_STAT_REG             AUX_BASE_ADDR + 0x64U
#define AUX_MU_BAUD		            AUX_BASE_ADDR + 0x68U


#define GPFSELx_BASE_ADDR			PERIPHERALS_BASE_ADDR + 0x00200000U
#define GPFSEL1			            GPFSELx_BASE_ADDR + 0x04U

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;


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

void main(void) {

	sendByteUART('H');
	sendByteUART('o');
	sendByteUART('l');
	sendByteUART('a');
	sendByteUART(' ');
	sendByteUART('W');
	sendByteUART('o');
	sendByteUART('r');
	sendByteUART('l');
	sendByteUART('d');
	sendByteUART('!');

	while (1);

}