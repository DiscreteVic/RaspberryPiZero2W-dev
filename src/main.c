

#include "bcm2835.h"

uint32_t img = 0xE004;
uint32_t pixs, rgb;
uint32_t pix, r, g, b;

uint8_t multiplier = 16;

void main(void) {
    BCM2835_configUART();
    BCM2835_videoInit();
    BCM2835_videoBlackScreen();
    uint16_t i, j;
    BCM2835_printStringUART((uint8_t *)"Start\n");
    for(i = 0; i < 427; i++){

        for(j = 0; j < 640; j+=4){
            pixs = getWordRegister(img);

            pix = pixs & 0xFFU;
            r = ((pix & 0xE0U) >> 5)*multiplier;
            g = ((pix & 0x1CU) >> 2)*multiplier;
            b = (pix & 0x3U)*multiplier;
            rgb = (r << 16 | g << 8 | b);
            BCM2835_videoDrawPixel(j,i,rgb);
            BCM2835_sendByteUART(0x5A);
            
            pix = pixs & 0xFFU;
            r = ((pix & 0xE0U) >> 5)*multiplier;
            g = ((pix & 0x1CU) >> 2)*multiplier;
            b = (pix & 0x3U)*multiplier;
            rgb = (r << 16 | g << 8 | b);
            BCM2835_videoDrawPixel(j + 1,i,rgb);

            pix = pixs & 0xFFU;
            r = ((pix & 0xE0U) >> 5)*multiplier;
            g = ((pix & 0x1CU) >> 2)*multiplier;
            b = (pix & 0x3U)*multiplier;
            rgb = (r << 16 | g << 8 | b);
            BCM2835_videoDrawPixel(j + 2,i,rgb);

            pix = pixs & 0xFFU;
            r = ((pix & 0xE0U) >> 5)*multiplier;
            g = ((pix & 0x1CU) >> 2)*multiplier;
            b = (pix & 0x3U)*multiplier;
            rgb = (r << 16 | g << 8 | b);
            BCM2835_videoDrawPixel(j + 3,i,rgb);


            img+=4;
            BCM2835_sendByteUART(0xFF);
        }
        BCM2835_sendByteUART(0xFF);

    }
    BCM2835_soft_waitms(5000);
    BCM2835_videoBlackScreen();
    BCM2835_printStringUART((uint8_t *)"\nIMG ");
	while (1);

}