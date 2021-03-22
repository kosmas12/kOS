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

; Multiboot header stuff
MBALIGN  equ  1
MEMINFO  equ  2
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot

align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 16

stack_bottom:
resb 16384  ; 16KiB stack
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top
	extern kernel_main
	call kernel_main
	cli
.hang: hlt
	jmp .hang
.end: