/**
* @File vgastr.cc
* @Date 2023-04-02
* @Description 字符串输出
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#include "vgastr.h"

__attribute__((section(".data"))) Cursor g_curs{};


void Cursor::write(Ptr<char_t> str)
{
    size_t str_addr = pos_x + pos_y * 80 * 2;
    auto p_str_dst = Ptr<char_t>(v_mem_start + str_addr);
    u32_t findX = 0;

    while (*str) {
        if (*str == 10) {
            findX = 1;
            ++str;
            if (*str == 0) {
                break;
            }
        }

        currentPos(VGACHAR_DF_CFLG);

        *p_str_dst = *str++;
        p_str_dst += 2;
    }

    if (findX == 1) {
        currentPos(VGACHAR_LR_CFLG);
    }
}

void Cursor::currentPos(u32_t flag)
{
    if (flag == VGACHAR_LR_CFLG) {
        ++this->pos_y;
        this->pos_x = 0;
        if (this->pos_y > 24) {
            this->pos_y = 0;
            clear_screen(VGADP_DFVL);
        }
        return;
    }
    if (flag == VGACHAR_DF_CFLG) {
        this->pos_x += 2;
        if (this->pos_x > 159) {
            this->pos_x = 0;
            ++this->pos_y;
            if (this->pos_y > 24) {
                this->pos_y = 0;
                clear_screen(VGADP_DFVL);
            }
            return;
        }
    }
}

// 转换数字
char_t *numberk(char_t *str, size_t n, ssize_t base)
{
    volatile Ptr<char_t> p;

    return str;
}

void clear_screen(u16_t srrv)
{
    g_curs.setPos(0, 0);

    auto p = Ptr<u16_t>(VGASTR_RAM_BASE);

    for (u32_t i = 0; i < 2001; ++i) {
        p[i] = srrv;
    }

    close_curs();
}

void put_one_char(char_t cr, size_t x, size_t y)
{
    auto addr = Ptr<char_t>(VGASTR_RAM_BASE + (x + (y * 80 * 2)));
    *addr = cr;
}

void close_curs()
{
}

Ptr<char_t> _strcopy(Ptr<char_t> target, Ptr<char_t> source)
{
    while (*source) {
        *target = *source;
        ++target;
        ++source;
    }
    return target;
}

void vsprintfk(Ptr<char_t> buf, Ptr<const char_t> fmt, va_list_t args)
{
    auto p = Ptr<char_t>(buf);
    va_list_t next_arg = args;
    while (*fmt) {
        if (*fmt != '%') {
            *p++ = *fmt++;
            continue;
        }
        ++fmt;
        switch (*fmt) {
            case 'd':
                break;
        }
    }
}

void kprint(const char_t *fmt, ...)
{

}
