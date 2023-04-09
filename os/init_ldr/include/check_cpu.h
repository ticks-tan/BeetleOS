/**
* @File check)cpu.h
* @Date 2023-04-07
* @Description 检查cpu
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_INIT_LDR_CHECK_CPU_H
#define __BEETLE_OS_INIT_LDR_CHECK_CPU_H

#include "ldr_type.h"

#define EMAP_PTR E80MAP_ADR
#define EMAP_NR_PTR E80MAP_NR

#define BASE_MEM_SZ 0x3f80000

#define PML4T_BADR 0x20000
#define PDPTE_BADR 0x21000

#define PDE_BADR 0x22000
#define PTE_BADR 0x23000

#define PG_SIZE 512

//			页面目录表及各种属性状态
/*___________________________________________________________
  |______________________|_|_|_|_|_|_|_|_|_|_|_|_|		   pagedirectorytble
			      | | | | | | | | | | | |		   BIT
			      | | | | | | | | | | | |_____________Bit0 P　0不存在/1存在
			      | | | | | | | | | | |_______________Bit1 R/W　0只读/1可读可写
			      | | | | | | | | | |_________________Bit2 U/S　0管理特权/1用户特权
			      | | | | | | | | |___________________Bit3 PWT　0回写/1直写  （页表）
			      | | | | | | | |_____________________Bit4 PCD　0高速缓存/1禁止高速缓存（页表）
			      | | | | | | |_______________________Bit5 A　0cpu未访问/1cpu访问置1但不清0
			      | | | | | |_________________________Bit6 D　页目录中保留为０
			      | | | | |___________________________Bit7 PS　0页大小4KB/1页大小为４MB
			      | | | |_____________________________Bit8 G 全局页为1时tlb中的页目录不失效忽略
			      | | |_______________________________Bit9-----\
			      | |_________________________________Bit10     |可供系统软件自由使用
			      |___________________________________Bit11----/
*/
//			页表及各种属性状态
/*___________________________________________________________
  |______________________|_|_|_|_|_|_|_|_|_|_|_|_|		   pagetable
			      | | | | | | | | | | | |		   BIT
			      | | | | | | | | | | | |_____________Bit0 P　0不存在/1存在（页）
			      | | | | | | | | | | |_______________Bit1 R/W　0只读/1可读可写 （页）
			      | | | | | | | | | |_________________Bit2 U/S　0管理特权/1用户特权（页）
			      | | | | | | | | |___________________Bit3 PWT　0回写/1直写  （页）
			      | | | | | | | |_____________________Bit4 PCD　0高速缓存/1禁止高速缓存（页）
			      | | | | | | |_______________________Bit5 A　0cpu未访问/1cpu访问置1但不清0 （页）
			      | | | | | |_________________________Bit6 D　页表中脏位cpu写入时会自动置位（页）
			      | | | | |___________________________Bit7 PTA　0　（页）页属性　奔腾3开始支持
			      | | | |_____________________________Bit8 G 全局页为1时tlb中的页不失效忽略（页）
			      | | |_______________________________Bit9-----\
			      | |_________________________________Bit10     |可供系统软件自由使用
			      |___________________________________Bit11----/
*/



#define PDT_S_PNT	0x1
#define PDT_S_RW	0x2
#define PDT_S_US	0x4
#define PDT_S_PWT	0x8
#define PDT_S_PCD	0x10
#define PDT_S_ACC	0x20
#define PDT_S_DITYRE	0x40
#define PDT_S_SIZE	0x80
#define PDT_S_GLOP	0x100

#define PT_S_PNT	0x1
#define PT_S_RW		0x2
#define PT_S_US		0x4
#define PT_S_PWT	0x8
#define PT_S_PCD	0x10
#define PT_S_ACC	0x20
#define PT_S_DITY	0x40
#define PT_S_PTARE	0x80
#define PT_S_GLOP	0x100

typedef unsigned long long pt64_t;

// 暂停CPU执行
#define CLI_HALT() __asm__ __volatile__("cli; hlt": : :"memory")

namespace _Ldr
{

    // 检查cpu是否支持 cpuid
    bool CheckCpuIdSupport();
    // 检查cpu是否支持长模式，系统关键
    bool CheckCpuLongModeSupport();
    // 检查cpu
    bool CheckCpu(_Base::Ptr<MachInfo> _info);

    // 初始化获取内存布局信息
    bool InitMemoryView(_Base::Ptr<MachInfo> _info);

    // 初始化内核栈地址
    bool InitKernelStackAddr(_Base::Ptr<MachInfo> _info);

    // 初始化放置内核文件到高地址空间
    bool InitKernelFile(_Base::Ptr<MachInfo> _info);

    // 初始化E820数组
    bool InitE820Map(_Base::Ptr<MachInfo> _info);

    // 初始化MMU页表
    bool InitMMUPage(_Base::Ptr<MachInfo> _info);

}

#endif // __BEETLE_OS_INIT_LDR_CHECK_CPU_H
