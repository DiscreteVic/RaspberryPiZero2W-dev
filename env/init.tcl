
target remote localhost:3333
monitor poll
monitor halt
monitor sleep 500
monitor reset halt

# restore build/main.bin binary 0x8040
restore build/main.elf binary