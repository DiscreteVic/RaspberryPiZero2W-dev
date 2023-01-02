

#include "bcm2835.h"

#define MAILBOX_BASE                    PERIPHERALS_BASE_ADDR + 0xB880U

#define     MAILBOX_READ                    MAILBOX_BASE + 0x00U 
#define     MAILBOX_STATUS                  MAILBOX_BASE + 0x18U
#define     MAILBOX_WRITE                   MAILBOX_BASE + 0x20U 
#define     MAILBOX_PROPERTY_CHANNEL        8u
#define     MAILBOX_FRAMEBUFFER_CHANNEL     1U
#define     MAILBOX_FULL                    0x80000000U
#define     MAILBOX_EMPTY                   0x40000000U
#define     MAILBOX_RESPONSE_NOERROR        0x80000000U

#define     MAILBOX_TAGS_NUM            7U
#define     MAILBOX_TAG_BUFF_SIZE       32U //Tags with their elements
#define     MAILBOX_TAG_ID_SETPHYWH     0x48003 
#define     MAILBOX_TAG_ID_SETVIRWH     0x48004 
#define     MAILBOX_TAG_ID_SETDPTH      0x48005 
#define     MAILBOX_TAG_ID_SETPIXORD    0x48006 
#define     MAILBOX_TAG_ID_SETVIROFFS   0x48009 
#define     MAILBOX_TAG_ID_ALLBUFF      0x40001 
#define     MAILBOX_TAG_ID_GETPTCH      0x40008 
#define     MAILBOX_TAG_ID_BLNKSCR      0x40002 

#define     MAILBOX_TAG_REQUEST         0U
#define     MAILBOX_TAG_LAST            0U

#define     SCREEN_W                    640U
#define     SCREEN_H                    480U

volatile uint32_t __attribute((aligned(16))) mb_buff[128];

bool BCM2835_mailboxCall(uint8_t channel){

    uint32_t reg = ((uint32_t)&mb_buff & ~(0xF) | channel & (0xF));

    while((getWordRegister(MAILBOX_STATUS) & MAILBOX_FULL));
    setWordRegister(MAILBOX_WRITE, reg);

    while(1){
        while((getWordRegister(MAILBOX_STATUS) & MAILBOX_EMPTY));
        
        if(reg == getWordRegister(MAILBOX_READ)) return mb_buff[1]==MAILBOX_RESPONSE_NOERROR;
    }
}

uint32_t width, height, pitch, isrgb;
uint8_t *frameBuff;

void fb_init()
{
    mb_buff[0] = (MAILBOX_TAG_BUFF_SIZE + 3)<<2; // SIZE
    mb_buff[1] = MAILBOX_TAG_REQUEST;
    mb_buff[2] = MAILBOX_TAG_ID_SETPHYWH;
    mb_buff[3] = 8U; //size buff value
    mb_buff[4] = 0U;
    mb_buff[5] = SCREEN_W;
    mb_buff[6] = SCREEN_H;
    mb_buff[7] = MAILBOX_TAG_ID_SETVIRWH;
    mb_buff[8] = 8U;
    mb_buff[9] = 8U;
    mb_buff[10] = SCREEN_W;
    mb_buff[11] = SCREEN_H;
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
        frameBuff = (uint32_t *)mb_buff[28];
    }
    
}

void blackScreen()
{
    mb_buff[0] = (6)<<2; // SIZE
    mb_buff[1] = MAILBOX_TAG_REQUEST;
    mb_buff[2] = MAILBOX_TAG_ID_SETPHYWH;
    mb_buff[3] = 4U;
    mb_buff[4] = 4U;
    mb_buff[5] = 0U;
    mb_buff[6] = MAILBOX_TAG_LAST;

    BCM2835_mailboxCall(MAILBOX_PROPERTY_CHANNEL);
}

void drawPixel(uint32_t x, uint32_t y, uint32_t attr)
{
    uint32_t offs = (y * pitch) + (x * 4);
    // VGA PAL ATTR TO DO
    setWordRegister(frameBuff + offs, attr);
}

void cleanScreen()
{
    uint32_t offs, i, j;
    for(i = 0; i < SCREEN_W; i++){
        for(j = 0; j < SCREEN_H; j++){
            offs = (j * pitch) + (i * 4);
            setWordRegister(frameBuff + offs, 0x000000U);
        }
    }
}


void main(void) {
    uint8_t i;


    BCM2835_configUART();
    BCM2835_mailboxCall(MAILBOX_PROPERTY_CHANNEL);
    fb_init();

    drawPixel(200,200,0xAA00AAU);
    BCM2835_hard_waitms(2000);
    cleanScreen();
    drawPixel(200,200,0xAA00AAU);

    BCM2835_printStringUART("DONE:\n");

	while (1);

}