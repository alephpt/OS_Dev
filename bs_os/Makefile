# $@ = target file

# $< = first dependency
# $^ = all dependencies

C_SOURCES = $(wildcard utility/*.c drivers/*.c cpu/*.c kernel/kernel.c)
C_HEADERS = $(wildcard utility/*.h drivers/*.h cpu/*.h)
OBJ_FILES = $(C_SOURCES:.c=.o cpu/interrupt.o)

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: boot/entry.o ${OBJ_FILES}
	i686-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

os.bin: boot/mbr.bin kernel.bin
	cat $^ > $@

run: os.bin
	#qemu-system-i386 -hda $<
	qemu-system-i386 -drive format=raw,media=disk,index=0,file=$<

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

#debugging purposes
kernel.elf: boot/entry.o ${OBJ_FILES}
	i686-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: os.bin kernel.elf
	qemu-system-i386 -s -S -fda os.bin -d guest_errors,int &
	i686-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	$(RM) *.bin *.o *.dis *.elf
	$(RM) kernel/*.o
	$(RM) boot/*.o boot/*.bin
	$(RM) drivers/*.o
	$(RM) cpu/*.o
