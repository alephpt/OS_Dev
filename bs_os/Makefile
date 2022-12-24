C_SOURCES = $(wildcard utility/*.c drivers/*.c cpu/*.c kernel/kernel.c)
C_HEADERS = $(wildcard utility/*.h drivers/*.h cpu/*.h)
OBJ_FILES = $(C_SOURCES:.c=.o cpu/interrupt.o)

all: run

kernel.bin: boot/entry.o ${OBJ_FILES}
	i686-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

os.bin: boot/mbr.bin kernel.bin
	cat $^ > $@

run: os.bin
	qemu-system-i386 -fda $<
#	qemu-system-i386 -drive format=raw,media=disk,index=0,file=$<

echo: os.bin
	xxd $<

%.o: %.c ${C_HEADERS}
	i686-elf-gcc -g -m32 -ffreestanding -c $< -o $@ #-g

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

%.dis: %.bin
	ndisasm -b 32 $< > $@

kernel.elf: boot/entry.o ${OBJ_FILES}
	i686-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: os.bin kernel.elf
	qemu-system-i386 -s -S -drive format=raw,media=disk,index=0,file=os.bin -d guest_errors,int &
	i686-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	$(RM) -v *.bin *.o *.dis *.elf
	$(RM) -v kernel/*.o
	$(RM) -v utility/*.o
	$(RM) -v boot/*.o boot/*.bin
	$(RM) -v drivers/*.o
	$(RM) -v cpu/*.o
