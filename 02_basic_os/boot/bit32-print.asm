[bits 32]

VIDEO_ADDRESS equ 0xb8000
WonB equ 0x0f

print32:
    pusha
    mov edx, VIDEO_ADDRESS

loop_print32:
    mov al, [ebx]
    mov ah, WonB

    cmp al, 0
    je done_print32

    mov [edx], ax
    add ebx, 1
    add edx, 2
    
    jmp loop_print32

done_print32:
    popa
    ret

clear_screen:
    pusha
    mov edi, VIDEO_ADDRESS
    mov ecx, 80*25
    mov eax, 0x20

    rep stosw
    popa
    ret