

#include "bcm2835.h"


void main(void) {
    uint32_t ta,tb;


    BCM2835_configUART();
    BCM2835_videoInit();

    BCM2835_videoDrawPixel(200,200,0xAA00AAU);
    
    BCM2835_hard_waitms(2000);
    BCM2835_videoDrawPixel(400,400,0xAA00AAU);
    BCM2835_hard_waitms(2000);
    BCM2835_videoBlackScreen();
	while (1);

}