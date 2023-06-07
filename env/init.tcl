
target remote localhost:3333
monitor reset halt

# restore build/main.bin binary 0x8040
load img/bee.elf 
load

layout asm