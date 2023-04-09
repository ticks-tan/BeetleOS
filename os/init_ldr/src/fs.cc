/**
* @File fs.cc
* @Date 2023-04-09
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/

#include "fs.h"

namespace _Ldr
{
    inline bool CheckAddrIsNotClash(u64_t _start_addr, u64_t _start_len, u64_t _kernel_addr, u64_t _kernel_len)
    {
        if (_kernel_addr >= _start_addr && _kernel_addr <= (_start_addr + _start_len)) {
            return false;
        }
        if (_kernel_addr <= _start_addr && (_kernel_addr + _kernel_len) >= _start_addr) {
            return false;
        }
        return true;
    }

    bool CheckAddrIsOk(_Base::Ptr<MachInfo> _info, u64_t _check_addr, u64_t _check_size)
    {
        // 栈空间
        if (!CheckAddrIsNotClash((_info->kernel_stack_addr - _info->kernel_stack_size),
                               _info->kernel_stack_size,
                               _check_addr, _check_size))
        {
            return false;
        }
        // 映像文件
        if (!CheckAddrIsNotClash(_info->os_img_addr, _info->os_img_size,
                               _check_addr, _check_size))
        {
            return false;
        }
        // 内核文件
        if (!CheckAddrIsNotClash(_info->kernel_img_addr, _info->kernel_img_size,
                               _check_addr, _check_size))
        {
            return false;
        }
        // e820数组
        if (!CheckAddrIsNotClash(_info->e820_phy_addr, _info->e820_phy_size,
                               _check_addr, _check_size))
        {
            return false;
        }
        return true;
    }

    bool MoveOSImageIfClash(_Base::Ptr<MachInfo> _info, u64_t _copy_addr, u64_t _copy_size) {
        if ((_copy_addr + _copy_size) >= 0xffffffff || _copy_size < 1) {
            return false;
        }
        auto to_addr = _Base::Ptr<void>(__ALIGN_4K(_copy_addr + _copy_size));
        u64_t to_size = _info->os_img_size;
        if (!CheckAddrIsNotClash(_info->os_img_addr, _info->os_img_size, _copy_addr, _copy_size)) {
            // 判断移动后内存是否可用
            if (nullptr == E820Map::CheckMemoryInE820MapCanUsable(
                    _Base::Ptr<E820Map>(_info->e820_phy_addr),
                    u32_t(_info->e820_phy_count),
                    u64_t(to_addr),
                    u64_t(to_size))) {
                return false;
            }
            // 拷贝内核镜像文件地址到指定内存
            _Base::memcopy(to_addr, _Base::Ptr<void>(_info->os_img_addr), to_size);
            _info->os_img_addr = u64_t(to_addr);
            return true;
        }
        return true;
    }

    u64_t CopyOSFile2PhyAddr(_Base::Ptr<MachInfo> _info, u32_t _to_addr, _Base::CPtr<char_t> _file_name)
    {
        if (nullptr == _info || _to_addr == 0 || nullptr == _file_name) {
            return 0;
        }
        u64_t fhd_addr = 0;
        u32_t fhd_size = 0;
        GetImageOSFhdPhyAddrAndSizeByName(_info, _file_name, &fhd_addr, &fhd_size);
        if (0 == fhd_addr || 0 == fhd_size) {
            return 0;
        }
        if (nullptr == E820Map::CheckMemoryInE820MapCanUsable(
                _Base::Ptr<E820Map>(_info->e820_phy_addr),
                _info->e820_phy_count, _to_addr, fhd_size))
        {
            return 0;
        }
        // 查找移动到的地址是否与其他已有文件冲突
        if (!CheckAddrIsOk(_info, _to_addr, fhd_size)) {
            return 0;
        }
        // 满足要求，拷贝文件
        _Base::memcopy(_Base::Ptr<void>(u64_t(_to_addr)), _Base::Ptr<void>(fhd_addr), fhd_size);
        return fhd_size;
    }

    void GetImageOSFhdPhyAddrAndSizeByName(_Base::Ptr<MachInfo> _info, _Base::CPtr<char_t> _file_name,
                                           _Base::Ptr<u64_t> _addr, _Base::Ptr<u32_t> _real_size)
    {
        if (nullptr == _info || nullptr == _file_name) {
            *_addr = *_real_size = 0;
            return;
        }
        auto fhd = MachInfo::GetOSFileHeaderDesByName(_info, _file_name);
        if (nullptr == fhd) {
            *_addr = *_real_size = 0;
        }
        u64_t addr = fhd->offset_start + _info->os_img_addr;
        u32_t size = fhd->file_real_size;
        if (addr > 0xffffffff) {
            *_addr = *_real_size = 0;
            return;
        }
        if (size > 0xffffffff) {
            *_addr = *_real_size = 0;
            return;
        }
        *_addr = addr;
        *_real_size = size;
    }
}