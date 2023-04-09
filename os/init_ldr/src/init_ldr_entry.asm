;; 二极引导器入口汇编
%include "ldr_asm.inc"
global _start
global real_addr_call_entry
global IDT_PTR
extern ldr_kernel_entry ; 二级引导器C++函数
[section .text]
[bits 32]
_start:
_entry:
	cli
	lgdt [GDT_PTR]
	lidt [IDT_PTR]
	jmp dword 0x8:_32bits_mode

_32bits_mode:
	mov ax, 0x10	; 数据段选择子(目的)
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	xor edi,edi
	xor esi,esi
	xor ebp,ebp
	xor esp,esp
	mov esp,0x90000
	call ldr_kernel_entry
	xor ebx,ebx
	jmp 0x2000000
	jmp $


real_addr_call_entry:
	pushad
	push    ds
	push    es
	push    fs
	push    gs
	call save_eip_jmp
	pop	gs
	pop	fs
	pop	es
	pop	ds
	popad
	ret
save_eip_jmp:
	pop esi
	mov [PM32_EIP_OFF],esi
	mov [PM32_ESP_OFF],esp
	jmp dword far [cpmty_mode]
cpmty_mode:
	dd 0x1000 ; 跳转到 0x1000 处，该处存放的是 real_int_save.asm 函数，该函数处理实际的BIOS中断调用
	dw 0x18
	jmp $

GDT_START:
knull_dsc: dq 0
kcode_dsc: dq 0x00cf9a000000ffff ;a-e
kdata_dsc: dq 0x00cf92000000ffff
k16cd_dsc: dq 0x00009a000000ffff ;a-e
k16da_dsc: dq 0x000092000000ffff
GDT_END:

GDT_PTR:
GDTLEN	dw GDT_END-GDT_START-1	;GDT界限
GDTBASE	dd GDT_START

IDT_PTR:
IDTLEN	dw 0x3ff
IDTBAS	dd 0