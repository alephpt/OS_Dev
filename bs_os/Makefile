

all: run

kernel.bin: entry.o kernel.o
	ld -m elf_i386 -e main -o $@ -Ttext 0x1000 $^ --oformat binary

entry.o: entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	i686-elf-gcc -m32 -ffreestanding -c $< -o $@
#	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

mbr.bin: mbr.asm
	nasm $< -f bin -o $@

os.bin: mbr.bin kernel.bin
	cat $^ > $@

run: os.bin
	qemu-system-i386 -hda $<

clean:
	$(RM) *.bin *.o *.dis
