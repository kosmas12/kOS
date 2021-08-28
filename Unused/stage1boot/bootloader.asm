# Copyright (c) 2021 The kOS authors.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software.
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

org 0x7c00

start: jmp boot

msg db "Loading kOS...", 0xA, 0xD, 0x0

boot:
    cli                               ; Disable interrupts

print:
    mov si, msg                       ; Move starting address of msg into SI
    cld                               ; Clear direction flags
    xor ax, ax                        ; Set AX to 0 (and set flags)
    mov ds, ax                        ; Set Data Segment Register to 0

showmessage:
    lodsb                             ; load byte at DS into AL, update (increment) SI
    or al, al                         ; Check if AL is 0
    jz load                           ; If 0, we're done printing so go ahead and load
    mov ah, 0x0E                      ; INT 0x13/AH=0x0E is teletype output
    mov bh, 0x00                      ; Page 0
    int 0x10                          ; Call BIOS to write character
    jmp showmessage                   ; Repeat for next character

load:
    mov al, 2                         ; Read 2 sectors (1 sector = 512 bytes)
    mov ch, 0                         ; Track 0
    mov cl, 2                         ; Read 2nd sector (1st sector is bootloader)
    mov dh, 0                         ; Head number

    ; Specify memory address to read boot disk to (ES:BX)
    mov bx, 0x500
    mov es, bx
    xor bx, bx                        ; Set BX to 0 (and set flags)

    mov ah, 0x2                       ; INT 0x13 with AH=0x2 means read sector
    int 0x13                          ; Call BIOS to read sector
    jmp 0x0000:0x5000                 ; Jump to sector

  ; Must be 512 bytes
  times 510 - ($-$$) db 0
  dw 0xAA55                           ; Boot Signature, last 2 bytes of image
