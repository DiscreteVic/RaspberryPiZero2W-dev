
#include "bcm2835_common.h"

// BARRIERS NOT SET - TO DO
void setWordRegister(uint32_t addr, uint32_t value){
    *((volatile uint32_t*)addr) = (uint32_t)value;
}

uint32_t getWordRegister(uint32_t addr){
	uint32_t reg = *((volatile uint32_t*)addr);
	*((volatile uint32_t*)addr);
    return reg;
}


