
CONT=zero2w-cont
RMT_CMD=docker exec -w="/root/shared" $(CONT)

GCC=$(RMT_CMD) arm-none-eabi-

OOCD=$(RMT_CMD) openocd
KOOCD=$(RMT_CMD) killall openocd

# BUILD VARIABLES
ARCH=arm-none-eabi-
BUILD_DIR=build
SRC_DIR=src
ENV_DIR=env

# DEBUGGING VARIABLES
OPENOCD_CMD=openocd
OPENOCD_DIR=/usr/local/share/openocd
GDB_CMD=gdb-multiarch
INTERFACE=jlink
