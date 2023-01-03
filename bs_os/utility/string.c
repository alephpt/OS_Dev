#include <stdint.h>
#include "./int.h"
#include "../drivers/display.h"

int str_len (char s[]) {
    int i = 0;
    
    while(s[i] != '\0') { ++i; }

    return i;
}

void reverse (char s[]) {
    int ch, i, j;

    for (i = 0, j = str_len(s) - 1; i < j; i++, j--) {
        ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }

    return;
}

void append (char *s, char n) {
    int len = str_len(s);

    s[len] = n;
    s[len + 1] = '\0';

    return;
}

int str_comp (char s1[], char s2[]) {
    int i;
    
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') {
            return 0;
        }
    }
    // is this supposed to be length? :thonks:
    return s1[i] - s2[i];
}

char* str_strip (char *str) {
    char *newStr;
    int strlen = str_len(str);

    for (int i = 0; i < strlen; i++) {
        newStr[i] = str[i];
    }

    return newStr;
}