include config.mk

APP=main

CFLAGS = -mtune=cortex-a53 -Wall -O2 -ffreestanding
LDFLAGS =-nostdlib -T src/linker.ld

build: clean
	@ mkdir -p build/
	@ $(ARCH)gcc $(CFLAGS) -c $(SRC_DIR)/$(APP).c -o $(BUILD_DIR)/$(APP).o  
	@ $(ARCH)ld $(LDFLAGS) $(BUILD_DIR)/$(APP).o -o $(BUILD_DIR)/$(APP).elf
	@ $(ARCH)objcopy -O binary $(BUILD_DIR)/$(APP).elf $(BUILD_DIR)/$(APP).bin


assemble: 
	@ mkdir -p build/
	@ $(ARCH)as -o build/$(APP).o $(APP).asm
	@ $(ARCH)ld -o build/$(APP) build/$(APP).o
	@ $(ARCH)objcopy -S -O binary build/$(APP) build/$(APP).bin


openocd:
	@ $(OPENOCD_CMD) -f $(OPENOCD_DIR)/scripts/interface/$(INTERFACE).cfg -f $(ENV_DIR)/rpiz2w.cfg

gdb:
	@ $(GDB_CMD) build/main.elf -x $(ENV_DIR)/init.tcl
	# @ $(GDB_CMD) -tui -x $(ENV_DIR)/init_v2.tcl

clean:
	@ rm -rf build/