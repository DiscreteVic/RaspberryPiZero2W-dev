
#include <bcm2835_timer.h>

void __attribute__((optimize(0)))  BCM2835_TIMER_soft_waitms(uint32_t milis){
// void  BCM2835_TIMER_soft_waitms(uint32_t milis){
	//CONSTANT VALUE OBTAINED EXPERIMENTALLY
	uint32_t i, j;

	for(j=milis; j > 0; j--){
		for(i=1916; i > 0; i--){
		}
	}

}

void __attribute__((optimize(0)))  BCM2835_TIMER_hard_wait100us(uint32_t hund_us){

	uint32_t timestampA, timestampB;

	uint32_t i;

	for(i=hund_us; i > 0; i--){
	    timestampA = getWordRegister(BCM2835_SYS_TIM_CLO);
	    timestampB = 0;
		while (timestampB < 100)
		{
			if(getWordRegister(BCM2835_SYS_TIM_CLO) >= timestampA) timestampB = getWordRegister(BCM2835_SYS_TIM_CLO) - timestampA;
			else timestampB = 0xFFFFFFFFU - (timestampA - getWordRegister(BCM2835_SYS_TIM_CLO));
		}
	}

}

void __attribute__((optimize(0)))  BCM2835_TIMER_hard_waitms(uint32_t milis){


	uint32_t timestampA, timestampB = 0;

	uint32_t i;

	for(i=milis; i > 0; i--){
	    timestampA = getWordRegister(BCM2835_SYS_TIM_CLO);
	    timestampB = 0;
		while (timestampB < 1000)
		{
			if(getWordRegister(BCM2835_SYS_TIM_CLO) >= timestampA) timestampB = getWordRegister(BCM2835_SYS_TIM_CLO) - timestampA;
			else timestampB = 0xFFFFFFFFU - (timestampA - getWordRegister(BCM2835_SYS_TIM_CLO));
		}
	}

}

uint32_t BCM2835_TIMER_getTimestamp(){

	uint32_t timestamp = getWordRegister(BCM2835_SYS_TIM_CLO);
	return timestamp;
}



