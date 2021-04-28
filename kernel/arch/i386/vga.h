//
// Created by kosmas on 23/3/21.
//

#ifndef KOS_VGA_H
#define KOS_VGA_H

enum VGAColors {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

/* Produce a VGA color */
static inline uint8_t VGAColor(enum VGAColors fg, enum VGAColors bg);

/* Produce a letter with foreground and background colors */
static inline uint16_t VGAEntry(unsigned char uc, uint8_t color);

#endif //KOS_VGA_H
