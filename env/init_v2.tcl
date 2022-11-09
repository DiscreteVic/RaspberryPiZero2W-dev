target remote localhost:3333
monitor poll
monitor halt
monitor sleep 500
monitor reset halt

load build/main.elf 0x8000