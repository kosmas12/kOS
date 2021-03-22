; kOS - An operating system made for fun
; Copyright (C) 2021  Kosmas Raptis
;
; This program is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version 2
; of the License, or (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

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