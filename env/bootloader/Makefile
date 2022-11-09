include ../../config.mk

all: clean
	@ $(ARCH)as -o ldr.elf ldr.s
	@ $(ARCH)objcopy -O binary ldr.elf ldr.bin

clean:
	@ rm -rf *.elf *.bin