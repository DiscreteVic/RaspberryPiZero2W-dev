

#include "bcm2835.h"

typedef struct dma_block_t{
    uint32_t ti;
    uint32_t src_ad;
    uint32_t dest_ad;
    uint32_t txfr_len;
    uint32_t strd;
    uint32_t nxt_cb_ad;
    uint32_t dbg;
} dma_block_t __attribute__ ((aligned (32)));

#define old_location   0xE000
#define new_location   0x60000
#define img_size   0x10AE00


#define dma_channel_0 0x3F007000

#define BUS_ADDR(x) (x + 0xC0000000)


uint32_t fBuff_add;

dma_block_t bk ;

void BCM2835_DMASetUp(){

    bk.ti         = (0x1U << 4) | (0x1U << 8);
    bk.src_ad     = BUS_ADDR((uint32_t)new_location);
    bk.dest_ad    = BUS_ADDR((uint32_t)fBuff_add);
    bk.txfr_len   = img_size;
    bk.strd       = 0x0;
    bk.nxt_cb_ad  = 0x0;
    bk.dbg        = 0x0;  

    // ENABLE CHANNEL
    setWordRegister(dma_channel_0 + 0xFF0U, 1U);
    // Disable debug pause
    setWordRegister(dma_channel_0 , 1U << 29);
    BCM2835_hard_waitms(1);

    //RESET
    setWordRegister(dma_channel_0, 0x80000000U);
    setWordRegister(dma_channel_0 + 4, BUS_ADDR((uint32_t)&bk));

    BCM2835_hard_waitms(1);

    //Active
    setWordRegister(dma_channel_0, 0x1U);

}



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
            setCodifiedImg(j,i,rgb,0x60000);
            //BCM2835_videoDrawPixel(j,i,rgb);
            pix = pixs & 0xFFU;
            r = ((pix & 0xE0U) >> 5)*multiplier;
            g = ((pix & 0x1CU) >> 2)*multiplier;
            b = (pix & 0x3U)*multiplier;
            rgb = (r << 16 | g << 8 | b);
            setCodifiedImg(j + 1,i,rgb,0x60000);
            //BCM2835_videoDrawPixel(j + 1,i,rgb);

            pix = pixs & 0xFFU;
            r = ((pix & 0xE0U) >> 5)*multiplier;
            g = ((pix & 0x1CU) >> 2)*multiplier;
            b = (pix & 0x3U)*multiplier;
            rgb = (r << 16 | g << 8 | b);
            setCodifiedImg(j + 2,i,rgb,0x60000);
            //BCM2835_videoDrawPixel(j + 2,i,rgb);

            pix = pixs & 0xFFU;
            r = ((pix & 0xE0U) >> 5)*multiplier;
            g = ((pix & 0x1CU) >> 2)*multiplier;
            b = (pix & 0x3U)*multiplier;
            rgb = (r << 16 | g << 8 | b);
            setCodifiedImg(j + 3,i,rgb,0x60000);
            //BCM2835_videoDrawPixel(j + 3,i,rgb);


            img+=4;
        }
        BCM2835_sendByteUART(0xFF);

    }
    fBuff_add = BCM2835_getFrameBuffAdd();
    
    BCM2835_DMASetUp();


    BCM2835_hard_waitms(5000);
    //BCM2835_videoBlackScreen();
    BCM2835_printStringUART((uint8_t *)"\nIMG ");
	while (1);

}