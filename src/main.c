#include <stdio.h>
//*((uint32_t *)address) = (uint32_t)value;

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

int main(){

    //Set uart clock

    // Write Data UART - DR Register
    *((uint32_t *)0x7E20100) = (uint32_t)0x0000005A;
    
    //Set baud div - IBRD FBRD Registers
    *((uint32_t *)0x7E20124) = (uint32_t)0x0000065B;
    *((uint32_t *)0x7E20128) = (uint32_t)0x00000001;

    // Set transmission  UART and enable - CR Register
    *((uint32_t *)0x7E20130) = (uint32_t)0x00000301;


    while(1);

    

    return 0;
}