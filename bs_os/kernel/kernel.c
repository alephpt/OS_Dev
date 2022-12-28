#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../utility/memory.h"

void kernel_init () {
    screen_clear();

    string_print("Interrupt Service Routines Loading .. \n");
    isr_install();

    string_print("External Interrupts Enabling .. \n");
    asm volatile("sti");

    string_print("Keyboard Initializing (IRQ 1) .. \n");
    keyboard_init();

    string_print("Dynamic Memory Initializing .. \n");
    dynamicMemory_init();

    newline_print();
//    screen_clear();

    return;
}

void kernel_entry (){
    kernel_init();

    string_print(" - | Welcome to Gambit | - ");
    newline_print();

    string_print("\n > ");

    return;
}
