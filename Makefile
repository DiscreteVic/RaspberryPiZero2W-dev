include config.mk

APP=main

build: clean
	@ mkdir -p build/
	@ $(ARCH)gcc -mtune=cortex-a53 -ffreestanding -c -o $(BUILD_DIR)/$(APP).o -Iinclude $(SRC_DIR)/$(APP).c 
	@ $(ARCH)gcc --entry=main -ffreestanding -nostdlib $(BUILD_DIR)/$(APP).o -o $(BUILD_DIR)/$(APP)
	@ $(ARCH)objcopy -S -O binary $(BUILD_DIR)/$(APP) $(BUILD_DIR)/$(APP).bin


assemble: 
	@ mkdir -p build/
	@ $(GCC)-as -o build/$(APP).o $(APP).asm
	@ $(GCC)-ld -o build/$(APP) build/$(APP).o
	@ $(GCC)-objcopy -S -O binary build/$(APP) build/$(APP).bin


openocd:
	@ $(OPENOCD_CMD) -f $(OPENOCD_DIR)/scripts/interface/$(INTERFACE).cfg -f $(ENV_DIR)/rpiz2w.cfg

gdb:
	@ $(GDB_CMD) -x $(ENV_DIR)/init.tcl
	# @ $(GDB_CMD) -tui -x $(ENV_DIR)/init_v2.tcl

clean:
	@ rm -rf build/