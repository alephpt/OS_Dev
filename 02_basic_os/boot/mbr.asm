[org 0x7c00]

KERNEL_OFFSET equ 0x1000
mov [BOOT_DRIVE], dl

; set base pointer, and point stack at base
mov bp, 0x9000
mov sp, bp

mov bx, MODE_16BIT_MSG
call print16
call newline_print16

call kernel_loader
call bit32_switch

jmp $

%include "boot/bit16-print.asm"
%include "boot/bit32-print.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/bit32-switch.asm"

[bits 16]
kernel_loader:
    mov bx, LOAD_KERNEL_MSG
    call print16
    call newline_print16

    mov bx, KERNEL_OFFSET
    mov dh, 31
    mov dl, [BOOT_DRIVE]
    call disk_loader

    call debug_line

    ; Switch to 32-bit protected mode
    lgdt [gdt_descriptor]      ; Load GDT
    mov eax, cr0
    or eax, 0x1                ; Set PE bit to enable protected mode
    mov cr0, eax

    jmp CODE_SEG:BIT32_START ; Jump to 32-bit code segment



[bits 32]
BIT32_START:
    mov ebx, MODE_32BIT_MSG
    call print32
    call KERNEL_OFFSET
    jmp $

debug_line:
    mov bx, DEBUG_MSG
    call print16
    call newline_print16
    ret

BOOT_DRIVE db 0
MODE_16BIT_MSG db "Started 16-Bit Real Mode", 0
MODE_32BIT_MSG db "Started 32-Bit Protected Mode", 0
LOAD_KERNEL_MSG db "Loading Kernel into Memory", 0
DEBUG_MSG db "Hit Debug Line", 0

times 510 - ($-$$) db 0
dw 0xaa55
