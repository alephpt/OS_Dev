#include <stdint.h>

unsigned char byte_in (uint16_t port) { unsigned char res; asm("in %%dx, %%al" : "=a" (res) : "d" (port)); return res; }
void byte_out (uint16_t port, uint16_t data) { asm("out %%al, %%dx" : : "a" (data), "d" (port)); return; }
unsigned short word_in (uint16_t port) { unsigned short result; asm("in %%dx, %%ax" : "=a" (result) : "d" (port)); return result; }
void word_out (uint16_t port, uint16_t data) { asm("out %%ax, %%dx" : : "a" (data), "d" (port)); return; }
void dword_out (uint16_t port, uint32_t data) { asm("out %%eax, %%dx" : : "a" (data), "d" (port)); return; }
uint32_t dword_in (uint16_t port) { uint32_t result; asm("in %%dx, %%eax" : "=a" (result) : "d" (port)); return result; }
void io_wait () { asm("out %%al, $0x80" :); return; }
void io_halt () { asm("hlt"); return; }
void io_cli () { asm("cli"); return; }