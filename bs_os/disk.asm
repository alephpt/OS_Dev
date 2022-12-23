disk_loader:
    pusha
    push dx

    mov ah, 0x02    ; read mode
    mov al, dh      ; number of sectors
    mov cl, 0x02    ; start from sector 2
    mov ch, 0x00    ; cylinder 0
    mov dh, 0x00    ; head 0

    int 0x13        ; BIOS interrupt
    jc disk_err     ; check carry bit
    pop dx          ; get original sector count
    cmp al, dh      ; actual read
    jne sector_err
    popa
    ret

disk_err:
    jmp disk_loop

sector_err:
    jmp disk_loop

disk_loop:
    jmp $
