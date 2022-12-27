#pragma once

#include <stdint.h>
#include <stddef.h>

#define NULL_P ((void*)0)
#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

void* alloc (int n);
void mem_cpy (char *source, char *dest, int nbytes);
void dynamicMemory_init ();
void* mem_alloc (size_t s);
void mem_free (void *p);
