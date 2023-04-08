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
#include "vgastr.h"

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
            KPrint("Your cpu not support cpuid! the os is die!");
            CLI_HALT();
        }
        if (!CheckCpuLongModeSupport()) {
            KPrint("Your cpu is not 64bit support, the os is die!");
            CLI_HALT();
        }
        _info->cpu_mode = 0x40;
        return true;
    }

    void E820MMap(_Base::Ptr<E820Map*> _retemp, _Base::Ptr<u32_t> _retemnr)
    {
        real_addr_call_entry(RLINTNR(0), 0, 0);
        *_retemnr = *_Base::Ptr<u32_t>(E80MAP_NR);
        *_retemp = _Base::Ptr<E820Map>(_Base::Ptr<u32_t>(E80MAP_ADDR));
    }

    void InitMemory(_Base::Ptr<MachInfo> _info)
    {
        _Base::Ptr<E820Map> e820map;
        u32_t e820_count = 0;
        _info->ebda_phy_addr = get_acpi_bios_ebda();
        E820MMap(&e820map, &e820_count);
        if (e820_count == 0) {
            KPrint("no e820map");
        }
        if (nullptr == CheckE820MemorySize(e820map, e820_count, 0x100000, 0x8000000)) {
            KPrint("Your computer memory is too low, the memory can't less than 128MB");
        }
        _info->e820_phy_addr = u64_t(e820map);
        _info->e820_phy_count = e820_count;
        _info->e820_phy_size = e820_count * sizeof(E820Map);
        _info->memory_size = GetE820MemorySize(e820map, e820_count);
        MachInfo::InitAcpiRsdp(_info);
    }

    _Base::Ptr<E820Map> CheckE820MemorySize(_Base::Ptr<E820Map> _e8p,u32_t _enr,u64_t _sadr,u64_t _size)
    {
        u64_t len = _sadr + _size;
        if (_enr == 0 || _e8p == nullptr) {
            return nullptr;
        }
        for (u32_t i = 0; i < _enr; ++i) {
            if (_e8p[i].type == RAM_USABLE) {
                if ((_sadr >= _e8p[i].start_addr) && (len < (_e8p[i].start_addr + _e8p[i].size))) {
                    return &_e8p[i];
                }
            }
        }
        return nullptr;
    }

    u64_t GetE820MemorySize(_Base::Ptr<E820Map> _e8p, u32_t _count)
    {
        u64_t size = 0;
        if (_count == 0 || _e8p == nullptr) {
            return 0;
        }
        for (u32_t i = 0; i < _count; ++i) {
            if (_e8p[i].type == RAM_USABLE) {
                size += _e8p[i].size;
            }
        }
        return size;
    }

}