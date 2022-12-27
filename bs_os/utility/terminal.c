#include <stdbool.h>
#include "../drivers/display.h"
#include "./string.h"

bool backspace (char s[]) {
    int len = str_len(s);

    if (len > 0) {
        s[len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

void execute_input (char *input) {
    if (str_comp(input, "SHUTDOWN") == 0) {
        string_print("Shutting Down. Goodbye!\n");
        asm volatile("hlt");
    }

    string_print("Unknown command: ");
    string_print(input);
    string_print("\n > ");

    return;
}
