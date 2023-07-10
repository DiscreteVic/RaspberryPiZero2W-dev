
#include <bcm2835_dma.h>

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
#define img_size   0x12C000


#define dma_channel_0 0x3F007000

#define BUS_ADDR(x) (x + 0xC0000000)


uint32_t fBuff_add;

dma_block_t bk ;

void BCM2835_DMASetUp(){
    uint8_t i;
    uint32_t padd = new_location;
    for(i = 0; i < 4; i++){
        bk.ti         = (0x1U << 4) | (0x1U << 8);
        bk.src_ad     = BUS_ADDR((uint32_t)padd);
        bk.dest_ad    = BUS_ADDR((uint32_t)fBuff_add);
        bk.txfr_len   = img_size;
        bk.strd       = 0x0;
        bk.nxt_cb_ad  = 0x0;
        bk.dbg        = 0x0;  

        // ENABLE CHANNEL
        setWordRegister(dma_channel_0 + 0xFF0U, 1U);
        // Disable debug pause
        setWordRegister(dma_channel_0 , 1U << 29);
        BCM2835_TIMER_hard_waitms(1);

        //RESET
        setWordRegister(dma_channel_0, 0x80000000U);
        setWordRegister(dma_channel_0 + 4, BUS_ADDR((uint32_t)&bk));

        BCM2835_TIMER_hard_waitms(1);

        //Active
        setWordRegister(dma_channel_0, 0x1U);

        BCM2835_TIMER_hard_waitms(2000);
        padd += 0x708000;
    }


}