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

// TODO: clean this up

#if defined(__linux__)
#error "You are not using a cross-compiler, this won't work"
#endif

#if !defined(__i386__)
#error "This kernel is designed for 32 bit systems, please use a compiler that targets i686"
#endif

#include <stdio.h>

#include "GDT/GDT.h"
#include "../IRQ/IDT.h"
#include "../Keyboard/Keyboard.h"
#include <Kernel/TerminalIO.h>

// Kernel entry point. Ignore any warnings saying this isn't used, it's called by the bootloader
void kernel_main(void) {
    terminalInit();

    GDTInstall();

    IDTInit();
    kbInit();

    // With our inits above, we can respond to user input despite the empty infinite loop
    while (1);

}

