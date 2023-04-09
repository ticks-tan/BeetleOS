/**
* @File macro.h
* @Date 2023-04-05
* @Description OS中需要用到的基础宏
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_BASE_MACRO_H
#define __BEETLE_OS_BASE_MACRO_H

/*------------------------------  define  ---------------------------------------*/


/*----- 编译器 -----*/
// GCC
#ifdef __GNUC__
#define __COMPILER_GCC __GNUC__
#endif
// MSVC
#ifdef _MSC_VER
#define __COMPILER_MSVC
#endif


// 结构体字节对齐
#ifdef __COMPILER_GCC
#define __TYPE_GCC_ALIGN_MIN(X) __attribute__((aligned(X)))
#define __TYPE_ALIGN __attribute__((packed))
#endif

// 对齐
#define __ALIGN(x, a) (((x) + (a) - 1) & ~((a) - 1))
// 4K 对齐
#define __ALIGN_4K(x)  __ALIGN(x,0x1000)

// 使用寄存器 eax、ebx、ecx 等传递参数，而不是栈，X为最大寄存器使用数量
#define __REG_CALL(X) __attribute__((regparm(X)))

// 不混淆函数或变量名称
#define __NO_MANGLE extern "C"

// 让变量位于某个段
#define __SECTION(Name) __attribute__((section(Name)))

// 无限循环
#define __INFINITY_LOOP { volatile bool _i = false; do { _i = true; }while(true); }

#endif // __BEETLE_OS_BASE_MACRO_H
