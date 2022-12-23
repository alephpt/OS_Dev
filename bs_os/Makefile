# $@ = target file

# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: entry.o kernel.o
	i686-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

entry.o: entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	i686-elf-gcc -m32 -ffreestanding -c $< -o $@

# Disassemble
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

mbr.bin: mbr.asm
	nasm $< -f bin -o $@

os-image.bin: mbr.bin kernel.bin
	cat $^ > $@

run: os.bin
	#qemu-system-i386 -hda $<
	qemu-system-i386 -drive format=raw,media=disk,index=0,file=$<

echo: os.bin
	xxd $<

clean:
	$(RM) *.bin *.o *.dis
