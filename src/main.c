

#include "bcm2835.h"



void main(void) {
	uint32_t regTest;

    BCM2835_configUART();
	BCM2835_configGPIOPin(16, GPIO_FUN_OUT);

    BCM2835_setGPIOPin(16);

	BCM2835_hard_wait100us(10);

    BCM2835_clearGPIOPin(16);
    BCM2835_printArrayUART("END");
	


	while (1);

}