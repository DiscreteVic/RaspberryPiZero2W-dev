#ifndef BCM2835_VIDEO
#define BCM2835_VIDEO

#include <common.h>

#include <bcm2835_common.h>


#define BCM2835_MAILBOX_BASE                    BCM2835_PERIPHERALS_BASE_ADDR + 0xB880U
#define BCM2835_MAILBOX_READ                    BCM2835_MAILBOX_BASE + 0x00U 
#define BCM2835_MAILBOX_STATUS                  BCM2835_MAILBOX_BASE + 0x18U
#define BCM2835_MAILBOX_WRITE                   BCM2835_MAILBOX_BASE + 0x20U 
#define BCM2835_MAILBOX_PROPERTY_CHANNEL        8u
#define BCM2835_MAILBOX_FRAMEBUFFER_CHANNEL     1U
#define BCM2835_MAILBOX_FULL                    0x80000000U
#define BCM2835_MAILBOX_EMPTY                   0x40000000U
#define BCM2835_MAILBOX_RESPONSE_NOERROR        0x80000000U

#define BCM2835_MAILBOX_TAGS_NUM                7U
#define BCM2835_MAILBOX_TAG_BUFF_SIZE           32U //Tags with their elements
#define BCM2835_MAILBOX_TAG_ID_SETPHYWH         0x48003 
#define BCM2835_MAILBOX_TAG_ID_SETVIRWH         0x48004 
#define BCM2835_MAILBOX_TAG_ID_SETDPTH          0x48005 
#define BCM2835_MAILBOX_TAG_ID_SETPIXORD        0x48006 
#define BCM2835_MAILBOX_TAG_ID_SETVIROFFS       0x48009 
#define BCM2835_MAILBOX_TAG_ID_ALLBUFF          0x40001 
#define BCM2835_MAILBOX_TAG_ID_GETPTCH          0x40008 
#define BCM2835_MAILBOX_TAG_ID_BLNKSCR          0x40002 
#define BCM2835_MAILBOX_TAG_REQUEST             0U
#define BCM2835_MAILBOX_TAG_LAST                0U

#define VIDEO_SCREEN_W                          640U
#define VIDEO_SCREEN_H                          480U


bool BCM2835_VIDEO_mailboxCall(uint8_t channel);

void BCM2835_VIDEO_init();

void BCM2835_VIDEO_drawPixel(uint32_t x, uint32_t y, uint32_t attr);

void BCM2835_VIDEO_blackScreen();

void BCM2835_VIDEO_colorScreen(uint32_t col);

void BCM2835_VIDEO_setCodifiedImg(uint16_t x, uint16_t y, uint32_t px, uint32_t membase);

uint32_t BCM2835_VIDEO_getFrameBuffAdd();

#endif 