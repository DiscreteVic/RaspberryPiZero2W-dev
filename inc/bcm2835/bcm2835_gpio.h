#ifndef BCM2835_GPIO
#define BCM2835_GPIO

#include <common.h>

#include <bcm2835_common.h>


#define BCM2835_GPIO_BASE_ADDR              BCM2835_PERIPHERAL_PHYSICAL_BASE + 0x200000U
#define BCM2835_GPIO_FUN_SEL_REG            BCM2835_GPIO_BASE_ADDR + 0x00U
#define BCM2835_GPIO_OUT_SET0_REG           BCM2835_GPIO_BASE_ADDR + 0x1CU
#define BCM2835_GPIO_OUT_SET1_REG           BCM2835_GPIO_BASE_ADDR + 0x20U
#define BCM2835_GPIO_OUT_CLR0_REG           BCM2835_GPIO_BASE_ADDR + 0x28U
#define BCM2835_GPIO_OUT_CLR1_REG           BCM2835_GPIO_BASE_ADDR + 0x2CU

#define BCM2835_GPIO_FUN_IN                 0x000U
#define BCM2835_GPIO_FUN_OUT                0x001U
#define BCM2835_GPIO_FUN_ALT0               0x100U
#define BCM2835_GPIO_FUN_ALT1               0x101U
#define BCM2835_GPIO_FUN_ALT2               0x110U
#define BCM2835_GPIO_FUN_ALT3               0x111U
#define BCM2835_GPIO_FUN_ALT4               0x011U
#define BCM2835_GPIO_FUN_ALT5               0x010U



uint8_t BCM2835_GPIO_configPin(uint8_t pin, uint16_t funct);

uint8_t BCM2835_GPIO_setPin(uint8_t pin);

uint8_t BCM2835_GPIO_clearPin(uint8_t pin);


#endif 