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

GDT_Pointer gdt_pointer;

static GDT_Entry gdt[3];

void GDT_Set_Gate(int number, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity)
{
    gdt[number].base_low    = (base & 0xFFFF);
    gdt[number].base_middle = (base >> 16) & 0xFF;
    gdt[number].base_high   = (base >> 24) & 0xFF;
    gdt[number].limit_low   = (limit & 0xFFFF);
    gdt[number].access      = access;

    gdt[number].granularity = ((limit >> 16) & 0x0F);
    gdt[number].granularity |= (granularity & 0xF0);
}

void GDT_Install()
{
    gdt_pointer.limit   = (sizeof(GDT_Entry) * 3) - 1;
    gdt_pointer.base    = (unsigned int)&gdt;

    GDT_Set_Gate(0, 0, 0, 0, 0);                // Code
    GDT_Set_Gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    GDT_Set_Gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data

    GDT_Flush();
}
