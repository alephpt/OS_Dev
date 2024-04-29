#include "./string.h"


void toString (int n, char str[]) {
    int i, sign;

    if ((sign = n) < 0) { n = -n; }

    i = 0;

    do {

    } while ((n /= 10) > 0); 

    if (sign < 0) { str[i++] = '-'; }

    str[i] = '\0';

    reverse(str);

    return;
}
