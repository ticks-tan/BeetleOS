/**
* @File init_head.cc
* @Date 2023-04-02
* @Description GRUB头，将二极引导放入指定内存区域
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/

#include "initldr.h"

void InitHeadFile()
{
    _Ldr::InitCursor(); // 初始化光标
    _Ldr::CloseCursor();
    _Ldr::ClearScreen(VGADP_DFVL);

    _Ldr::WriteRealIntSaveFile();   // 放置调用BIOS中断获取的信息
    _Ldr::WriteLdrKernelFile();
}

namespace _Ldr
{
    using namespace _Base;

    void WriteRealIntSaveFile()
    {
        Ptr<fhdsc_t> fhdsc_start = FindFile("init_int_save.bin");
        if (nullptr == fhdsc_start) {
            KError("file not found : init_int_save.bin");
        }
        // 从映像文件中拷贝到物理内存 0x1000 处
        memcopy(
                Ptr<void>(REALDRV_PHY_ADDR),
                Ptr<void>(fhdsc_start->fhd_intsfsoff + LDR_FILE_ADDR),
                fhdsc_start->fhd_frealsz
                );
    }

    _Base::Ptr<fhdsc_t> FindFile(CPtr<char_t> _name)
    {
        Ptr<mlosrddsc_t> mrd_addrs = Ptr<mlosrddsc_t>(MRD_DSC_ADDR);
        if (mrd_addrs->mdc_endgic != MDC_END_GIC ||
            mrd_addrs->mdc_rv != MDC_RVGIC ||
            mrd_addrs->mdc_fhdnr < 2 ||
            mrd_addrs->mdc_filnr < 2)
        {
            KError("not found mrd_dsc");
        }

        Ptr<fhdsc_t> fhdsc_start = Ptr<fhdsc_t>(mrd_addrs->mdc_fhdbk_s + LDR_FILE_ADDR);

        for (u64_t i = 0; i < mrd_addrs->mdc_fhdnr; ++i) {
            if (strcmp(_name, fhdsc_start[i].fhd_name) == 0) {
                return &fhdsc_start[i];
            }
        }
        KError("file not found");
        return nullptr;
    }

    void WriteLdrKernelFile()
    {
        Ptr<fhdsc_t> fhdsc_start = FindFile("init_ldr_kernel.bin");
        if (nullptr == fhdsc_start) {
            KError("not found file : init_ldr_kernel.bin");
        }
        // 拷贝到物理地址 0x2000 处，汇编函数会跳转到此处运行
        // 存放二级引导主模块
        memcopy(
                Ptr<void>(ILDR_KERNEL_PHY_ADDR),
                Ptr<void>(fhdsc_start->fhd_intsfsoff + LDR_FILE_ADDR),
                fhdsc_start->fhd_frealsz
                );
    }

    void WriteShellFile()
    {
    }

    void WriteKernelFile()
    {
    }
}