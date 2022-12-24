#pragma once
#include <stdint.h>

#define IDT_ENTRIES 256
#define KERNEL_CS 0x08

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

typedef struct {
    uint16_t low_offset;
    uint16_t high_offset;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
} __attribute__((packed)) idt_gate_t;

void load_idt();
void set_idt_gate (int n, uint32_t handler);
