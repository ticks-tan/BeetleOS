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

char *numberk(char_t *str, uint_t n, sint_t base);
void clear_screen(u16_t srrv);
void put_one_char(char_t cr, uint_t x, uint_t y);
void close_curs();
void vsprintfk(char_t *buf, const char_t *fmt, va_list_t args);
void kprint(const char_t *fmt, ...);

struct Cursor
{
    uint_t vmem_s;
    uint_t vmem_e;
    uint_t cvmem_adr;

    uint_t pos_x;
    uint_t pos_y;

    Cursor_t();

    void setPos(u32_t x, u32_t y);
    void write(Ptr<chat_t> str);

    void currentPos(u32_t flag)
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
        return;
    }

};



#endif // __BEETLE_OS_VGASTR_H
