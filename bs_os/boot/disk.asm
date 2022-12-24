disk_loader:
    pusha
    push dx

    mov ah, 0x02            ; read mode
    mov al, dh              ; number of sectors
    mov cl, 0x02            ; start from sector 2
    mov ch, 0x00            ; cylinder 0
    mov dh, 0x00            ; head 0

    int 0x13                ; BIOS interrupt
    jc disk_err             ; check carry bit
    pop dx                  ; get original sector count
    cmp al, dh              ; actual read
    jne sector_err
    popa
    ret

disk_err:
    mov bx, ERROR_DISK
    call print16
    call newline_print16
    mov dh, ah              ; copy error from disk
    call hex_print16
    jmp disk_loop

sector_err:
    mov bx, ERROR_SECTORS
    call print16

disk_loop:
    jmp $

ERROR_DISK: db "Error reading Disk.", 0
ERROR_SECTORS: db "Incorrect number of sectors read.", 0
