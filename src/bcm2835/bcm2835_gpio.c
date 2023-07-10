
#include <bcm2835_gpio.h>

uint8_t BCM2835_GPIO_configPin(uint8_t pin, uint16_t funct){ // TO DO ERROR WRITING same reg twice
	uint32_t tmpReg;
	uint8_t funSelRegOff = (pin / 10);
	uint32_t funSelRegAddr = BCM2835_GPIO_FUN_SEL_REG + (funSelRegOff * 0x04U);
	
	if(pin <= 53){
		tmpReg = getWordRegister(funSelRegAddr);
		tmpReg &= ~(((uint32_t)0b111) << ((pin - (10*funSelRegOff))*3));
		setWordRegister(funSelRegAddr, tmpReg |= ((uint32_t)funct) << ((pin - (10*funSelRegOff)))*3);
	}
	else{
		return 1;
	}
	return 0;
}

uint8_t BCM2835_GPIO_setPin(uint8_t pin){
	
	if(pin <= 31){
		setWordRegister(BCM2835_GPIO_OUT_SET0_REG, 0x1U << pin);
	}	
	else if(pin <= 53){
		setWordRegister(BCM2835_GPIO_OUT_SET1_REG, 0x1U << (pin - 31));
	}
	else{
		return 1;
	}
	return 0;
	
}

uint8_t BCM2835_GPIO_clearPin(uint8_t pin){
	
	if(pin <= 31){
		setWordRegister(BCM2835_GPIO_OUT_CLR0_REG, 0x1U << pin);
	}	
	else if(pin <= 53){
		setWordRegister(BCM2835_GPIO_OUT_CLR1_REG, 0x1U << (pin - 31));
	}
	else{
		return 1;
	}
	return 0;
	
	
}
