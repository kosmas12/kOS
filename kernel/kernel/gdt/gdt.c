/*
This file is part of kOS - An operating system made for fun
Copyright (C) 2021 Kosmas Raptis

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "gdt.h"

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
