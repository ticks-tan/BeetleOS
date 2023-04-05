/**
* @File fs_parse.h
* @Date 2023-04-02
* @Description 解析映像文件
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_INITLDR_FS_PARSE_H
#define __BEETLE_OS_INITLDR_FS_PARSE_H

int strcmpl(const char *a,const char *b);
int move_krlimg(machbstart_t* mbsp,u64_t cpyadr,u64_t cpysz);
void init_krlfile(machbstart_t* mbsp);
void init_defutfont(machbstart_t *mbsp);
fhdsc_t* get_fileinfo(char_t* fname,machbstart_t* mbsp);
void get_file_rpadrandsz(char_t *fname, machbstart_t* mbsp,u32_t* retadr,u32_t* retsz);
u64_t get_filesz(char_t* filenm,machbstart_t* mbsp);
u64_t get_wt_imgfilesz(machbstart_t* mbsp);
u64_t r_file_to_padr(machbstart_t* mbsp,u32_t f2adr,char_t* fnm);
void set_rwhdhdpack(rwhdpach_t* setp,u8_t sn,u16_t off,u16_t seg,u32_t lbal,u32_t lbah);
void* read_sector(u64_t sector);
void ret_mbr();
int is_part(dpt_t* isp);
u64_t ret_imgfilesz();

#endif // __BEETLE_OS_INITLDR_FS_PARSE_H
