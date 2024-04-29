print16:
    pusha

loop_print16:
    mov al, [bx]
    cmp al, 0
    je done_print16

    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp loop_print16

done_print16:
    popa
    ret

newline_print16:
    pusha
    mov ah, 0x0e
    mov al, 0x0a
    int 0x10
    mov al, 0x0d
    int 0x10

    popa
    ret

clear_print16:
    pusha
    mov ah, 0x00
    mov al, 0x03
    int 0x10

    popa
    ret

hex_print16:
    pusha
    mov cx, 0

loop_hex_print16:
    cmp cx, 4
    je end_hex_print16

    mov ax, dx
    and ax, 0x00f
    add al, 0x30
    cmp al, 0x39
    jle phase2_loop_hex
    add al, 7

phase2_loop_hex:
    mov bx, OUT_HEX_PRINT16 + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4

    add cx, 1
    jmp loop_hex_print16

end_hex_print16:
    mov bx, OUT_HEX_PRINT16
    call print16

    popa
    ret

OUT_HEX_PRINT16:
    db '0x0000',0


