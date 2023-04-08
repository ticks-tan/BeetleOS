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

namespace _Ldr {

    // 全局变量，位于数据段
    __SECTION(".data") VgaCursor g_vga_cursor{};

    void InitCursor()
    {
        g_vga_cursor.memory_start = VGA_TXT_RAM_START;
        g_vga_cursor.memory_end = VGA_TXT_RAM_END;
        g_vga_cursor.cv_memory_addr = g_vga_cursor.y = g_vga_cursor.x = 0;
    }

    void ClearScreen(u16_t _ch)
    {
        g_vga_cursor.y = g_vga_cursor.x = 0;
        auto p = (_Base::Ptr<u16_t>)(VGA_TXT_RAM_START);
        // 2000 个字符 ？？
        for (u32_t i = 0; i < 2001; ++i) {
            p[i] = _ch;
        }
        CloseCursor();
    }

    void PutChar(char_t _ch, VGAAttr _attr = VGAAttr::Default())
    {
        g_vga_cursor.putChar(_ch, _attr);
    }

    void CloseCursor()
    {
        out_u8(VGA_CTRL_REG_ADR, VGA_CURSOR_REG_INX);
        out_u8(VGA_CTRL_REG_DAT, VGA_CURSOR_CLOSE);
    }

    void KPrint(_Base::CPtr<char_t> _str)
    {
        g_vga_cursor.write(_str);
    }

    [[noreturn]]
    void KError(_Base::CPtr<char_t> _error)
    {
        KPrint(_error);
        for (;;) {
            ;
        }
    }

    void VgaCursor::write(_Base::CPtr<char_t> _str, VGAAttr _attr)
    {
        auto str_dst = _Base::Ptr<char_t>(getOffset());
        bool findX = false;

        while ((*_str) != 0) {
            // 换行
            if ((*_str) == VGA_CHAR_LF) {
                findX = true;
                ++_str;
                if ((*_str) == 0) {
                    break;
                }
            }
            // 普通
            setCurrentPos(VGA_CHAR_DF);
            // 写字符
            *str_dst = (*_str);
            ++str_dst; ++_str;
            // 写字符属性
            *str_dst = _attr.attr;
            ++str_dst; ++_str;
        }

        if (findX) {
            setCurrentPos(VGA_CHAR_LF);
        }
    }

    void VgaCursor::setCurrentPos(u32_t _flag)
    {
        // 换行
        if (_flag == VGA_CHAR_LF) {
            ++y;
            x = 0;
            if (y > 24) {
                y = 0;
                ClearScreen(VGADP_DFVL);
            }
            return;
        }
        if (_flag == VGA_CHAR_DF) {
            x += 2;
            if (x > 159) {
                x = 0;
                ++y;
                if (y > 24) {
                    y = 0;
                    ClearScreen(VGADP_DFVL);
                }
                return;
            }
        }
    }

    void VgaCursor::putChar(char_t _ch, VGAAttr _attr)
    {
        char_t str[2] = {_ch, '\0'};
        write(str, _attr);
    }

}
