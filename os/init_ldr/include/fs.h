/**
* @File fs.h
* @Date 2023-04-09
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_INIT_LDR__FS_H
#define __BEETLE_OS_INIT_LDR__FS_H

#include "ldr_type.h"

namespace _Ldr
{
    // 检查地址与是否与已有文件地址冲突
    inline bool CheckAddrIsNotClash(u64_t _start_addr, u64_t _start_len, u64_t _kernel_addr, u64_t _kernel_len);
    // 检查地址是否可用
    bool CheckAddrIsOk(_Base::Ptr<MachInfo> _info, u64_t _check_addr, u64_t _check_size);
    // 查看栈空间是否与内核镜像冲突，如果冲突就将内核文件移动到更高的地址
    bool MoveOSImageIfClash(_Base::Ptr<MachInfo> _info, u64_t _copy_addr, u64_t _copy_size);

    // 拷贝内核中文件到物理内存地址
    u64_t CopyOSFile2PhyAddr(_Base::Ptr<MachInfo> _info, u32_t _to_addr, _Base::CPtr<char_t> _file_name);
    // 获取文件头结构开始地址和真实大小
    void GetImageOSFhdPhyAddrAndSizeByName(_Base::Ptr<MachInfo> _info, _Base::CPtr<char_t> _file_name,
                                           _Base::Ptr<u64_t> _addr, _Base::Ptr<u32_t> _real_size);

}

#endif // __BEETLE_OS_INIT_LDR__FS_H
