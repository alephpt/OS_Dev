#pragma once

#include <stdint.h>

unsigned char byte_in (uint16_t port);
void byte_out (uint16_t port, uint16_t data);
unsigned short word_in (uint16_t port);
void word_out (uint16_t port, uint16_t data);
