
#include "bcm2835.h"

// BARRIERS NOT SET - TO DO
void setWordRegister(uint32_t addr, uint32_t value){
    *((volatile uint32_t*)addr) = (uint32_t)value;
}

uint32_t getWordRegister(uint32_t addr){
	uint32_t reg = *((volatile uint32_t*)addr);
	*((volatile uint32_t*)addr);
    return reg;
}

uint8_t BCM2835_configGPIOPin(uint8_t pin, uint16_t funct){ // TO DO ERROR WRITING same reg twice
	uint32_t tmpReg;
	uint8_t funSelRegOff = (pin / 10);
	uint32_t funSelRegAddr = GPIO_FUN_SEL_REG + (funSelRegOff * 0x04U);
	
	if(pin <= 53){
		tmpReg = getWordRegister(funSelRegAddr);
		tmpReg &= ~(((uint32_t)0b111) << ((pin - (10*funSelRegOff))*3));
		setWordRegister(funSelRegAddr, tmpReg |= ((uint32_t)funct) << ((pin - (10*funSelRegOff)))*3);
	}
	else{
		return 1;
	}
	return 0;
}

uint8_t BCM2835_setGPIOPin(uint8_t pin){
	
	if(pin <= 31){
		setWordRegister(GPIO_OUT_SET0_REG, 0x1U << pin);
	}	
	else if(pin <= 53){
		setWordRegister(GPIO_OUT_SET1_REG, 0x1U << (pin - 31));
	}
	else{
		return 1;
	}
	return 0;
	
}

uint8_t BCM2835_clearGPIOPin(uint8_t pin){
	
	if(pin <= 31){
		setWordRegister(GPIO_OUT_CLR0_REG, 0x1U << pin);
	}	
	else if(pin <= 53){
		setWordRegister(GPIO_OUT_CLR1_REG, 0x1U << (pin - 31));
	}
	else{
		return 1;
	}
	return 0;
	
	
}

void BCM2835_configUART(){
	uint32_t r;
    // UART1
    // Enable UART
	r = getWordRegister(AUXENB_REG);
	r |= 1;
	setWordRegister(AUXENB_REG, r);
    // Set 8-bits data
	setWordRegister(AUX_MU_LCR_REG, 3);

    // Disable interrupts
	setWordRegister(AUX_MU_IER_REG, 0);

    // Clear port
	setWordRegister(AUX_MU_IIR_REG, 0x6);

    // Set Baudrate -> 115200 bps
	setWordRegister(AUX_MU_BAUD, 270);

    // Configure GPIO to UART
	r = getWordRegister(GPFSEL1);
	    // Reset GPIO pins
	r &= !((7<<12)|(7<<15));
	    // Set ALT5
	r |= (2 <<12)|(2<<15);
	setWordRegister(GPFSEL1, r);

    // Enable Port
	r = getWordRegister(AUX_MU_CNTL_REG);
	r |= 0x3;
	setWordRegister(AUX_MU_CNTL_REG, r);
}

void BCM2835_sendByteUART(uint8_t b) {

    // Check if TX is available
	while ((getWordRegister(AUX_MU_LSR_REG) & 0x20) == 0);
    // Send
	setWordRegister(AUX_MU_IO_REG, (uint32_t)b);

}

void BCM2835_printStringUART(uint8_t *arr) {
	uint8_t i;

	for(i = 0; arr[i] != '\0'; i++){
		BCM2835_sendByteUART(arr[i]);
	}


}

void BCM2835_printRegisterUART(uint32_t reg) {
	
	uint8_t i;

	for(i = 32; i > 0; i-=4){
		if(((uint8_t)(reg >> (i-4)) & 0xFU) < 0xAU){
			BCM2835_sendByteUART(((uint8_t)(reg >> (i-4)) & 0xFU) + 0x30U);
		}
		else{
			BCM2835_sendByteUART(((uint8_t)(reg >> (i-4)) & 0xFU) + 0x37U);
		}
	}


}

uint8_t BCM2835_receiveByteUART(){

	uint8_t r;

    // Check if data is available
	while ((getWordRegister(AUX_MU_LSR_REG) & 0x1) == 0);

	r = (uint8_t)getWordRegister(AUX_MU_IO_REG);

	return r;

}


void __attribute__((optimize(0)))  BCM2835_soft_waitms(uint32_t milis){
// void  BCM2835_soft_waitms(uint32_t milis){
	//CONSTANT VALUE OBTAINED EXPERIMENTALLY
	uint32_t i, j;

	for(j=milis; j > 0; j--){
		for(i=1916; i > 0; i--){
		}
	}

}

void __attribute__((optimize(0)))  BCM2835_hard_wait100us(uint32_t hund_us){

	uint32_t timestampA, timestampB;

	uint32_t i;

	for(i=hund_us; i > 0; i--){
	    timestampA = getWordRegister(SYS_TIM_CLO);
	    timestampB = 0;
		while (timestampB < 100)
		{
			if(getWordRegister(SYS_TIM_CLO) >= timestampA) timestampB = getWordRegister(SYS_TIM_CLO) - timestampA;
			else timestampB = 0xFFFFFFFFU - (timestampA - getWordRegister(SYS_TIM_CLO));
		}
	}

}

