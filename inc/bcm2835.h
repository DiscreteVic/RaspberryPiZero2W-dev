#ifndef BCM2835
#define BCM2835

#include "common.h"

#define PERIPHERAL_PHYSICAL_BASE    0x3F000000U //
#define PERIPHERAL_BUS_BASE         0x7E000000U

#define PERIPHERALS_BASE_ADDR       PERIPHERAL_PHYSICAL_BASE

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


#define GPFSELx_BASE_ADDR			PERIPHERALS_BASE_ADDR + 0x00200000U
#define GPFSEL1			            GPFSELx_BASE_ADDR + 0x04U


void setWordRegister(uint32_t addr, uint32_t value);
uint32_t getWordRegister(uint32_t addr);
void configUART();
void sendByteUART(uint8_t b);
uint8_t receiveByteUART();


#endif 