#include <stdio.h>

#if defined(__is_libk)
#include <kernel/terminalio.h>
#endif

int putchar(int intc) {
#if defined(__is_libk)
	char c = (char) intc;
	terminalPutChar(c);
#endif
	return intc;
}
