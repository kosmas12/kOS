#include "vga.h"

static inline uint8_t VGAColor(enum VGAColors fg, enum VGAColors bg) {
    return fg | bg << 4;
}

static inline uint16_t VGAEntry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}