#include <stdint.h>

unsigned char byte_in (uint16_t port) 
{
    unsigned char res;
    asm("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

void byte_out (uint16_t port, uint16_t data) 
{
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
    return;
}

unsigned short word_in (uint16_t port) 
{
    unsigned short result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void word_out (uint16_t port, uint16_t data) 
{
    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
    return;
}
