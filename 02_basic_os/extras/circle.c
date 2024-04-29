#include "./circle.h"
#include "../drivers/display.h"

void drawCircle(int center_x, int center_y, int radius, uint8_t color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int pixel_x = center_x + x;
                int pixel_y = center_y + y;
                int offset = get_offset(pixel_x, pixel_y);
                char_set(' ', offset);  // Set character (pixel)
                char_set(color, offset + 1);  // Set color attribute
            }
        }
    }
}