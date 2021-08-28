// Copyright (c) 2021 The kOS authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software.
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "GDT.h"

/* Our GDT, with 3 entries, and finally our special GDT pointer */
struct GDTEntry GDT[3];
struct GDTPtr gp;

/* Setup a descriptor in the Global Descriptor Table */
void GDTSetGate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    /* Setup the descriptor base address */
    GDT[num].baseLow = (base & 0xFFFF);
    GDT[num].baseMiddle = (base >> 16) & 0xFF;
    GDT[num].baseHigh = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    GDT[num].limitLow = (limit & 0xFFFF);
    GDT[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    GDT[num].granularity |= (gran & 0xF0);
    GDT[num].access = access;
}

/* Initializes GDT with 3 entries and applies changes */
void GDTInstall() {
    gp.limit = (sizeof(struct GDTEntry) * 3) - 1;
    gp.base = (unsigned int) &GDT;

    // Code segment
    GDTSetGate(0, 0, 0, 0, 0);

    GDTSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Data segment
    GDTSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Apply changes
    GDTFlush();
}
