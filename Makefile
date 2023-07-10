include config.mk

SOURCES := $(shell find . -type f -name '*.c')
OBJECTS := $(subst .c,.o,$(SOURCES))
BL := $(shell find . -type f -name '*.s')
OBJECTS += $(subst .s,.o,$(BL))

INCLUDES := $(shell find . -type f -name '*.h')
INC_DIRS := $(dir $(INCLUDES))
INC_FLAGS := $(subst ./,-I,$(INC_DIRS))

APP=main

CFLAGS = -g -mtune=cortex-a53 -Wall -O2 -ffreestanding $(INC_FLAGS)
LDFLAGS =-nostdlib -T ld/linker.ld

all: clean build

build: $(OBJECTS)
	@ $(GCC)ld $(LDFLAGS) $(subst ./,build/,$(OBJECTS)) -o $(BUILD_DIR)/$(APP).elf
	@ $(GCC)objcopy -O binary $(BUILD_DIR)/$(APP).elf $(BUILD_DIR)/$(APP).bin

info:
	$(info $(OBJECTS))
	$(info $(SOURCES))
	$(info $(BL))
	$(info $(INC_FLAGS))

%.o: %.c
	@ mkdir -p $(BUILD_DIR)/$(dir $@)
	@ $(GCC)gcc $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

%.o: %.s
	@ mkdir -p $(BUILD_DIR)/$(dir $@)
	@ $(GCC)as -o $(BUILD_DIR)/$@ $<

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


clean:
	@ rm -rf build/