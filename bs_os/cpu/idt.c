#include "./idt.h"
#include "../utility/memory.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void load_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    asm volatile("lidt (%0)" : : "r" (&idt_reg));
}

void set_idt_gate (int n, uint32_t handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].selector = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = high_16(handler);
}
