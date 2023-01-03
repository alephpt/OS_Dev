#include "./timer.h"
#include "./isr.h"
#include "../drivers/display.h"
#include "../drivers/io.h"
#include "../utility/memory.h"
#include "../utility/int.h"

uint32_t tick = 0;

static void timer_callback (registers_t *regs) {
    tick++;
    string_print("Tick: ");

    char tick_ascii[256];
    toString(tick, tick_ascii);
    string_print(tick_ascii);
    newline_print();
}

void timer_init (uint32_t freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = 1193180 / freq;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    byte_out(0x43, 0x36);
    byte_out(0x40, low);
    byte_out(0x40, high);
}
