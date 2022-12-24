#include <stdint.h>

unsigned char byte_in (uint16_t port) 
{
    unsigned char res;
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

void byte_out (uint16_t port, uint16_t data) 
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
    return;
}

unsigned short word_in (uint16_t port) 
{
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void word_out (uint16_t port, uint16_t data) 
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
    return;
}
