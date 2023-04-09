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

__NO_MANGLE void init_ldr_header()
{
    _Ldr::InitCursor(); // 初始化光标
    _Ldr::CloseCursor();
    _Ldr::ClearScreen(VGA_DP_DF);

    _Ldr::WriteRealIntSaveFile();   // 放置 init_int_save.bin 文件到 0x1000(4KB) 处
    _Ldr::WriteLdrKernelFile();     // 放置 init_ldr_kernel.bin 文件到 0x200000(2MB) 处
}

namespace _Ldr
{
    using namespace _Base;

    void WriteRealIntSaveFile()
    {
        Ptr<ImageOSFileHDes> fhd_start = FindFile("init_int_save.bin");
        if (nullptr == fhd_start) {
            KError("Not found file: init_int_save.bin");
        }
        // 从映像文件中拷贝到物理内存 0x1000(4KB) 处
        memcopy(
                Ptr<void>(IMAGE_LDR_READ_INT_PHY_ADDR),
                Ptr<void>(fhd_start->offset_start + LDR_FILE_ADDR),
                fhd_start->file_real_size
                );
    }

    void WriteLdrKernelFile()
    {
        Ptr<ImageOSFileHDes> fhd_start = FindFile("init_ldr_kernel.bin");
        if (nullptr == fhd_start) {
            KError("Not found file : init_ldr_kernel.bin");
        }
        // 拷贝到物理地址 0x200000(2MB) 处，汇编函数会跳转到此处运行
        // 存放二级引导主模块
        memcopy(
                Ptr<void>(IMAGE_LDR_KERNEL_PHY_ADDR),
                Ptr<void>(fhd_start->offset_start + LDR_FILE_ADDR),
                fhd_start->file_real_size
                );
    }

    _Base::Ptr<ImageOSFileHDes> FindFile(CPtr<char_t> _name)
    {
        auto mrd_addrs = Ptr<ImageFileHDes>(MRD_DSC_ADDR);
        if (mrd_addrs->end_magic != IMAGE_OS_MDC_END_MAGIC ||
            mrd_addrs->version != IMAGE_OS_MDC_RV_MAGIC ||
            mrd_addrs->fhd_count < 2 ||
            mrd_addrs->file_count < 2)
        {
            return nullptr;
        }

        auto fhd_start = Ptr<ImageOSFileHDes>(mrd_addrs->fhd_start_offset + LDR_FILE_ADDR);

        for (u64_t i = 0; i < mrd_addrs->fhd_count; ++i) {
            if (strcmp(_name, fhd_start[i].file_name) == 0) {
                return &fhd_start[i];
            }
        }
        return nullptr;
    }

}