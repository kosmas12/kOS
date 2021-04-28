#include <timing.h>

void delay(int t) {
    volatile int i;
    volatile int j;

    for(i=0; i<t; i++)
        for (j = 0; j < 300000; j++)
            __asm__("NOP");
}
