/**
* @File vgastr.h
* @Date 2023-04-02
* @Description vga模式字符串输出头文件
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_INIT_LDR_VGA_STR_H
#define __BEETLE_OS_INIT_LDR_VGA_STR_H

#include "base_string.h"
#include "io.h"

namespace _Ldr {

    /*
     * BIOS中断调用 int 10H
     * AL寄存器存放 02H(颜色2种) 或 03H(颜色16种)，默认 03H
     * VESA 文本工作模式，屏幕分为25行80列，并映射到 0xb8000 地址处，
     * 每两个字节对应一个字符，一个字节为字符，另一个字节为字符颜色
     */
#define VGASTR_RAM_BASE (0xb8000)   // VGA显卡开始地址
#define VGASTR_RAM_END  (0xbffff)   // VGA显卡结束地址
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

    void InitCursor();
    void ClearScreen(u16_t srrv);
    void PutChar(char_t cr, size_t x, size_t y);
    void CloseCursor();
    void KPrint(_Base::CPtr<char_t> _str);
    void KError(_Base::CPtr<char_t> _error);

    struct Cursor {
        size_t memory_start;
        size_t memory_end;
        size_t cv_memory_addr;

        size_t pos_x;
        size_t pos_y;

        void setPos(u32_t _x, u32_t _y) {
            pos_x = _x;
            pos_y = _y;
        }

        void write(_Base::CPtr<char_t> _str);

        void currentPos(u32_t _flag);

        Cursor()
            : memory_start(VGASTR_RAM_BASE)
            , memory_end(VGASTR_RAM_END)
            , cv_memory_addr(0)
            , pos_x(0)
            , pos_y(0)
        {}
    };

}

#endif // __BEETLE_OS_INIT_LDR_VGA_STR_H
