ARCH = ./bin/arm-none-eabi

AS = $(ARCH)-as
CC = $(ARCH)-gcc
LD = $(ARCH)-ld

OBJDUMP = $(ARCH)-objdump
OBJCOPY = $(ARCH)-objcopy

AFLAGS = --warn --fatal-warnings
CFLAGS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding -g -ggdb

blink.thumb.bin: blink.thumb.list blink.thumb.elf
	$(OBJCOPY) blink.thumb.elf blink.thumb.bin -O binary

blink.thumb.list: blink.thumb.elf
	$(OBJDUMP) -D blink.thumb.elf > blink.thumb.list

blink.thumb.elf: memmap vectors.o blink.thumb.o
	$(LD) -o blink.thumb.elf -T memmap vectors.o blink.thumb.o

blink.thumb.o: blink.c
	$(CC) $(CFLAGS) -mthumb -c blink.c -o blink.thumb.o

vectors.o: vectors.s
	$(AS) $(AFLAGS) vectors.s -o vectors.o

clean:
	rm -f blink.thumb.bin
	rm -f blink.thumb.list
	rm -f blink.thumb.elf
	rm -f blink.thumb.o
	rm -f vectors.o


makerun:
	sudo openocd -f /usr/share/openocd/scripts/board/stm32f0discovery.cfg

maketel:
#	echo "halt\nload_image \"blink.thumb.elf\"\nresume 0x20000000\n" | 
	telnet localhost 4444
