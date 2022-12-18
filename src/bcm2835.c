
#include "bcm2835.h"

// BARRIERS NOT SET - TO DO
void setWordRegister(uint32_t addr, uint32_t value){
    *((volatile uint32_t*)addr) = (uint32_t)value;
}

uint32_t getWordRegister(uint32_t addr){
    return *((volatile uint32_t*)addr);
}

uint8_t BCM2835_configGPIOPin(uint8_t pin, uint16_t funct){ // TO DO ERROR WRITING same reg twice
	uint32_t tmpReg;
	uint8_t funSelRegOff = (pin / 10);
	uint8_t funSelReg = funSelRegOff * 0x04U;
	uint32_t funSelRegAddr = GPIO_FUN_SEL_REG + funSelReg;
	
	if(pin <= 53){
		tmpReg = getWordRegister(funSelRegAddr);
		tmpReg &= !(((uint32_t)0b111) << ((pin - (10*funSelRegOff))*3));
		setWordRegister(funSelRegAddr, tmpReg |= ((uint32_t)funct) << ((pin - (10*funSelRegOff)))*3);
	}
	else{
		return 1;
	}
	return 0;
}

uint8_t BCM2835_setGPIOPin(uint8_t pin){
	
	if(pin <= 31){
		setWordRegister(GPIO_OUT_SET0_REG, 0x1U << pin);
	}	
	else if(pin <= 53){
		setWordRegister(GPIO_OUT_SET1_REG, 0x1U << (pin - 31));
	}
	else{
		return 1;
	}
	return 0;
	
}

uint8_t BCM2835_clearGPIOPin(uint8_t pin){
	
	if(pin <= 31){
		setWordRegister(GPIO_OUT_CLR0_REG, 0x1U << pin);
	}	
	else if(pin <= 53){
		setWordRegister(GPIO_OUT_CLR1_REG, 0x1U << (pin - 31));
	}
	else{
		return 1;
	}
	return 0;
	
	
}

void BCM2835_configUART(){
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

void BCM2835_sendByteUART(uint8_t b) {

    // Check if TX is available
	while ((getWordRegister(AUX_MU_LSR_REG) & 0x20) == 0);
    // Send
	setWordRegister(AUX_MU_IO_REG, (uint32_t)b);

}

uint8_t BCM2835_receiveByteUART(){

	uint8_t r;

    // Check if data is available
	while ((getWordRegister(AUX_MU_LSR_REG) & 0x1) == 0);

	r = (uint8_t)getWordRegister(AUX_MU_IO_REG);

	return r;

}


 void __attribute__((optimize(0)))  BCM2835_soft_waitms(uint32_t milis){
// void  BCM2835_soft_waitms(uint32_t milis){
	//CONSTANT VALUE OBTAINED EXPERIMENTALLY
	uint32_t i, j;

	for(j=milis; j > 0; j--){
		for(i=1916; i > 0; i--){
		}
	}

}