/* tutorial lead from wiki.osdev.org/bare_bones */
.set ALIGN,     1<<0                // aligns modules on page bounds
.set MEMINFO,   1<<1                // provides memory map
.set FLAGS,     ALIGN | MEMINFO     // multiboot flag field
.set MAGIC,     0x1BADB002          // lets bootloader find header
.set CHECKSUM,  -(MAGIC + FLAGS)    // checksum of above

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp
    call kernel_main
    cli
1:  hlt
    jmp 1b

.size _start, . - _start
