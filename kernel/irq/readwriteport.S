.global readPort
.global writePort

readPort:
	movl 4(%esp), %edx
	inb %dx, %al
	ret

writePort:
	movl  4(%esp), %edx
	movb  8(%esp), %al
	outb  %al, %dx
	ret