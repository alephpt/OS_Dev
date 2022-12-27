#include "isr.h"
#include "idt.h"
#include "../drivers/display.h"
#include "../drivers/io.h"
#include "../utility/memory.h"

isr_t interrupt_handlers[256];

char *exception_messages[] = {
    "Divide by zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_install () {
    set_idt_gate(0, (int32_t) isr0);
    set_idt_gate(1, (int32_t) isr1);
    set_idt_gate(2, (int32_t) isr2);
    set_idt_gate(3, (int32_t) isr3);
    set_idt_gate(4, (int32_t) isr4);
    set_idt_gate(5, (int32_t) isr5);
    set_idt_gate(6, (int32_t) isr6);
    set_idt_gate(7, (int32_t) isr7);
    set_idt_gate(8, (int32_t) isr8);
    set_idt_gate(9, (int32_t) isr9);
    set_idt_gate(10, (int32_t) isr10);
    set_idt_gate(11, (int32_t) isr11);
    set_idt_gate(12, (int32_t) isr12);
    set_idt_gate(13, (int32_t) isr13);
    set_idt_gate(14, (int32_t) isr14);
    set_idt_gate(15, (int32_t) isr15);
    set_idt_gate(16, (int32_t) isr16);
    set_idt_gate(17, (int32_t) isr17);
    set_idt_gate(18, (int32_t) isr18);
    set_idt_gate(19, (int32_t) isr19);
    set_idt_gate(20, (int32_t) isr20);
    set_idt_gate(21, (int32_t) isr21);
    set_idt_gate(22, (int32_t) isr22);
    set_idt_gate(23, (int32_t) isr23);
    set_idt_gate(24, (int32_t) isr24);
    set_idt_gate(25, (int32_t) isr25);
    set_idt_gate(26, (int32_t) isr26);
    set_idt_gate(27, (int32_t) isr27);
    set_idt_gate(28, (int32_t) isr28);
    set_idt_gate(29, (int32_t) isr29);
    set_idt_gate(30, (int32_t) isr30);
    set_idt_gate(31, (int32_t) isr31);

    // ICW1
    byte_out(0x20, 0x11);
    byte_out(0xA0, 0x11);
    // ICW2
    byte_out(0x21, 0x20);
    byte_out(0xA1, 0x28);
    // ICW3
    byte_out(0x21, 0x04);
    byte_out(0xA1, 0x02);
    // ICW4
    byte_out(0x21, 0x01);
    byte_out(0xA1, 0x01);
    // OCW1
    byte_out(0x21, 0x0);
    byte_out(0xA1, 0x0);

    // IRQ ISRs (Primary PIC)
    set_idt_gate(32, (uint32_t)irq0);
    set_idt_gate(33, (uint32_t)irq1);
    set_idt_gate(34, (uint32_t)irq2);
    set_idt_gate(35, (uint32_t)irq3);
    set_idt_gate(36, (uint32_t)irq4);
    set_idt_gate(37, (uint32_t)irq5);
    set_idt_gate(38, (uint32_t)irq6);
    set_idt_gate(39, (uint32_t)irq7);

    // IRQ ISRs (Secodary PIC)
    set_idt_gate(40, (uint32_t)irq8);
    set_idt_gate(41, (uint32_t)irq9);
    set_idt_gate(42, (uint32_t)irq10);
    set_idt_gate(43, (uint32_t)irq11);
    set_idt_gate(44, (uint32_t)irq12);
    set_idt_gate(45, (uint32_t)irq13);
    set_idt_gate(46, (uint32_t)irq14);
    set_idt_gate(47, (uint32_t)irq15);

    load_idt();
}

void isr_handler (registers_t *r) {
    string_print(exception_messages[r->int_no]);
    newline_print();
}

void irq_handler (registers_t *r) {
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }

    // primary EOI
    byte_out(0x20, 0x20);

    // secondary EOI
    if (r->int_no < 40) {
        byte_out(0xA0, 0x20);
    }
}

void register_interrupt_handler (uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}
