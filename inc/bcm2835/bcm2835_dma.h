#ifndef BCM2835_DMA
#define BCM2835_DMA

#include <common.h>

#include <bcm2835_common.h>
#include <bcm2835_timer.h>

#define BCM2835_DMA_CHANNEL0            0x3F007000
#define BCM2835_DMA_CHANNEL1            BCM2835_DMA_CHANNEL0 + 0x100U
#define BCM2835_DMA_CHANNEL2            BCM2835_DMA_CHANNEL0 + 0x200U
#define BCM2835_DMA_CHANNEL3            BCM2835_DMA_CHANNEL0 + 0x300U
#define BCM2835_DMA_CHANNEL4            BCM2835_DMA_CHANNEL0 + 0x400U
#define BCM2835_DMA_CHANNEL5            BCM2835_DMA_CHANNEL0 + 0x500U
#define BCM2835_DMA_CHANNEL6            BCM2835_DMA_CHANNEL0 + 0x600U
#define BCM2835_DMA_CHANNEL7            BCM2835_DMA_CHANNEL0 + 0x700U
#define BCM2835_DMA_CHANNEL8            BCM2835_DMA_CHANNEL0 + 0x800U
#define BCM2835_DMA_CHANNEL9            BCM2835_DMA_CHANNEL0 + 0x900U
#define BCM2835_DMA_CHANNEL10           BCM2835_DMA_CHANNEL0 + 0xA00U
#define BCM2835_DMA_CHANNEL11           BCM2835_DMA_CHANNEL0 + 0xB00U
#define BCM2835_DMA_CHANNEL12           BCM2835_DMA_CHANNEL0 + 0xC00U
#define BCM2835_DMA_CHANNEL13           BCM2835_DMA_CHANNEL0 + 0xD00U
#define BCM2835_DMA_CHANNEL14           BCM2835_DMA_CHANNEL0 + 0xE00U


#define BCM2835_DMA_TI_SRC_ADDR_INC     (0x1U << 8)
#define BCM2835_DMA_TI_DEST_ADDR_INC    (0x1U << 4)


typedef struct dma_block_t{
    uint32_t ti;
    uint32_t src_ad;
    uint32_t dest_ad;
    uint32_t txfr_len;
    uint32_t strd;
    uint32_t nxt_cb_ad;
    uint32_t dbg;
} BCM2835_DMA_block_t __attribute__ ((aligned (32)));

#define BCM2835_DMA_BUS_ADDR(x) (x + 0xC0000000)



uint8_t BCM2835_DMA_enableChannel(uint8_t dma_channel);

void BCM2835_DMA_configBlock(BCM2835_DMA_block_t* bk, uint32_t sAdd, uint32_t dAdd, uint32_t len);

uint8_t BCM2835_DMA_transferBlock(uint8_t dma_channel, BCM2835_DMA_block_t bk);



#endif 