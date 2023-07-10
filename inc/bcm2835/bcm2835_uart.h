#ifndef BCM2835_UART
#define BCM2835_UART

#include <common.h>

#include <bcm2835_common.h>


#define BCM2835_AUX_BASE_ADDR               BCM2835_PERIPHERALS_BASE_ADDR + 0x00215000U
#define BCM2835_AUXENB_REG			        BCM2835_AUX_BASE_ADDR + 0x04U
#define BCM2835_AUX_MU_IO_REG	            BCM2835_AUX_BASE_ADDR + 0x40U
#define BCM2835_AUX_MU_IER_REG	            BCM2835_AUX_BASE_ADDR + 0x44U
#define BCM2835_AUX_MU_IIR_REG	            BCM2835_AUX_BASE_ADDR + 0x48U
#define BCM2835_AUX_MU_LCR_REG	            BCM2835_AUX_BASE_ADDR + 0x4CU
#define BCM2835_AUX_MU_MCR_REG	            BCM2835_AUX_BASE_ADDR + 0x50U
#define BCM2835_AUX_MU_LSR_REG	            BCM2835_AUX_BASE_ADDR + 0x54U
#define BCM2835_AUX_MU_MSR_REG	            BCM2835_AUX_BASE_ADDR + 0x58U
#define BCM2835_AUX_MU_CNTL_REG             BCM2835_AUX_BASE_ADDR + 0x60U
#define BCM2835_AUX_MU_STAT_REG             BCM2835_AUX_BASE_ADDR + 0x64U
#define BCM2835_AUX_MU_BAUD		            BCM2835_AUX_BASE_ADDR + 0x68U

void BCM2835_UART_config();

void BCM2835_UART_sendByte(uint8_t b);

uint8_t BCM2835_UART_receiveByte();

void BCM2835_UART_printString(uint8_t *arr);

void BCM2835_UART_printRegister(uint32_t reg);


#endif 