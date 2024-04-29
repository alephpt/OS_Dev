[bits 16]
bit32_switch:
    cli                     ; disable interrupts
    lgdt [gdt_descriptor]   ; load GDT descriptor
    mov eax, cr0            ; enable protected
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:bit32_load ; far jump

[bits 32]
bit32_load:
    mov ax, DATA_SEG        ; update segment regs
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000        ; init stack
    mov esp, ebp            ; set stack pointer

    call BIT32_START
