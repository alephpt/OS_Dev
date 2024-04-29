global _start;
[bits 32]

_start:
    [extern kernel_entry]
    call kernel_entry
    jmp $
