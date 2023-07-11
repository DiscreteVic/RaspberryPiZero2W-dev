
#include <bcm2835_dma.h>


uint8_t BCM2835_DMA_enableChannel(uint8_t dma_channel){

    if(dma_channel < 15U){
        // ENABLE CHANNEL
        setWordRegister(BCM2835_DMA_CHANNEL0 + 0xFF0U, (1U << dma_channel));
        return 0;
    }
    else{
        return 1;
    }
}

void BCM2835_DMA_configBlock(BCM2835_DMA_block_t* bk, uint32_t sAdd, uint32_t dAdd, uint32_t len){

    bk->ti         = BCM2835_DMA_TI_SRC_ADDR_INC | BCM2835_DMA_TI_DEST_ADDR_INC;
    bk->src_ad     = BCM2835_DMA_BUS_ADDR((uint32_t)sAdd);
    bk->dest_ad    = BCM2835_DMA_BUS_ADDR((uint32_t)dAdd);
    bk->txfr_len   = (uint32_t)len;
    bk->strd       = 0x0;
    bk->nxt_cb_ad  = 0x0;
    bk->dbg        = 0x0; 

}



uint8_t BCM2835_DMA_transferBlock(uint8_t dma_channel, BCM2835_DMA_block_t bk){

    uint32_t dmaChannelAddr;

    if(dma_channel > 15U){
        return 1;
    }

    dmaChannelAddr = BCM2835_DMA_CHANNEL0 + (0x100 * dma_channel);

    // Disable debug pause
    setWordRegister(dmaChannelAddr , 1U << 29);
    BCM2835_TIMER_hard_waitms(1);

    //RESET
    setWordRegister(dmaChannelAddr, 0x80000000U);
    setWordRegister(dmaChannelAddr + 4, BCM2835_DMA_BUS_ADDR((uint32_t)&bk));

    BCM2835_TIMER_hard_waitms(1);

    //Active
    setWordRegister(dmaChannelAddr, 0x1U);


    return 0;
}