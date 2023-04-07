/**
* @File base_type.h
* @Date 2023-04-02
* @Description 内核使用的基本类型别名
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/

#ifndef __BEETLE_OS__BASE_BASE_TYPE_H
#define __BEETLE_OS__BASE_BASE_TYPE_H

/*------------------------------  typedef  ---------------------------------------*/

typedef bool bool_t;

typedef unsigned char u8_t;

typedef unsigned short u16_t;

typedef unsigned int u32_t;

typedef unsigned long long u64_t;


typedef signed char s8_t;

typedef signed short s16_t;

typedef signed int s32_t;

typedef signed long long s64_t;

typedef char char_t;
typedef char char8_t;
typedef unsigned char uchar_t;
typedef unsigned char uchar8_t;

typedef u64_t cpuflag_t;

typedef unsigned long size_t;
typedef signed long ssize_t;
typedef unsigned long address_t;

typedef char_t* va_list_t;

#endif // __BEETLE_OS__BASE_BASE_TYPE_H
