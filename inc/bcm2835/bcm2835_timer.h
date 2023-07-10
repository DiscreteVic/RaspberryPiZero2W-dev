#ifndef BCM2835_TIMER
#define BCM2835_TIMER

#include <common.h>

#include <bcm2835_common.h>


#define BCM2835_SYS_TIM_BASE_ADDR           BCM2835_PERIPHERALS_BASE_ADDR + 0x00003000U 
#define BCM2835_SYS_TIM_CS                  BCM2835_SYS_TIM_BASE_ADDR + 0x0U
#define BCM2835_SYS_TIM_CLO                 BCM2835_SYS_TIM_BASE_ADDR + 0x4U
#define BCM2835_SYS_TIM_CHI                 BCM2835_SYS_TIM_BASE_ADDR + 0x8U
#define BCM2835_SYS_TIM_C0                  BCM2835_SYS_TIM_BASE_ADDR + 0xCU
#define BCM2835_SYS_TIM_C1                  BCM2835_SYS_TIM_BASE_ADDR + 0x10U
#define BCM2835_SYS_TIM_C2                  BCM2835_SYS_TIM_BASE_ADDR + 0x14U
#define BCM2835_SYS_TIM_C3                  BCM2835_SYS_TIM_BASE_ADDR + 0x18U


void BCM2835_TIMER_soft_waitms(uint32_t milis);

void BCM2835_TIMER_hard_wait100us(uint32_t hund_us);

void BCM2835_TIMER_hard_waitms(uint32_t milis);

uint32_t BCM2835_TIMER_getTimestamp();

#endif 