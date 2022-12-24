#include <stdint.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

void mem_cpy (char *source, char *dest, int nbytes);
int string_length (char s[]);
void reverse(char s[]);
void int_to_string(int n, char str[]);
