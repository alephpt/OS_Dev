#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../utility/utils.h"

void kernel_entry (){
    screen_clear();
    string_print("Hello, Kernel!\n");

    string_print("Interrupt Service Routines Loading .. \n");
    isr_install();

    string_print("External Interrupts Enabling .. \n");
    asm volatile("sti");

    string_print("Keyboard Initializing (IRQ 1) .. \n");
    keyboard_init();

    return;
}
