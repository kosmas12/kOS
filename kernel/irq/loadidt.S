.global loadIDT

loadIDT:
	mov 4(%esp), %edx
	lidt (%edx)
	sti 				// turn on interrupts
	ret