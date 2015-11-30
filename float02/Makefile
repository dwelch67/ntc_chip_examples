

#ARMGNU ?= arm-none-linux-gnueabi
#ARMGNU ?= arm-none-eabi
ARMGNU ?= arm-linux-gnueabi


MSTUFF = -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=hard

AOPS = --warn --fatal-warnings $(MSTUFF)
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding $(MSTUFF)


all : notmain.bin

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.bin.s
	rm -f *.elf
	rm -f *.list
	rm -f *.list.c
	rm -f *.uci
	rm -f *.ucp
	rm -f *.mem
	rm -f listtoc
	rm -f notmain

notmain.o : notmain.c
	$(ARMGNU)-gcc $(COPS) -c notmain.c -o notmain.o

novectors.o : novectors.s
	$(ARMGNU)-as $(AOPS) -mfpu=vfp novectors.s -o novectors.o

uart.o : uart.c
	$(ARMGNU)-gcc $(COPS) -c uart.c -o uart.o

notmain.bin : memmap novectors.o uart.o notmain.o 
	$(ARMGNU)-ld novectors.o uart.o notmain.o -T memmap -o notmain.elf
	$(ARMGNU)-objdump -D notmain.elf > notmain.list
	$(ARMGNU)-objcopy notmain.elf -O binary notmain.bin 






