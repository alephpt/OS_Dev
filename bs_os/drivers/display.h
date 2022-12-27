#pragma once

#define VIDEO_BUFFER 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WonB 0x0f
#define VGA_CTRL 0x3d4
#define VGA_DATA 0x3d5
#define VGA_HIGH_OFFSET 0x0e
#define VGA_LOW_OFFSET 0x0f

int scroll (int offset);
void string_print (char *string);
void backspace_print ();
void newline_print ();
void screen_clear ();
