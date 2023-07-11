

#include <bcm2835_uart.h>
#include <bcm2835_timer.h>
#include <bcm2835_video.h>
#include <bcm2835_dma.h>

#define old_location    0xE004
#define new_location   0x60000
#define img_size   0x10AE00



uint32_t img = old_location;
uint32_t pimg = new_location;
uint32_t pixs, rgb;
uint32_t pix, r, g, b;

uint8_t multiplier = 16;

#define N_IMG       4

BCM2835_DMA_block_t bk;

uint32_t fBuff_add;

void main(void) {
    BCM2835_UART_config();
    BCM2835_VIDEO_init();
    BCM2835_VIDEO_blackScreen();
    uint16_t i, j;
    BCM2835_UART_printString((uint8_t *)"Start\n");
    uint8_t k;
    uint32_t img_off = 0;
    for(k = 0; k < N_IMG; k++){

        BCM2835_UART_printString((uint8_t *)"Image ");
        BCM2835_UART_printWord(k);
        BCM2835_UART_printString((uint8_t *)": ");
        BCM2835_UART_printWord(pimg);
        BCM2835_UART_printString((uint8_t *)": ");
        BCM2835_UART_printWord(img+img_off);
        BCM2835_UART_printString((uint8_t *)"\n");
        for(i = 0; i < 480; i++){

            for(j = 0; j < 640; j+=4){
                pixs = getWordRegister(img+img_off);

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


                img_off+=4;
            }

        }

        BCM2835_UART_printString((uint8_t *)"END: ");
        BCM2835_UART_printWord(img_off);
        BCM2835_UART_printString((uint8_t *)"\n");
        img_off=0;
        pimg += 0x708000;
        img += 0x4b000;
    }

    BCM2835_UART_printString((uint8_t *)"LOADED ");
    fBuff_add = BCM2835_VIDEO_getFrameBuffAdd();
    
    BCM2835_DMA_enableChannel(0);
    uint8_t l = 0;
    uint32_t imgAddr = new_location;
    for(l = 0 ; l<N_IMG ; l++){
        BCM2835_UART_printString((uint8_t *)"Image ");
        BCM2835_UART_printWord(l);
        BCM2835_UART_printString((uint8_t *)": ");
        BCM2835_UART_printWord(imgAddr);
        BCM2835_UART_printString((uint8_t *)"\n");

        BCM2835_DMA_configBlock(&bk, imgAddr, fBuff_add, img_size);
        BCM2835_DMA_transferBlock(0, bk);
        imgAddr += 0x708000;
        BCM2835_TIMER_hard_waitms(1000);
    }


    BCM2835_TIMER_hard_waitms(5000);
    
    BCM2835_UART_printString((uint8_t *)"\nIMG ");
	while (1);

}