#include <stdint.h>

void mem_cpy (char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

int string_length(char s[]) {
    int i = 0;

    while (s[++i] != '\0');

    return i;
}

void reverse (char s[]) {
    int ch, i, j;

    for (i = 0, j = string_length(s) - 1; i < j; i++, j--) {
        ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }

    return;
}

void int_to_string (int n, char str[]) {
    int i, sign;

    if ((sign = n) < 0) { n = -n; }

    i = 0;

    do { 
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) { str[i++] = '-'; }

    str[i] = '\0';

    reverse(str);

    return;
}
