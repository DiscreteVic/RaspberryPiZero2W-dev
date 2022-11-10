include config.mk

APP=main

CFLAGS = -mtune=cortex-a53 -Wall -O2 -ffreestanding -Iinc
LDFLAGS =-nostdlib -T ld/linker.ld

all: clean build

build: bcm2835.o  main.o
	@ $(ARCH)as -o build/ldr.o env/bootloader/ldr.s
	@ $(ARCH)ld $(LDFLAGS) $(BUILD_DIR)/*.o -o $(BUILD_DIR)/$(APP).elf
	@ $(ARCH)objcopy -O binary $(BUILD_DIR)/$(APP).elf $(BUILD_DIR)/$(APP).bin


%.o: src/%.c
	@ mkdir -p build/
	@ $(ARCH)gcc $(CFLAGS) -c $< -o build/$@


assemble: 
	@ mkdir -p build/
	@ $(ARCH)as -o build/$(APP).o $(APP).s
	@ $(ARCH)ld -o build/$(APP) build/$(APP).o
	@ $(ARCH)objcopy -S -O binary build/$(APP) build/$(APP).bin


openocd:
	@ $(OPENOCD_CMD) -f $(OPENOCD_DIR)/scripts/interface/$(INTERFACE).cfg -f $(ENV_DIR)/rpiz2w.cfg

gdb:
	@ $(GDB_CMD) build/main.elf -x $(ENV_DIR)/init.tcl
	# @ $(GDB_CMD) -tui -x $(ENV_DIR)/init_v2.tcl

clean:
	@ rm -rf build/