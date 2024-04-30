#include "./circle.h"

int getOffset(int x, int y) {
    return 2 * (y * 80 + x);
}

void charSet(char c, int offset) {
    char *video_memory = (char *) 0xb8000;
    video_memory[offset] = c;
}

void drawCircle(int center_x, int center_y, int radius, uint8_t color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int pixel_x = center_x + x;
                int pixel_y = center_y + y;
                int offset = getOffset(pixel_x, pixel_y);
                charSet(' ', offset);  // Set character (pixel)
                charSet(color, offset + 1);  // Set color attribute
            }
        }
    }
}