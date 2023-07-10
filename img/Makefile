
include ../config.mk

#Package Imagemagick
SOFT=convert

all: convert elf

convert:
	@ convert bee.bmp -depth 8 -type palette BMP3:bee.bin

elf: 
	#@ $(GCC)objcopy -S -I binary -O elf32-little --change-section-address .data=0xE000 img/bee.bin img/bee.elf
	@ $(GCC)objcopy -S -I binary -O elf32-little --change-section-address .data=0xE000 img/001.bin img/001.elf
	@ $(GCC)objcopy -S -I binary -O elf32-little --change-section-address .data=0x59000 img/002.bin img/002.elf
	@ $(GCC)objcopy -S -I binary -O elf32-little --change-section-address .data=0xA4000 img/003.bin img/003.elf
	@ $(GCC)objcopy -S -I binary -O elf32-little --change-section-address .data=0xEF000 img/004.bin img/004.elf
	

clean:
	@ rm  *.elf