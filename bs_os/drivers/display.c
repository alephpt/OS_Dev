#include <stdint.h>
#include "./display.h"
#include "./io.h"
#include "../utility/memory.h"

void cursor_set (int offset) {
    offset /= 2;

    byte_out(VGA_CTRL, VGA_HIGH_OFFSET);
    byte_out(VGA_DATA, (unsigned char) (offset >> 8));
    byte_out(VGA_CTRL, VGA_LOW_OFFSET);
    byte_out(VGA_DATA, (unsigned char) (offset & 0xff));

    return;
}

int cursor_get () {
    byte_out(VGA_CTRL, VGA_HIGH_OFFSET);
    int offset = byte_in(VGA_DATA) << 8;
    byte_out(VGA_CTRL, VGA_LOW_OFFSET);
    offset += byte_in(VGA_DATA);
    return offset * 2;
}

void char_set (char character, int offset) {
    unsigned char *vidm = (unsigned char *) VIDEO_BUFFER;
    vidm[offset] = character;
    vidm[offset + 1] = WonB;
    return;
}

int get_row (int offset) { return offset / (2 * MAX_COLS); }
int get_offset (int col, int row) { return 2 * (row * MAX_COLS + col); }
int new_line (int offset) { return get_offset(0, get_row(offset) + 1); }

int scroll (int offset) {
    mem_cpy(
            (char *) (get_offset(0, 1) + VIDEO_BUFFER),
            (char *) (get_offset(0, 0) + VIDEO_BUFFER),
            MAX_COLS * (MAX_ROWS - 1) * 2
           );

    for (int col = 0; col < MAX_COLS; col++) {
        char_set(' ', get_offset(col, MAX_ROWS - 1));
    }

    return offset - 2 * MAX_COLS;
}

void string_print (char *string) {
    int offset = cursor_get();
    int i = 0;

    while (string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll(offset);
        }

        if (string[i] == '\n') {
            offset = new_line(offset);
        } else {
            char_set(string[i], offset);
            offset += 2;
        }
        i++;
    }

    cursor_set(offset);
    return;
}

void backspace_print () {
    int newCursor  = cursor_get() - 2;
    char_set(' ', newCursor);
    cursor_set(newCursor);
    return;
}

void newline_print () {
    int newOffset = new_line(cursor_get());

    if (newOffset >= MAX_ROWS * MAX_COLS * 2) {
        newOffset = scroll(newOffset);
    }

    cursor_set(newOffset);
    return;
}

void screen_clear() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; ++i) {
        char_set(' ', i * 2);
    }

    cursor_set(get_offset(0, 0));
    return;
}
