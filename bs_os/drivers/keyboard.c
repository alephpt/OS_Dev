#include "./io.h"
#include "./keyboard.h"
#include "./display.h"
#include "../utility/utils.h"
#include "../cpu/isr.h"


void letter_print (uint8_t code) {
    switch (code) {
        case 0x0:
            string_print("ERR");
            break;
        case 0x1:
            string_print("ESC");
            break;
        case 0x2:
            string_print("1");
            break; 
        case 0x3:
            string_print("2");
            break; 
        case 0x4:
            string_print("3");
            break; 
        case 0x5:
            string_print("4");
            break; 
        case 0x6:
            string_print("5");
            break; 
        case 0x7:
            string_print("6");
            break; 
        case 0x8:
            string_print("7");
            break; 
        case 0x9:
            string_print("8");
            break; 
        case 0x0A:
            string_print("9");
            break; 
        case 0x0B:
            string_print("0");
            break; 
        case 0x0C:
            string_print("-");
            break; 
        case 0x0D:
            string_print("+");
            break; 
        case 0x0E:
            string_print("Backspace");
            break; 
        case 0x0F:
            string_print("Tab");
            break; 
        case 0x10:
            string_print("Q");
            break; 
        case 0x11:
            string_print("W");
            break; 
        case 0x12:
            string_print("E");
            break; 
        case 0x13:
            string_print("R");
            break; 
        case 0x14:
            string_print("T");
            break; 
        case 0x15:
            string_print("Y");
            break; 
        case 0x16:
            string_print("U");
            break; 
        case 0x17:
            string_print("I");
            break; 
        case 0x18:
            string_print("O");
            break; 
        case 0x19:
            string_print("P");
            break; 
        case 0x1A:
            string_print("[");
            break; 
        case 0x1B:
            string_print("]");
            break; 
        case 0x1C:
            string_print("ENTER");
            break; 
        case 0x1D:
            string_print("LCtrl");
            break; 
        case 0x1E:
            string_print("A");
            break; 
        case 0x1F:
            string_print("S");
            break; 
        case 0x20:
            string_print("D");
            break; 
        case 0x21:
            string_print("F");
            break; 
        case 0x22:
            string_print("G");
            break; 
        case 0x23:
            string_print("H");
            break; 
        case 0x24:
            string_print("J");
            break; 
        case 0x25:
            string_print("K");
            break; 
        case 0x26:
            string_print("L");
            break; 
        case 0x27:
            string_print(";");
            break; 
        case 0x28:
            string_print("'");
            break; 
        case 0x29:
            string_print(" ");
            break; 
        case 0x2A:
            string_print("LShift");
            break; 
        case 0x2B:
            string_print("\\");
            break; 
        case 0x2C:
            string_print("Z");
            break; 
        case 0x2D:
            string_print("X");
            break; 
        case 0x2E:
            string_print("C");
            break; 
        case 0x2F:
            string_print("V");
            break; 
        case 0x30:
            string_print("B");
            break; 
        case 0x31:
            string_print("N");
            break; 
        case 0x32:
            string_print("M");
            break; 
        case 0x33:
            string_print(",");
            break; 
        case 0x34:
            string_print(".");
            break; 
        case 0x35:
            string_print("/");
            break; 
        case 0x36:
            string_print("RShift");
            break; 
        case 0x37:
            string_print("Keypad *");
            break; 
        case 0x38:
            string_print("LAlt");
            break; 
        case 0x39:
            string_print("Space");
            break;
        default:
            if (code <= 0x7F) {
                string_print("Unknown Key Down");
            } else
            if (code <= 0x39 + 0x80) {
                string_print("Key Up ");
                letter_print(code - 0x80);
            } else {
                string_print("Unknown Key Up");
            }
            break;
    }
}

static void keyboard_callback (registers_t *regs) {
    uint8_t scancode = byte_in(0x60);
    letter_print(scancode);
    newline_print();
}

void keyboard_init () {
    register_interrupt_handler(IRQ1, keyboard_callback);    
}
