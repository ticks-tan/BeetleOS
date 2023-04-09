;; GRUB头汇编，一些固定格式
MBT_HDR_FLAGS	EQU 0x00010003
MBT_HDR_MAGIC	EQU 0x1BADB002
MBT2_MAGIC	EQU 0xe85250d6
global _start
extern init_ldr_header ; 假设有这个段，后面进行调用
[section .text]
[bits 32]
_start:
	jmp _entry
align 4
mbt_hdr:
	dd MBT_HDR_MAGIC
	dd MBT_HDR_FLAGS
	dd -(MBT_HDR_MAGIC+MBT_HDR_FLAGS)
	dd mbt_hdr
	dd _start
	dd 0
	dd 0
	dd _entry
	;
	; multiboot header
	;
ALIGN 8
mbhdr:
	DD	0xE85250D6
	DD	0
	DD	mhdrend - mbhdr
	DD	-(0xE85250D6 + 0 + (mhdrend - mbhdr))
	DW	2, 0
	DD	24
	DD	mbhdr
	DD	_start
	DD	0
	DD	0
	DW	3, 0
	DD	12
	DD	_entry
	DD      0
	DW	0, 0
	DD	8
mhdrend:

;; 关闭中断并设置GDT
_entry:
	cli ; 关闭中断

	in al, 0x70
	or al, 0x80
	out 0x70, al ; 关闭不可屏蔽中断

	lgdt [GDT_PTR] ; 加载GDT_PTR到GDT寄存器
	jmp dword 0x8:_32bits_mode ; 长跳转刷新cs寄存器

;; 初始化通用寄存器，栈寄存器，为C++程序运行做初始化
_32bits_mode:
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	xor edi, edi
	xor esi, esi
	xor ebp, ebp
	xor esp, esp
	mov esp, 0x7c00         ; 设置栈顶地址，0x7c00是GRUB程序开始地址
	call init_ldr_header    ; 调用该函数，在C程序中实现
	jmp 0x200000            ; 跳转到二级引导器主模块


;; GDT全局段描述符
GDT_START:
knull_dsc: dq 0
kcode_dsc: dq 0x00cf9e000000ffff
kdata_dsc: dq 0x00cf92000000ffff
k16cd_dsc: dq 0x00009e000000ffff
k16da_dsc: dq 0x000092000000ffff
GDT_END:
GDT_PTR:
GDTLEN	dw GDT_END-GDT_START-1	; GDT界限
GDTBASE	dd GDT_START