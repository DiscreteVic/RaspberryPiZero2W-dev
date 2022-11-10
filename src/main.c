

#include "bcm2835.h"

void main(void) {

    configUART();

	sendByteUART('H');
	sendByteUART('o');
	sendByteUART('l');
	sendByteUART('a');
	sendByteUART(' ');
	sendByteUART('M');
	sendByteUART('U');
	sendByteUART('N');
	sendByteUART('D');
	sendByteUART('O');
	sendByteUART('!');

	while (1);

}