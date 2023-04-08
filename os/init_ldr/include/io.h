/**
* @File io.h
* @Date 2023-04-07
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_INIT_LDR_IO_H
#define __BEETLE_OS_INIT_LDR_IO_H

#include "kernel_base.h"

namespace _Ldr
{
    static inline void out_u8(const u16_t _port, const u8_t _val)
    {
        __asm__ __volatile__(
                "outb %1, %0\n\t"
                :
                : "dN"(_port), "a"(_val)
                );
    }
    static inline u8_t in_u8(const u16_t _port)
    {
        u8_t val;
        __asm__ __volatile__(
                "inb %1, %0\n\t"
                : "=a"(val)
                : "dN"(_port)
                );
        return val;
    }

    static inline void out_u16(const u16_t _port, const u16_t _val)
    {
        __asm__ __volatile__(
                "outw %1, %0\n\t"
                :
                : "dN"(_port), "a"(_val)
                );
    }
    static inline u16_t in_u16(const u16_t _port)
    {
        u16_t val;
        __asm__ __volatile__(
                "inw %1, %0\n\t"
                : "=a"(val)
                : "dN"(_port)
                );
        return val;
    }

}

#endif // __BEETLE_OS_INIT_LDR_IO_H
