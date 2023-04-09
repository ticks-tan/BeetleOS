/**
* @File check_cpu.cc
* @Date 2023-04-07
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/

#include "check_cpu.h"
#include "vga_str.h"
#include "fs.h"

namespace _Ldr {

    // 通过改写 eflags 寄存器第21位，观察位是否改变来判断是否支持 cpuid
    bool CheckCpuIdSupport()
    {
        volatile bool rets = false;
        __asm__ __volatile__(
                "pushfl \n\t"
                "popl %%eax \n\t"               // 获取 eflags 寄存器内容到 eax
                "movl %%eax,%%ebx \n\t"         // 保存副本到 ebx
                "xorl $0x0200000,%%eax \n\t"    // 改变值后重新写入 eflags 寄存器
                "pushl %%eax \n\t"
                "popfl \n\t"
                "pushfl \n\t"
                "popl %%eax \n\t"               // 再次获取到 eax
                "xorl %%ebx,%%eax \n\t"         // 比较两次值变化
                "jz 1f \n\t"
                "movl $1,%0 \n\t"               // 发生改变，支持
                "jmp 2f \n\t"
                "1: movl $0,%0 \n\t"
                "2: \n\t"
                : "=c"(rets)
                :
                : "memory"
                );
        return rets;
    }

    bool CheckCpuLongModeSupport()
    {
        volatile bool rets = false;
        __asm__ __volatile__(
                "movl $0x80000000,%%eax \n\t"
                "cpuid \n\t"
                "cmpl $0x80000001,%%eax \n\t"
                "setnb %%al \n\t"
                "jb 1f \n\t"
                "movl $0x80000001,%%eax \n\t"
                "cpuid \n\t"
                "bt $29,%%edx  \n\t" // long mode  support 位
                "setcb %%al \n\t"
                "1: \n\t"
                "movzx %%al,%%eax \n\t"
                : "=a"(rets)
                :
                : "memory"
                );
        return rets;
    }

    bool CheckCpu(_Base::Ptr<MachInfo> _info)
    {
        if (!CheckCpuIdSupport()) {
            KError("Your cpu not support cpuid! the os is die!");
            CLI_HALT();
        }
        if (!CheckCpuLongModeSupport()) {
            KError("Your cpu is not 64bit support, the os is die!");
            CLI_HALT();
        }
        _info->cpu_mode = 0x40;
        return true;
    }

    bool InitMemoryView(_Base::Ptr<MachInfo> _info)
    {
        _Base::Ptr<E820Map> e820map = nullptr;
        u32_t e820_count = 0;
        // 调用BIOS中断获取 E820 内存信息(开始地址，内存视图数量)
        E820Map::MMap(&e820map, &e820_count);
        if (e820_count == 0) {
            KError("E820 Map Info Not Found");
            return false;
        }
        // 在 E820 数组中查找内存，查看是否有满足最小内存要求的可用内存
        // 最小内存搜索开始内存为 16MB 处
        if (nullptr == E820Map::CheckMemoryInE820MapCanUsable(
                e820map, e820_count,
                0x100000, 0x8000000))
        {
            KError("Your computer memory is too low, the memory can't less than 128MB");
            return false;
        }
        _info->e820_phy_addr = u64_t(e820map);  // E820 开始物理内存
        _info->e820_phy_count = e820_count;     // E820 数组数量
        _info->e820_phy_size = e820_count * sizeof(E820Map);    // E820 数组总大小
        _info->memory_size = E820Map::GetAllMemorySize(e820map, e820_count);    // 总可用内存大小

        // 初始化 ACPI 信息
        MachInfo::InitAcpiRsdp(_info);

        return true;
    }


    bool InitKernelStackAddr(_Base::Ptr<MachInfo> _info)
    {
        // 判断栈空间是否与映像文件冲突 (0x8f000 + 0x1000 = 0x90000)
        // 如果冲突就会移动到与栈空间4KB对齐的下一个地址
        if (!MoveOSImageIfClash(_info, 0x8f000, 0x1001)) {
            KError("Kernel image move error");
            return false;
        }
        _info->kernel_stack_addr = KERNEL_STACK_PHY_ADDR;   // 0x90000
        _info->kernel_stack_size = KERNEL_STACK_SIZE;       // 0x1000 (4KB)

        return true;
    }

    bool InitKernelFile(_Base::Ptr<MachInfo> _info)
    {
        u64_t size = CopyOSFile2PhyAddr(_info, IMAGE_KERNEL_PHY_ADDR, "kernel.bin");
        if (size == 0) {
            KError("Can't move the kernel.bin file");
            return false;
        }
        _info->kernel_img_addr = IMAGE_KERNEL_PHY_ADDR;
        _info->kernel_img_size = size;
        _info->next_free_phy_addr = __ALIGN_4K(_info->kernel_img_addr + _info->kernel_img_size);
        _info->mb_kalldendpadr = _info->kernel_img_addr + _info->kernel_img_size;

        return true;
    }

    bool InitE820Map(_Base::Ptr<MachInfo> _info)
    {
        auto s_map = _Base::Ptr<E820Map>(_info->e820_phy_addr);
        u64_t size = _info->e820_phy_count;
        u64_t t_map = _info->next_free_phy_addr;
        if (!MoveOSImageIfClash(_info, t_map, (size * sizeof(E820Map)))) {
            KError("Move kernel image file error");
            return false;
        }
        // 拷贝到高地址
        _Base::memcopy(_Base::Ptr<void>(t_map), s_map, (size * sizeof(E820Map)));
        _info->e820_phy_addr = t_map;
        _info->e820_phy_size = size * sizeof(E820Map);
        _info->next_free_phy_addr = __ALIGN_4K(t_map + (size * sizeof(E820Map)));
        _info->mb_kalldendpadr = t_map + _info->e820_phy_size;
        return true;
    }

    // 初始化MMU页表
    bool InitMMUPage(_Base::Ptr<MachInfo> _info)
    {
        // 顶级页目录，512个条目，每个条目8字节，一共 4096 字节
        auto tp = _Base::Ptr<u64_t>(KERNEL_INIT_PAGE_PHY_ADDR);
        // 页目录指针，512个条目，每个条目8字节，一共 4096 字节
        auto pp = _Base::Ptr<u64_t>(KERNEL_INIT_PAGE_PHY_ADDR + 0x1000);
        // 页目录，512个条目
        auto page = _Base::Ptr<u64_t>(KERNEL_INIT_PAGE_PHY_ADDR + 0x2000);
        // 物理地址从 0 开始映射
        u64_t phy_addr = 0;

        // 移动映像文件，（一个顶级页目录，16个页目录指针，每个页目录包含 512 个 2MB 大小物理页面）
        if (!MoveOSImageIfClash(_info, KERNEL_INIT_PAGE_PHY_ADDR, (0x1000 * 16 + 0x2000)))
        {
            KError("Move kernel image file error");
            return false;
        }
        // 清空顶级页目录和页目录指针
        for (u32_t i = 0; i < PGENTY_SIZE; ++i) {
            tp[i] = 0;
            pp[i] = 0;
        }
        // 映射物理地址到虚拟地址
        for (u32_t i = 0; i < 16; ++i) {
            pp[i] = u64_t(page) | KPDPTE_RW | KPDPTE_P;
            for (u32_t ii = 0; ii < PGENTY_SIZE; ++ii) {
                //大页 KPDE_PS 2MB，可读写 KPDE_RW，存在 KPDE_P
                // 物理页2MB，页目录项指向2MB开始地址
                page[ii] = 0 | phy_addr | KPDE_PS | KPDE_RW | KPDE_P;
                // 物理地址加 2MB
                phy_addr += 0x200000;
            }
            page = _Base::Ptr<u64_t>(page + 0x1000);
        }
        // 让顶级页目录第 (KRNL_VIRTUAL_ADDRESS_START) >> KPML4_SHIFT) & 0x1ff 项与第0项指向同一个页目录指针
        // 长模式下，39 - 48 位是顶级目录索引，右移 39 位，且只保留 0 - 8 位（即 &0x1FF）
        // 可获得 0xffff 8000 0000 0000 在顶级目录中的索引项
        // 这样便可以让 0xffff800000000000～0xffff800400000000 和虚拟地址：0～0x400000000，
        // 访问到同一个物理地址空间 0～0x400000000，
        // 内核在启动初期，虚拟地址和物理地址要保持相同
        tp[(((KRNL_VIRTUAL_ADDRESS_START) >> KPML4_SHIFT) & 0x1ff)] = u64_t(u64_t(pp) | KPML4_RW | KPML4_P);
        tp[0] = (u64_t)(u64_t(pp) | KPML4_RW | KPML4_P);

        // 保存页表地址
        _info->mmu_page_phy_addr = u64_t(KERNEL_INIT_PAGE_PHY_ADDR);
        _info->subpages_len = u64_t(0x1000 * 16 + 0x2000);
        _info->phy_mem_map_size = u64_t(0x400000000);
        return true;
    }

}