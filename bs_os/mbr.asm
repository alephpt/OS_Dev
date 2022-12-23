[bits 16]
[org 0x7c00]

KERNEL_OFFSET equ 0x1000
mov [BOOT_DRIVE], dl

; set base pointer, and point stack at base
mov bp, 0x9000
mov sp, bp

call kernel_loader
call bit32_switch

jmp $

%include "disk.asm"
%include "gdt.asm"
%include "bit32-switch.asm"

[bits 16]
kernel_loader:
    mov bx, KERNEL_OFFSET
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call disk_loader
    ret

[bits 32]
BIT32_START:
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0
times 510 - ($-$$) db 0
dw 0xaa55
