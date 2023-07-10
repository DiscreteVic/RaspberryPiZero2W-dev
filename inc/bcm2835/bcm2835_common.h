#ifndef BCM2835_COMMON
#define BCM2835_COMMON

#include <bcm2835_common.h>
#include <common.h>

#define BCM2835_PERIPHERAL_PHYSICAL_BASE    0x3F000000U //
#define BCM2835_PERIPHERAL_BUS_BASE         0x7E000000U

#define BCM2835_PERIPHERALS_BASE_ADDR       BCM2835_PERIPHERAL_PHYSICAL_BASE


#define BCM2835_GPFSELx_BASE_ADDR			BCM2835_PERIPHERALS_BASE_ADDR + 0x00200000U
#define BCM2835_GPFSEL0			            BCM2835_GPFSELx_BASE_ADDR + 0x00U
#define BCM2835_GPFSEL1			            BCM2835_GPFSELx_BASE_ADDR + 0x04U

#define SPI_BASE_ADDR               BCM2835_PERIPHERALS_BASE_ADDR + 0x00204000U
#define SPI_CS_REG                  SPI_BASE_ADDR + 0x00U
#define SPI_FIFO_REG                SPI_BASE_ADDR + 0x04U
#define SPI_CLK_REG                 SPI_BASE_ADDR + 0x08U
#define SPI_DLEN_REG                SPI_BASE_ADDR + 0x0CU
#define SPI_LTOH_REG                SPI_BASE_ADDR + 0x10U
#define SPI_DC_REG                  SPI_BASE_ADDR + 0x14U

void setWordRegister(uint32_t addr, uint32_t value);
uint32_t getWordRegister(uint32_t addr);


#endif 