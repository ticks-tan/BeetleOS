/**
* @File graph.h
* @Date 2023-04-02
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_GRAPH_H
#define __BEETLE_OS_GRAPH_H

void init_graph(machbstart_t* mbsp);
void graph_t_init(graph_t* initp);
u32_t vfartolineadr(u32_t vfar);
void init_kinitfvram(machbstart_t* mbsp);
void get_vbemode(machbstart_t* mbsp);
void get_vbemodeinfo(machbstart_t* mbsp);
void set_vbemodeinfo();
void bga_write_reg(u16_t index, u16_t data);
u16_t bga_read_reg(u16_t index);
u32_t get_bgadevice();
u32_t chk_bgamaxver();
void init_bgadevice(machbstart_t* mbsp);
u32_t utf8_to_unicode(utf8_t* utfp,int* retuib);

#endif // __BEETLE_OS_GRAPH_H
