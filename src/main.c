

#include <bcm2835_uart.h>
#include <bcm2835_timer.h>
#include <bcm2835_video.h>
#include <bcm2835_dma.h>



uint32_t img = 0xE004;
uint32_t pimg = 0x60000;
uint32_t pixs, rgb;
uint32_t pix, r, g, b;

uint8_t multiplier = 16;


void main(void) {
    BCM2835_UART_config();
    BCM2835_VIDEO_init();
    BCM2835_VIDEO_blackScreen();
    uint16_t i, j;
    BCM2835_UART_printString((uint8_t *)"Start\n");
    uint8_t k;
    for(k = 0; k < 4; k++){

        for(i = 0; i < 480; i++){

            for(j = 0; j < 640; j+=4){
                pixs = getWordRegister(img);

                pix = pixs & 0xFFU;
                r = ((pix & 0xE0U) >> 5)*multiplier;
                g = ((pix & 0x1CU) >> 2)*multiplier;
                b = (pix & 0x3U)*multiplier;
                rgb = (r << 16 | g << 8 | b);
                BCM2835_VIDEO_setCodifiedImg(j,i,rgb,pimg);
                //BCM2835_videoDrawPixel(j,i,rgb);
                pix = pixs & 0xFFU;
                r = ((pix & 0xE0U) >> 5)*multiplier;
                g = ((pix & 0x1CU) >> 2)*multiplier;
                b = (pix & 0x3U)*multiplier;
                rgb = (r << 16 | g << 8 | b);
                BCM2835_VIDEO_setCodifiedImg(j + 1,i,rgb,pimg);
                //BCM2835_videoDrawPixel(j + 1,i,rgb);

                pix = pixs & 0xFFU;
                r = ((pix & 0xE0U) >> 5)*multiplier;
                g = ((pix & 0x1CU) >> 2)*multiplier;
                b = (pix & 0x3U)*multiplier;
                rgb = (r << 16 | g << 8 | b);
                BCM2835_VIDEO_setCodifiedImg(j + 2,i,rgb,pimg);
                //BCM2835_videoDrawPixel(j + 2,i,rgb);

                pix = pixs & 0xFFU;
                r = ((pix & 0xE0U) >> 5)*multiplier;
                g = ((pix & 0x1CU) >> 2)*multiplier;
                b = (pix & 0x3U)*multiplier;
                rgb = (r << 16 | g << 8 | b);
                BCM2835_VIDEO_setCodifiedImg(j + 3,i,rgb,pimg);
                //BCM2835_videoDrawPixel(j + 3,i,rgb);


                img+=4;
            }

        }
        pimg += 0x708000;
        img = 0xE004+0x4b000*(k+1);
    }

    BCM2835_UART_printString((uint8_t *)"LOADED ");
    fBuff_add = BCM2835_VIDEO_getFrameBuffAdd();
    
    BCM2835_DMASetUp();


    BCM2835_TIMER_hard_waitms(5000);
    //BCM2835_videoBlackScreen();
    BCM2835_UART_printString((uint8_t *)"\nIMG ");
	while (1);

}