;; 调用BIOS中断保存信息，BIOS实模式下，所以使用16位编译，放到 0x1000 内存处
%include "ldr_asm.inc"
global _start
[section .text]
[bits 16]
_start:
_16_mode:
	mov	bp,0x20 ; 指向 GDT 中第16位数据段描述符
	mov	ds, bp
	mov	es, bp
	mov	ss, bp
	mov	ebp, cr0
	and	ebp, 0xfffffffe
	mov	cr0, ebp ; CR0.P = 0 关闭保护模式
	jmp	0:real_entry ; 真正进入实模式
real_entry:
	mov bp, cs
	mov ds, bp
	mov es, bp
	mov ss, bp ; 重新设置实模式下段寄存器值
	mov sp, 08000h ; 设置栈
	mov bp,func_table
	add bp,ax
	call [bp] ; 调用寒暑表中函数，ax 是C函数参数传过来的 __attribute__((regparm(3)))
	cli
	call disable_nmi
	mov	ebp, cr0
	or	ebp, 1
	mov	cr0, ebp ; CRO.P = 1 开启保护模式
	jmp dword 0x8:_32bits_mode
[BITS 32]
_32bits_mode:
	mov bp, 0x10
	mov ds, bp
	mov ss, bp ; 重新设置保护模式下的段寄存器0x10是32位数据段描述符的索引
	mov esi,[PM32_EIP_OFF] ; 加载之前保存的 ESI
	mov esp,[PM32_ESP_OFF] ; 加载之前保存的 ESP
	jmp esi ; 回到 real_addr_call_entry 函数中

[BITS 16]
DispStr:
	mov bp,ax
	mov cx,23
	mov ax,01301h
	mov bx,000ch
	mov dh,10
	mov dl,25
	mov bl,15
	int 10h
	ret
cleardisp:
	mov ax,0600h     	;这段代码是为了清屏
	mov bx,0700h
	mov cx,0
	mov dx,0184fh
	int 10h			;调用的BOIS的10号
	ret

;; 获取内存视图
_get_memory_map:
	push ds
	push es
	push ss
	mov esi,0
	mov dword[E820MAP_NR],esi    ; 将 e820 数组数量放入 E820MAP_NR 宏定义的位置处
	mov dword[E820MAP_ADDR_ADDR],E820MAP_ADDR ; 将 E820MAP_ADDR 内存数据复制到 E820MAP_ADDR_ADDR处

	xor ebx,ebx
	mov edi,E820MAP_ADDR
loop:
	mov eax,0e820h  ; eax 寄存器赋值为 0xE820 ，e820 内存数组名称由来
	mov ecx,20
	mov edx,0534d4150h
	int 15h ; 调用 BIOS 15 号中断获取内存信息
	jc .1

	add edi,20
	cmp edi,E820MAP_ADDR+0x1000
	jg .1

	inc esi

	cmp ebx,0
	jne loop

	jmp .2

.1:
	mov esi,0

.2:
	mov dword[E820MAP_NR],esi
	pop ss
	pop es
	pop ds
	ret
_read:
	push ds
	push es
	push ss
	xor eax,eax
	mov ah,0x42
	mov dl,0x80
	mov si,RWHDPACK_ADR
	int 0x13
	jc  .err
	pop ss
	pop es
	pop ds
	ret
.err:
	mov ax,int131errmsg
	call DispStr
	jmp $
	pop ss
	pop es
	pop ds
	ret

_getvbemode:
        push es
        push ax
        push di
        mov di,VBEINFO_ADR
        mov ax,0
        mov es,ax
        mov ax,0x4f00
        int 0x10
        cmp ax,0x004f
        jz .ok
        mov ax,getvbmodeerrmsg
        call DispStr
        jmp $
 .ok:
        pop di
        pop ax
        pop es
        ret
_getvbeonemodeinfo:
        push es
        push ax
        push di
        push cx
        mov di,VBEMINFO_ADR
        mov ax,0
        mov es,ax
        mov cx,0x118
        mov ax,0x4f01
        int 0x10
        cmp ax,0x004f
        jz .ok
        mov ax,getvbmodinfoeerrmsg
        call DispStr
        jmp $
 .ok:
        pop cx
        pop di
        pop ax
        pop es
        ret
_setvbemode:
        push ax
        push bx
        mov bx,0x4118
        mov ax,0x4f02
        int 0x10
        cmp ax,0x004f
        jz .ok
        mov ax,setvbmodeerrmsg
        call DispStr
        jmp $
 .ok:
        pop bx
        pop ax
        ret
disable_nmi:
	push ax
	in al, 0x70     ; port 0x70NMI_EN_PORT
	or al, 0x80	; disable all NMI source
	out 0x70,al	; NMI_EN_PORT
	pop ax
	ret

func_table: ; 函数表
	dw _get_memory_map ; 获取内存视图 (偏移为 0)
	dw _read    ; 读取硬盘
        dw _getvbemode ; 获取显卡vbe模式
        dw _getvbeonemodeinfo ; 获取显卡vbe数据
        dw _setvbemode  ; 设置显卡vbe模式


int131errmsg: db     "int 13 read hdsk  error"
        db 0
getvbmodeerrmsg: db     "get vbemode err"
        db 0
getvbmodinfoeerrmsg: db     "get vbemodeinfo err"
                db 0
setvbmodeerrmsg: db     "set vbemode err"
        db 0
