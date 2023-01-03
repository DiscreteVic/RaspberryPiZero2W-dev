#ifndef BCM2835
#define BCM2835

#include "common.h"


#define PERIPHERAL_PHYSICAL_BASE    0x3F000000U //
#define PERIPHERAL_BUS_BASE         0x7E000000U

#define PERIPHERALS_BASE_ADDR       PERIPHERAL_PHYSICAL_BASE


#define GPIO_BASE_ADDR              PERIPHERAL_PHYSICAL_BASE + 0x200000U
#define GPIO_FUN_SEL_REG            GPIO_BASE_ADDR + 0x00U
#define GPIO_OUT_SET0_REG           GPIO_BASE_ADDR + 0x1CU
#define GPIO_OUT_SET1_REG           GPIO_BASE_ADDR + 0x20U
#define GPIO_OUT_CLR0_REG           GPIO_BASE_ADDR + 0x28U
#define GPIO_OUT_CLR1_REG           GPIO_BASE_ADDR + 0x2CU

#define GPIO_FUN_IN                 0x000U
#define GPIO_FUN_OUT                0x001U
#define GPIO_FUN_ALT0               0x100U
#define GPIO_FUN_ALT1               0x101U
#define GPIO_FUN_ALT2               0x110U
#define GPIO_FUN_ALT3               0x111U
#define GPIO_FUN_ALT4               0x011U
#define GPIO_FUN_ALT5               0x010U



#define AUX_BASE_ADDR               PERIPHERALS_BASE_ADDR + 0x00215000U
#define AUXENB_REG			        AUX_BASE_ADDR + 0x04U
#define AUX_MU_IO_REG	            AUX_BASE_ADDR + 0x40U
#define AUX_MU_IER_REG	            AUX_BASE_ADDR + 0x44U
#define AUX_MU_IIR_REG	            AUX_BASE_ADDR + 0x48U
#define AUX_MU_LCR_REG	            AUX_BASE_ADDR + 0x4CU
#define AUX_MU_MCR_REG	            AUX_BASE_ADDR + 0x50U
#define AUX_MU_LSR_REG	            AUX_BASE_ADDR + 0x54U
#define AUX_MU_MSR_REG	            AUX_BASE_ADDR + 0x58U
#define AUX_MU_CNTL_REG             AUX_BASE_ADDR + 0x60U
#define AUX_MU_STAT_REG             AUX_BASE_ADDR + 0x64U
#define AUX_MU_BAUD		            AUX_BASE_ADDR + 0x68U


#define SPI_BASE_ADDR               PERIPHERALS_BASE_ADDR + 0x00204000U
#define SPI_CS_REG                  SPI_BASE_ADDR + 0x00U
#define SPI_FIFO_REG                SPI_BASE_ADDR + 0x04U
#define SPI_CLK_REG                 SPI_BASE_ADDR + 0x08U
#define SPI_DLEN_REG                SPI_BASE_ADDR + 0x0CU
#define SPI_LTOH_REG                SPI_BASE_ADDR + 0x10U
#define SPI_DC_REG                  SPI_BASE_ADDR + 0x14U



#define GPFSELx_BASE_ADDR			PERIPHERALS_BASE_ADDR + 0x00200000U
#define GPFSEL0			            GPFSELx_BASE_ADDR + 0x00U
#define GPFSEL1			            GPFSELx_BASE_ADDR + 0x04U


#define SYS_TIM_BASE_ADDR           PERIPHERALS_BASE_ADDR + 0x00003000U 
#define SYS_TIM_CS                  SYS_TIM_BASE_ADDR + 0x0U
#define SYS_TIM_CLO                 SYS_TIM_BASE_ADDR + 0x4U
#define SYS_TIM_CHI                 SYS_TIM_BASE_ADDR + 0x8U
#define SYS_TIM_C0                  SYS_TIM_BASE_ADDR + 0xCU
#define SYS_TIM_C1                  SYS_TIM_BASE_ADDR + 0x10U
#define SYS_TIM_C2                  SYS_TIM_BASE_ADDR + 0x14U
#define SYS_TIM_C3                  SYS_TIM_BASE_ADDR + 0x18U


#define MAILBOX_BASE                    PERIPHERALS_BASE_ADDR + 0xB880U
#define MAILBOX_READ                    MAILBOX_BASE + 0x00U 
#define MAILBOX_STATUS                  MAILBOX_BASE + 0x18U
#define MAILBOX_WRITE                   MAILBOX_BASE + 0x20U 
#define MAILBOX_PROPERTY_CHANNEL        8u
#define MAILBOX_FRAMEBUFFER_CHANNEL     1U
#define MAILBOX_FULL                    0x80000000U
#define MAILBOX_EMPTY                   0x40000000U
#define MAILBOX_RESPONSE_NOERROR        0x80000000U

#define MAILBOX_TAGS_NUM            7U
#define MAILBOX_TAG_BUFF_SIZE       32U //Tags with their elements
#define MAILBOX_TAG_ID_SETPHYWH     0x48003 
#define MAILBOX_TAG_ID_SETVIRWH     0x48004 
#define MAILBOX_TAG_ID_SETDPTH      0x48005 
#define MAILBOX_TAG_ID_SETPIXORD    0x48006 
#define MAILBOX_TAG_ID_SETVIROFFS   0x48009 
#define MAILBOX_TAG_ID_ALLBUFF      0x40001 
#define MAILBOX_TAG_ID_GETPTCH      0x40008 
#define MAILBOX_TAG_ID_BLNKSCR      0x40002 
#define MAILBOX_TAG_REQUEST         0U
#define MAILBOX_TAG_LAST            0U

#define VIDEO_SCREEN_W                    640U
#define VIDEO_SCREEN_H                    480U

void setWordRegister(uint32_t addr, uint32_t value);
uint32_t getWordRegister(uint32_t addr);

uint8_t BCM2835_configGPIOPin(uint8_t pin, uint16_t funct);

uint8_t BCM2835_setGPIOPin(uint8_t pin);

uint8_t BCM2835_clearGPIOPin(uint8_t pin);

void BCM2835_configUART();

void BCM2835_sendByteUART(uint8_t b);

uint8_t BCM2835_receiveByteUART();

void BCM2835_printStringUART(uint8_t *arr);

void BCM2835_printRegisterUART(uint32_t reg);

void BCM2835_soft_waitms(uint32_t milis);

void BCM2835_hard_wait100us(uint32_t hund_us);

void BCM2835_hard_waitms(uint32_t milis);

uint32_t BCM2835_timerGetTimestamp();

bool BCM2835_mailboxCall(uint8_t channel);

void BCM2835_videoInit();

void BCM2835_videoDrawPixel(uint32_t x, uint32_t y, uint32_t attr);

void BCM2835_videoBlackScreen();

void BCM2835_videoColorScreen(uint32_t col);

#endif 