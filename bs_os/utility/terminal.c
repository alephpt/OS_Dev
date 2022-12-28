#include <stdbool.h>
#include "../drivers/display.h"
#include "./string.h"

typedef struct {
    const char* start;
    const char* current;
} Scanner;

typedef enum {
    SHUTDOWN,
    DIZZ,
    TEST,
} commandVals;

Scanner scanner;

int parseInput (char in[]) {
    if (str_comp(in, "SHUTDOWN") == 0) {
        return SHUTDOWN;
    } else 
    if (str_comp(in, "DIZZ") == 0) {
        return DIZZ;
    } else 
    if (str_comp(in, "TEST") == 0) {
        return TEST;
    } 

    return -1;    
}

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
    if (str_comp(input, "TEST") == 0) {
        string_print("This Test Worked!\n");
    } else 
    if (str_comp(input, "SHUTDOWN") == 0) {
        string_print("Shutting Down. Goodbye!\n");
        asm volatile("hlt");
    } else 
    if (str_comp(input, "DIZZ") == 0) {
        string_print("Gae!\n");
    } else 
    {
        string_print("Unknown command: ");
        string_print(input);
    }
    
    string_print("\n > ");

    return;

    return;
}
