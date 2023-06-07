include config.mk

APP=main

CFLAGS = -mtune=cortex-a53 -Wall -O2 -ffreestanding -Iinc 
LDFLAGS =-nostdlib -T ld/linker.ld

all: clean build

build: bcm2835.o  main.o
	@ $(GCC)as -o  build/ldr.o env/bootloader/ldr.s
	@ $(GCC)ld $(LDFLAGS) $(BUILD_DIR)/*.o -o $(BUILD_DIR)/$(APP).elf
	@ $(GCC)objcopy -O binary $(BUILD_DIR)/$(APP).elf $(BUILD_DIR)/$(APP).bin


%.o: src/%.c
	@ mkdir -p build/
	@ $(GCC)gcc $(CFLAGS) -c $< -o build/$@


assemble: 
	@ mkdir -p build/
	@ $(GCC)as -o build/$(APP).o $(APP).s
	@ $(GCC)ld -o build/$(APP) build/$(APP).o
	@ $(GCC)objcopy -S -O binary build/$(APP) build/$(APP).bin


openocd:
	@ $(OOCD) -f $(OPENOCD_DIR)/scripts/interface/$(INTERFACE).cfg -c "bindto 0.0.0.0" -f env/rpiz2w.cfg

stop_openocd:
	@ $(KOOCD) 

restart_openocd: stop_openocd openocd

start_docker:
	@ docker start $(CONT)

gdb:
	@ $(GDB_CMD) build/main.elf -x $(ENV_DIR)/init.tcl
	# @ $(GDB_CMD) -tui -x $(ENV_DIR)/init_v2.tcl

image:
	@ $(GCC)objcopy -S -I binary -O elf32-little --change-section-address .data=0xE000 img/bee.bin img/bee.elf


clean:
	@ rm -rf build/