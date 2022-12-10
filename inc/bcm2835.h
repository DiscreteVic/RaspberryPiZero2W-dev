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

#define GPIO_FUN_IN                0x000U
#define GPIO_FUN_OUT                 0x001U
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


void setWordRegister(uint32_t addr, uint32_t value);
uint32_t getWordRegister(uint32_t addr);

uint8_t BCM2835_configGPIOPin(uint8_t pin, uint8_t funct);

uint8_t BCM2835_setGPIOPin(uint8_t pin);

uint8_t BCM2835_clearGPIOPin(uint8_t pin);


void BCM2835_configUART();
void BCM2835_sendByteUART(uint8_t b);
uint8_t BCM2835_receiveByteUART();


#endif 