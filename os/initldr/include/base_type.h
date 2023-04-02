/**
* @File base_type.h
* @Date 2023-04-02
* @Description 内核使用的基本类型别名
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_BASE_TYPE_H
#define __BEETLE_OS_BASE_TYPE_H

/*------------------------------  typedef  ---------------------------------------*/

typedef bool bool_t;

typedef unsigned char u8_t;

typedef unsigned short u16_t;

typedef unsigned int u32_t;

typedef unsigned long long u64_t;


typedef signed char i8_t;

typedef signed short i16_t;

typedef signed int i32_t;

typedef signed long long i64_t;


typedef signed char char_t;
typedef unsigned char uchar_t;

typedef u64_t cpuflag_t;

typedef unsigned long size_t;
typedef signed long ssize_t;
typedef unsigned long address_t;

/*------------------------------  template  ---------------------------------------*/

template<typename T>
using Ptr = T*;

template<typename T>
using Ref = T&;

#define __Extern_C \
#ifdef __cplusplus \
    extern "C" { \
#endif


/*------------------------------  define  ---------------------------------------*/

#define Extern_C_Block(statement) \
extern "C" {                \
    statement               \
};

#define Extern_C_Line extern "C"

#define ALIGN(x, a) (((x) + (a) - 1) & ~((a) - 1))


#endif // __BEETLE_OS_BASE_TYPE_H
