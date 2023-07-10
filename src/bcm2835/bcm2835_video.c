
#include <bcm2835_video.h>


uint32_t width, height, pitch, isrgb;
uint8_t *frameBuff;

volatile uint32_t __attribute((aligned(16))) mb_buff[128];


void BCM2835_VIDEO_setCodifiedImg(uint16_t x, uint16_t y, uint32_t px, uint32_t membase){

    uint32_t offs = (y * pitch) + (x * 4);


    setWordRegister((uint32_t)(membase + offs), px);

}

bool BCM2835_VIDEO_mailboxCall(uint8_t channel){

    uint32_t reg = (((uint32_t)&mb_buff & ~(0xF)) | (channel & (0xF)));

    while((getWordRegister(BCM2835_MAILBOX_STATUS) & BCM2835_MAILBOX_FULL));
    setWordRegister(BCM2835_MAILBOX_WRITE, reg);

    while(1){
        while((getWordRegister(BCM2835_MAILBOX_STATUS) & BCM2835_MAILBOX_EMPTY));
        
        if(reg == getWordRegister(BCM2835_MAILBOX_READ)) return mb_buff[1]==BCM2835_MAILBOX_RESPONSE_NOERROR;
    }
}


void BCM2835_VIDEO_init()
{
	//FRAME BUFFER INIT
    mb_buff[0] = (BCM2835_MAILBOX_TAG_BUFF_SIZE + 3)<<2; // SIZE
    mb_buff[1] = BCM2835_MAILBOX_TAG_REQUEST;
    mb_buff[2] = BCM2835_MAILBOX_TAG_ID_SETPHYWH;
    mb_buff[3] = 8U; //size buff value
    mb_buff[4] = 0U;
    mb_buff[5] = VIDEO_SCREEN_W;
    mb_buff[6] = VIDEO_SCREEN_H;
    mb_buff[7] = BCM2835_MAILBOX_TAG_ID_SETVIRWH;
    mb_buff[8] = 8U;
    mb_buff[9] = 8U;
    mb_buff[10] = VIDEO_SCREEN_W;
    mb_buff[11] = VIDEO_SCREEN_H;
    mb_buff[12] = BCM2835_MAILBOX_TAG_ID_SETVIROFFS;
    mb_buff[13] = 8;
    mb_buff[14] = 8;
    mb_buff[15] = 0; 
    mb_buff[16] = 0; 
    mb_buff[17] = BCM2835_MAILBOX_TAG_ID_SETDPTH;
    mb_buff[18] = 4;
    mb_buff[19] = 4;
    mb_buff[20] = 32; // bppx
    mb_buff[21] = BCM2835_MAILBOX_TAG_ID_SETPIXORD;
    mb_buff[22] = 4;
    mb_buff[23] = 4;
    mb_buff[24] = 1; // RGB
    mb_buff[25] = BCM2835_MAILBOX_TAG_ID_ALLBUFF;
    mb_buff[26] = 8;
    mb_buff[27] = 8;
    mb_buff[28] = 4096; 
    mb_buff[29] = 0;    
    mb_buff[30] = BCM2835_MAILBOX_TAG_ID_GETPTCH;
    mb_buff[31] = 4;
    mb_buff[32] = 4;
    mb_buff[33] = 0; 
    mb_buff[BCM2835_MAILBOX_TAG_BUFF_SIZE + 2] = BCM2835_MAILBOX_TAG_LAST;


    if (BCM2835_VIDEO_mailboxCall(BCM2835_MAILBOX_PROPERTY_CHANNEL) && mb_buff[20] == 32 && mb_buff[28] != 0) {
        mb_buff[28] &= 0x3FFFFFFF; 
        width = mb_buff[10];       
        height = mb_buff[11];      
        pitch = mb_buff[33];       // Number of bytes per line
        isrgb = mb_buff[24];       
        frameBuff = (uint8_t *)mb_buff[28];
    }
    
}


uint32_t BCM2835_VIDEO_getFrameBuffAdd(){
	return (uint32_t)frameBuff;
}

void BCM2835_VIDEO_drawPixel(uint32_t x, uint32_t y, uint32_t attr)
{
    uint32_t offs = (y * pitch) + (x * 4);
    // VGA PAL ATTR = COLOR
    setWordRegister((uint32_t)(frameBuff + offs), attr);
}

void BCM2835_VIDEO_blackScreen()
{
    uint32_t offs, i, j;
    for(i = 0; i < VIDEO_SCREEN_W; i++){
        for(j = 0; j < VIDEO_SCREEN_H; j++){
            offs = (j * pitch) + (i * 4);
            setWordRegister((uint32_t)(frameBuff + offs), 0x000000U);
        }
    }
}

void BCM2835_VIDEO_colorScreen(uint32_t col)
{
    uint32_t offs, i, j;
    for(i = 0; i < VIDEO_SCREEN_W; i++){
        for(j = 0; j < VIDEO_SCREEN_H; j++){
            offs = (j * pitch) + (i * 4);
            setWordRegister((uint32_t)(frameBuff + offs), col);
        }
    }
}


