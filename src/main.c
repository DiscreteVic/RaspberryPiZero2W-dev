

#include "bcm2835.h"

typedef struct dma_block_t{
    uint32_t ti;
    uint32_t src_ad;
    uint32_t dest_ad;
    uint32_t txfr_len;
    uint32_t strd;
    uint32_t nxt_cb_ad;
    uint32_t dbg;
} dma_block_t;

#define new_location   0x60000
#define old_location   0xE000
#define img_size   0x42B80


#define dma_channel_0 0x3F007000

//#define BUS_ADDR(x) ((x | 0x40000000) & ~0xC0000000)
#define BUS_ADDR(x) (x + 0xC0000000)

void main(void) {
    dma_block_t bk __attribute__ ((aligned (32)));
    BCM2835_configUART();
    BCM2835_printStringUART((uint8_t *)"Start\n");
    //BCM2835_printStringUART((uint8_t *)"Address: ");
    //BCM2835_printRegisterUART(adr);
    //BCM2835_printStringUART((uint8_t *)"\n");

    bk.ti         = (0x1U << 4) | (0x1U << 8);
    bk.src_ad     = BUS_ADDR((uint32_t)old_location);
    bk.dest_ad    = BUS_ADDR((uint32_t)new_location);
    bk.txfr_len   = img_size;
    bk.strd       = 0x0;
    bk.nxt_cb_ad  = 0x0;
    bk.dbg        = 0x0;  


    BCM2835_printStringUART((uint8_t *)"Old: ");
    BCM2835_printRegisterUART((uint32_t)getWordRegister((uint32_t)old_location));
    BCM2835_printStringUART((uint8_t *)"\n");
    BCM2835_printStringUART((uint8_t *)"New: ");
    BCM2835_printRegisterUART((uint32_t)getWordRegister((uint32_t)new_location));
    BCM2835_printStringUART((uint8_t *)"\n");
    
    BCM2835_printStringUART((uint8_t *)"A Status: ");
    BCM2835_printRegisterUART((uint32_t)getWordRegister(dma_channel_0));
    BCM2835_printStringUART((uint8_t *)"\n");

    // ENABLE CHANNEL
    setWordRegister(dma_channel_0 + 0xFF0U, 1U);
    // Disable debug pause
    setWordRegister(dma_channel_0 , 1U << 29);
    BCM2835_hard_waitms(5);

    BCM2835_printStringUART((uint8_t *)"BStatus: ");
    BCM2835_printRegisterUART((uint32_t)getWordRegister(dma_channel_0));
    BCM2835_printStringUART((uint8_t *)"\n");

    //RESET
    setWordRegister(dma_channel_0, 0x80000000U);
    setWordRegister(dma_channel_0 + 4, BUS_ADDR((uint32_t)&bk));

    BCM2835_hard_waitms(1);


    BCM2835_printStringUART((uint8_t *)"Old Addr: ");
    BCM2835_printRegisterUART((uint32_t)getWordRegister(dma_channel_0 + 4));
    BCM2835_printStringUART((uint8_t *)"\n");


    //Active
    setWordRegister(dma_channel_0, 0x1U);

    uint8_t i = 0;
    while (i <= 5)
    {
        BCM2835_printStringUART((uint8_t *)"C Status: ");
        BCM2835_printRegisterUART((uint32_t)getWordRegister(dma_channel_0));
        BCM2835_printStringUART((uint8_t *)"\n");
        BCM2835_hard_waitms(500);
        i++;
    }
    
    BCM2835_printStringUART((uint8_t *)"Addr: ");
    BCM2835_printRegisterUART((uint32_t)getWordRegister(dma_channel_0 + 4));
    BCM2835_printStringUART((uint8_t *)"\n");

    BCM2835_printStringUART((uint8_t *)"Old: ");
    BCM2835_printRegisterUART((uint32_t)getWordRegister((uint32_t)old_location));
    BCM2835_printStringUART((uint8_t *)"\n");
    BCM2835_printStringUART((uint8_t *)"New: ");
    BCM2835_printRegisterUART((uint32_t)getWordRegister((uint32_t)new_location));
    BCM2835_printStringUART((uint8_t *)"\n");
    

    BCM2835_hard_waitms(5000);
	while (1);

}