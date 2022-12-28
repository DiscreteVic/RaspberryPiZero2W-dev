

#include "bcm2835.h"
#include <stdio.h>

#define BCM2835_SPI0_BASE 0x3F204000

void main(void) {
	
	uint32_t regTest;

    BCM2835_configUART();
	uint8_t i;
	for(i = 0; i < 10; i++){
		regTest = getWordRegister(SYS_TIM_CLO);
    	BCM2835_printRegisterUART(regTest);
    	BCM2835_printArrayUART("\n");
	}


	while (1);

}