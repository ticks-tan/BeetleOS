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


#define VGADP_DFVL 0x0700
#define VGADP_HLVL 0x0f00
#define VGASADH_REG_INX 0x0c
#define VGASADL_REG_INX 0x0d

/*
 * VGA 文字模式显示字符包括字符位和属性位，如下：
 * |------------------------------------------------------------------|
 * |               字符             |                 属性             |
 * |-------------------------------||---------------------------------|
 * | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 || 0 | 1 | 2 | 3 | 4 | 5 | 6 |  7  |
 * |               字符             ||      前景色    |   背景色   |闪烁位|
 * |------------------------------------------------------------------|
 *
 * > 属性最后一位可用作闪烁控制或者用作第 4 位背景色
 * > 如果其他属性位设置为 0 ，属性位第一位可用作控制下划线
 *
 * 实模式和保护模式下 VGA 文本缓冲区默认开始于物理地址 0xB8000 ，结束于 0xBFFFF
 * 最常用的文本模式是默认的 80 列 x 25 行或 80×25，具有 16 种颜色和 8×16 像素大字符
 * BIOS 中断号为 10 , AL 寄存器存放 0x02 或者 0x03
 *
 * VGA 文字模式颜色值表：
 * [name]	  [value]
 * ------------------
 *  Black	    0x0
 *  Blue	    0x1
 *  Green	    0x2
 *  Cyan	    0x3
 *  Red	        0x4
 *  Magenta	    0x5
 *  Brown	    0x6
 *  Gray	    0x7
 *  DarkGray	0x8
 *  BrightBlue	0x9
 *  BrightGreen	0xA
 *  BrightCyan	0xB
 *  BrightRed	0xC
 *  BrightMagenta	0xD
 *  Yellow	    0xE
 *  White	    0xF
 * -----------------
 *
 * 参考文献 [1](https://en.wikipedia.org/wiki/VGA_text_mode)
 *
 */
#define VGA_TXT_COLOR_BLACK     (0x0)
#define VGA_TXT_COLOR_BLUR      (0x1)
#define VGA_TXT_COLOR_GREEN     (0x2)
#define VGA_TXT_COLOR_CYAN      (0x3)
#define VGA_TXT_COLOR_RED       (0x4)
#define VGA_TXT_COLOR_MAGENTA   (0x5)
#define VGA_TXT_COLOR_BROWN     (0x6)
#define VGA_TXT_COLOR_GRAY      (0x7)
#define VGA_TXT_COLOR_DARK_GRAY     (0x8)
#define VGA_TXT_COLOR_BRIGHT_BLUE   (0x9)
#define VGA_TXT_COLOR_BRIGHT_GREEN  (0xA)
#define VGA_TXT_COLOR_BRIGHT_CYAN   (0xB)
#define VGA_TXT_COLOR_BRIGHT_RED    (0xC)
#define VGA_TXT_COLOR_BRIGHT_MAGENTA    (0xD)
#define VGA_TXT_COLOR_YELLOW    (0xE)
#define VGA_TXT_COLOR_BRIGHT_WHITE  (0xF)

#define MAKE_VGA_COLOR(b,f) ((b << 4) | f)

#define VGA_TXT_RAM_START   (0xb8000)   // VGA显卡开始地址
#define VGA_TXT_RAM_END     (0xbffff)   // VGA显卡结束地址
#define VGA_CHAR_LF 10  // 换行符
#define VGA_CHAR_DF 0   // 空字符

#define VGA_CTRL_REG_ADR 0x3d4
#define VGA_CTRL_REG_DAT 0x3d5
#define VGA_CURSOR_REG_INX 0x0a
#define VGA_CURSOR_CLOSE 0x20


namespace _Ldr {

    // VGA文本模式字符
    struct VGAAttr
    {
        char8_t attr;

    public:
        VGAAttr(u8_t _fg, u8_t _bg)
            : attr(MAKE_VGA_COLOR(_bg, _fg))
        {}
        static VGAAttr Default() {
            return VGAAttr{VGA_TXT_COLOR_BRIGHT_WHITE, VGA_TXT_COLOR_BLACK};
        }

    } __TYPE_ALIGN; // VGAAttr

    // VGA文本模式光标
    struct VgaCursor {
        size_t memory_start;    // 字符内存开始地址
        size_t memory_end;      // 字符内存结束地址
        size_t cv_memory_addr;  // 暂定

        /*
         * ----- x
         * |
         * |
         * y
         *
         */
        size_t x;
        size_t y;

    public:
        void setPos(u32_t _x, u32_t _y) {
            x = _x;
            y = _y;
        }
        size_t getOffset() const {
            return (memory_start + x + (y * 80 * 2));
        }

        // 写字符串，默认黑底白字
        void write(_Base::CPtr<char_t> _str, VGAAttr _attr = VGAAttr::Default());
        // 写一个字符
        void putChar(char_t _ch, VGAAttr _attr = VGAAttr::Default());
        // 自动设置当前光标位置
        void setCurrentPos(u32_t _flag);

        VgaCursor()
            : memory_start(VGA_TXT_RAM_START)
            , memory_end(VGA_TXT_RAM_END)
            , cv_memory_addr(0)
            , x(0)
            , y(0)
        {}
    }; // VGACursor


    // 初始化全局光标
    void InitCursor();
    // 清理屏幕
    void ClearScreen(u16_t _ch);
    // 显示一个字符
    void PutChar(char_t _ch, VGAAttr _attr);
    // 关闭光标
    void CloseCursor();
    // 打印
    extern void KPrint(_Base::CPtr<char_t> _str);
    // 错误输出
    [[noreturn]] extern void KError(_Base::CPtr<char_t> _error);

}

#endif // __BEETLE_OS_INIT_LDR_VGA_STR_H