void __attribute__((optimize(0)))  BCM2835_hard_waitms(uint32_t milis){


	uint32_t timestampA, timestampB = 0;

	uint32_t i;

	for(i=milis; i > 0; i--){
	    timestampA = getWordRegister(SYS_TIM_CLO);
	    timestampB = 0;
		while (timestampB < 1000)
		{
			if(getWordRegister(SYS_TIM_CLO) >= timestampA) timestampB = getWordRegister(SYS_TIM_CLO) - timestampA;
			else timestampB = 0xFFFFFFFFU - (timestampA - getWordRegister(SYS_TIM_CLO));
		}
	}

}

uint32_t BCM2835_timerGetTimestamp(){

	uint32_t timestamp = getWordRegister(SYS_TIM_CLO);
	return timestamp;
}



volatile uint32_t __attribute((aligned(16))) mb_buff[128];

bool BCM2835_mailboxCall(uint8_t channel){

    uint32_t reg = (((uint32_t)&mb_buff & ~(0xF)) | (channel & (0xF)));

    while((getWordRegister(MAILBOX_STATUS) & MAILBOX_FULL));
    setWordRegister(MAILBOX_WRITE, reg);

    while(1){
        while((getWordRegister(MAILBOX_STATUS) & MAILBOX_EMPTY));
        
        if(reg == getWordRegister(MAILBOX_READ)) return mb_buff[1]==MAILBOX_RESPONSE_NOERROR;
    }
}

uint32_t width, height, pitch, isrgb;
uint8_t *frameBuff;

void BCM2835_videoInit()
{
	//FRAME BUFFER INIT
    mb_buff[0] = (MAILBOX_TAG_BUFF_SIZE + 3)<<2; // SIZE
    mb_buff[1] = MAILBOX_TAG_REQUEST;
    mb_buff[2] = MAILBOX_TAG_ID_SETPHYWH;
    mb_buff[3] = 8U; //size buff value
    mb_buff[4] = 0U;
    mb_buff[5] = VIDEO_SCREEN_W;
    mb_buff[6] = VIDEO_SCREEN_H;
    mb_buff[7] = MAILBOX_TAG_ID_SETVIRWH;
    mb_buff[8] = 8U;
    mb_buff[9] = 8U;
    mb_buff[10] = VIDEO_SCREEN_W;
    mb_buff[11] = VIDEO_SCREEN_H;
    mb_buff[12] = MAILBOX_TAG_ID_SETVIROFFS;
    mb_buff[13] = 8;
    mb_buff[14] = 8;
    mb_buff[15] = 0; 
    mb_buff[16] = 0; 
    mb_buff[17] = MAILBOX_TAG_ID_SETDPTH;
    mb_buff[18] = 4;
    mb_buff[19] = 4;
    mb_buff[20] = 32; // bppx
    mb_buff[21] = MAILBOX_TAG_ID_SETPIXORD;
    mb_buff[22] = 4;
    mb_buff[23] = 4;
    mb_buff[24] = 1; // RGB
    mb_buff[25] = MAILBOX_TAG_ID_ALLBUFF;
    mb_buff[26] = 8;
    mb_buff[27] = 8;
    mb_buff[28] = 4096; 
    mb_buff[29] = 0;    
    mb_buff[30] = MAILBOX_TAG_ID_GETPTCH;
    mb_buff[31] = 4;
    mb_buff[32] = 4;
    mb_buff[33] = 0; 
    mb_buff[MAILBOX_TAG_BUFF_SIZE + 2] = MAILBOX_TAG_LAST;


    if (BCM2835_mailboxCall(MAILBOX_PROPERTY_CHANNEL) && mb_buff[20] == 32 && mb_buff[28] != 0) {
        mb_buff[28] &= 0x3FFFFFFF; 
        width = mb_buff[10];       
        height = mb_buff[11];      
        pitch = mb_buff[33];       // Number of bytes per line
        isrgb = mb_buff[24];       
        frameBuff = (uint8_t *)mb_buff[28];
    }
    
}

void BCM2835_videoDrawPixel(uint32_t x, uint32_t y, uint32_t attr)
{
    uint32_t offs = (y * pitch) + (x * 4);
    // VGA PAL ATTR = COLOR
    setWordRegister((uint32_t)(frameBuff + offs), attr);
}

void BCM2835_videoBlackScreen()
{
    uint32_t offs, i, j;
    for(i = 0; i < VIDEO_SCREEN_W; i++){
        for(j = 0; j < VIDEO_SCREEN_H; j++){
            offs = (j * pitch) + (i * 4);
            setWordRegister((uint32_t)(frameBuff + offs), 0x000000U);
        }
    }
}

void BCM2835_videoColorScreen(uint32_t col)
{
    uint32_t offs, i, j;
    for(i = 0; i < VIDEO_SCREEN_W; i++){
        for(j = 0; j < VIDEO_SCREEN_H; j++){
            offs = (j * pitch) + (i * 4);
            setWordRegister((uint32_t)(frameBuff + offs), col);
        }
    }
}


