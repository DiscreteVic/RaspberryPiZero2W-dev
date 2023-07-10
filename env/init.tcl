
target remote localhost:3333
monitor reset halt

# restore build/main.bin binary 0x8040
#load img/001.elf
#load img/002.elf
#load img/003.elf
#load img/004.elf
load
b main
#b BCM2835_DMASetUp
cont
layout src