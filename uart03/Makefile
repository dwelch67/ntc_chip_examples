

#ARMGNU ?= arm-none-linux-gnueabi
#ARMGNU ?= arm-none-eabi
ARMGNU ?= arm-linux-gnueabi

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 


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
	$(ARMGNU)-as novectors.s -o novectors.o

uart.o : uart.c
	$(ARMGNU)-gcc $(COPS) -c uart.c -o uart.o

notmain.bin : memmap novectors.o uart.o notmain.o 
	$(ARMGNU)-ld novectors.o uart.o notmain.o -T memmap -o notmain.elf
	$(ARMGNU)-objdump -D notmain.elf > notmain.list
	$(ARMGNU)-objcopy --srec-forceS3 notmain.elf -O srec notmain.srec
	$(ARMGNU)-objcopy notmain.elf -O binary notmain.bin 

