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
    __attribute__((section(".data"))) Cursor g_curs{};

    void InitCursor()
    {
        g_curs.memory_start = VGASTR_RAM_BASE;
        g_curs.memory_end = VGASTR_RAM_END;
        g_curs.cv_memory_addr = g_curs.pos_y = g_curs.pos_x = 0;
    }

    void ClearScreen(u16_t srrv)
    {
        g_curs.pos_y = g_curs.pos_x = 0;
        auto p = (_Base::Ptr<u16_t>)(VGASTR_RAM_BASE);
        for (u32_t i = 0; i < 2001; ++i) {
            p[i] = srrv;
        }
        CloseCursor();
    }

    void PutChar(char_t _ch, u32_t _x, u32_t _y)
    {
        size_t str_addr = VGASTR_RAM_BASE + (_x + (_y * 80 * 2));
        auto p = _Base::Ptr<char_t>(str_addr);
        *p = _ch;
    }
    void CloseCursor()
    {
        out_u8(VGACTRL_REG_ADR, VGACURS_REG_INX);
        out_u8(VGACTRL_REG_DAT, VGACURS_CLOSE);
    }
    void KPrint(_Base::CPtr<char_t> _str)
    {
        g_curs.write(_str);
    }

    void KError(_Base::CPtr<char_t> _error)
    {
        KPrint(_error);
        for (;;) {
            ;
        }
    }

    void Cursor::write(_Base::CPtr<char_t> _str)
    {
        size_t str_addr = pos_x + pos_y * 80 * 2;
        auto p_str_dst = _Base::Ptr<char_t>(memory_start + str_addr);
        bool findX = false;

        while (*_str) {
            if (*_str == 10) {
                findX = true;
                ++_str;
                if (*_str == 0) {
                    break;
                }
            }
            currentPos(VGACHAR_DF_CFLG);
            *p_str_dst = *_str++;
            p_str_dst += 2;
        }

        if (findX) {
            currentPos(VGACHAR_LR_CFLG);
        }
    }

    void Cursor::currentPos(u32_t _flag) {
        if (_flag == VGACHAR_LR_CFLG) {
            ++pos_y;
            pos_x = 0;
            if (pos_y > 24) {
                pos_y = 0;
                ClearScreen(VGADP_DFVL);
            }
            return;
        }
        if (_flag == VGACHAR_DF_CFLG) {
            pos_x += 2;
            if (pos_x > 159) {
                pos_x = 0;
                ++pos_y;
                if (pos_y > 24) {
                    pos_y = 0;
                    ClearScreen(VGADP_DFVL);
                }
                return;
            }
        }
    }

}
