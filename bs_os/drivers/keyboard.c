#include "./io.h"
#include "./keyboard.h"
#include "./display.h"
#include "../utility/string.h"
#include "../utility/terminal.h"
#include "../utility/memory.h"
#include "../cpu/isr.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SC_MAX 56

static char input_buffer[256];

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char ascii_table[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback (registers_t *regs) {
    uint8_t scanned = byte_in(0x60);

    if (scanned > SC_MAX) { return; }

    if (scanned == BACKSPACE) {
        if (backspace(input_buffer)) {
            backspace_print();
        }
    } else 
    if (scanned == ENTER) {
        newline_print();
        execute_input(input_buffer);
       // input_buffer[0] = '\0';
    } else {
        char let = ascii_table[(int) scanned];
        append(input_buffer, let);
        char str[2] = { let, '\0' };
        string_print(str);
    }

    return;
}

void keyboard_init () {
    register_interrupt_handler(IRQ1, keyboard_callback);    
}
