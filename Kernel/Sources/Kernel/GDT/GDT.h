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

#pragma once

//#pragma pack (push, 1)
typedef struct __attribute__((__packed__))  GDT_Entry
{
    unsigned short  limit_low;
    unsigned short  base_low;
    unsigned char   base_middle;
    unsigned char   access;
    unsigned char   granularity;
    unsigned char   base_high;
} __attribute__((__packed__)) GDT_Entry;

typedef struct __attribute__((__packed__)) GDT_Pointer
{
    unsigned short  limit;
    unsigned int    base;
} __attribute__((__packed__)) GDT_Pointer;
//#pragma pack (pop)

extern void GDT_Flush();

void GDT_Set_Gate(int number, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity);
void GDT_Install();
