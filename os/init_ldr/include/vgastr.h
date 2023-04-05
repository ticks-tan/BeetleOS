/**
* @File vgastr.h
* @Date 2023-04-02
* @Description 字符串输出头文件
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_VGASTR_H
#define __BEETLE_OS_VGASTR_H

#define VGASTR_RAM_BASE (0xb8000)
#define VGASTR_RAM_END  (0xbffff)
#define VGADP_DFVL 0x0700
#define VGADP_HLVL 0x0f00
#define VGACTRL_REG_ADR 0x3d4
#define VGACTRL_REG_DAT 0x3d5
#define VGACURS_REG_INX 0x0a
#define VGACURS_CLOSE 0x20
#define VGACHAR_LR_CFLG 10
#define VGACHAR_DF_CFLG 0
#define VGASADH_REG_INX 0x0c
#define VGASADL_REG_INX 0x0d

#include "base_type.h"

char_t *numberk(char_t *str, size_t n, ssize_t base);
void clear_screen(u16_t srrv);
void put_one_char(char_t cr, size_t x, size_t y);
void close_curs();
void vsprintfk(char_t *buf, const char_t *fmt, va_list_t args);
void kprint(const char_t *fmt, ...);

struct Cursor
{
    size_t v_mem_start;
    size_t v_mem_end;
    size_t cv_mem_adr;

    size_t pos_x;
    size_t pos_y;

    void setPos(u32_t x, u32_t y) {
        pos_x = x;
        pos_y = y;
    }

    void write(Ptr<char_t> str);

    void currentPos(u32_t flag);

    Cursor()
        : v_mem_start(VGASTR_RAM_BASE)
        , v_mem_end(VGASTR_RAM_END)
        , cv_mem_adr(0)
        , pos_x(0)
        , pos_y(0)
    {}
};


#endif // __BEETLE_OS_VGASTR_H
