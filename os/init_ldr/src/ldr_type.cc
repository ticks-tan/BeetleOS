/**
* @File ldr_type.cc
* @Date 2023-04-08
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/

#include "ldr_type.h"

namespace _Ldr {

    /*------------------------------------- ACPI --------------------------------------*/

    _Base::Ptr<MachAcpiRsdp>
    MachAcpiRsdp::FindAcpiRsdpFromEbda()
    {
        // 先查找 0x40E 处往后 1KB 位置
        auto find_addr = _Base::Ptr<void>(BIOS_ACPI_RSDP_ADDR);
        auto rsdp = MachAcpiRsdp::ScanRsdpFromEbda(find_addr, BIOS_ACPI_RSDP_AREA);
        if (nullptr != rsdp) {
            return rsdp;
        }
        // 没有再从 0xE0000～0xFFFFF 区域查找
        find_addr = _Base::Ptr<void>(BIOS_ACPI_RSDP_OTHER_ADDR);
        rsdp = MachAcpiRsdp::ScanRsdpFromEbda(find_addr, BIOS_ACPI_RSDP_OTHER_AREA);
        if (nullptr != rsdp) {
            return rsdp;
        }
        return nullptr;
    }

    _Base::Ptr<MachAcpiRsdp>
    MachAcpiRsdp::ScanRsdpFromEbda(_Base::Ptr<void> _addr, u32_t _size)
    {
        if (nullptr == _addr || _size < BIOS_ACPI_RSDP_AREA) {
            return nullptr;
        }
        auto tmp_addr = _Base::Ptr<u8_t>(_addr);
        _Base::Ptr<MachAcpiRsdp> rsdp;

        for (u64_t i = 0; i <= (_size - 8); ++i) {
            if (('R' == tmp_addr[i]) && ('S' == tmp_addr[i + 1]) &&
                ('D' == tmp_addr[i + 2]) && (' ' == tmp_addr[i + 3]) &&
                ('P' == tmp_addr[i + 4]) && ('T' == tmp_addr[i + 5]) &&
                ('R' == tmp_addr[i + 6]) && (' ' == tmp_addr[i + 7]))
            {
                rsdp = MachAcpiRsdp::CheckIsOk(_Base::Ptr<MachAcpiRsdp>(&tmp_addr[i]));
                if (nullptr != rsdp) {
                    return rsdp;
                }
            }
        }
        return nullptr;
    }

    /*------------------------------------- E820Map --------------------------------------*/

    void E820Map::MMap(_Base::Ptr<_Base::Ptr<E820Map>> _e820_map, _Base::Ptr<u32_t> _count)
    {
        real_addr_call_entry(0, 0, 0);
        *_count = *(_Base::Ptr<u32_t>(E820MAP_NR));
        *_e820_map = _Base::Ptr<E820Map>(_Base::Ptr<u32_t>(E820MAP_ADDR_ADDR));
    }

    _Base::Ptr<E820Map>
    E820Map::CheckMemoryInE820MapCanUsable(_Base::Ptr<E820Map> _e820_map, u32_t _e820_count, u64_t _start_addr, u64_t _size)
    {
        if (_e820_count == 0 || _e820_map == nullptr) {
            return nullptr;
        }
        u64_t len = _start_addr + _size;

        for (u64_t i = 0; i < _e820_count; ++i) {
            if (_e820_map[i].type == E820_RAM_USABLE) {
                if ((_start_addr >= _e820_map[i].start_addr) &&
                    (len < _e820_map[i].start_addr + _e820_map[i].size))
                {
                    return &_e820_map[i];
                }
            }
        }
        return nullptr;
    }

    u64_t E820Map::GetAllMemorySize(_Base::CPtr<E820Map> _e820_map, u32_t _count)
    {
        if (nullptr == _e820_map || _count == 0) {
            return 0;
        }
        u64_t len = 0;
        for (u64_t i = 0; i < _count; ++i) {
            if (_e820_map[i].type == E820_RAM_USABLE) {
                len += _e820_map[i].size;
            }
        }
        return len;
    }

    /*------------------------------------- Image File Header Description --------------------------------------*/

    _Base::Ptr<ImageOSFileHDes>
    MachInfo::GetOSFileHeaderDesByName(_Base::Ptr<MachInfo> _info, _Base::CPtr<char_t> _file_name)
    {
        auto fhd = _Base::Ptr<ImageFileHDes>(_info->os_img_addr + IMAGE_OS_HDC_OFF);
        if (fhd->end_magic != IMAGE_OS_MDC_END_MAGIC ||
            fhd->version != IMAGE_OS_MDC_RV_MAGIC ||
            fhd->fhd_count < 2 ||
            fhd->file_count < 2)
        {
            KError("Not found mrddsc");
            return nullptr;
        }

        auto file_fhd = _Base::Ptr<ImageOSFileHDes>(fhd->fhd_start_offset + _info->os_img_addr);

        for (u64_t i = 0; i < fhd->fhd_count; ++i) {
            if (0 == _Base::strcmp(_file_name, file_fhd[i].file_name)) {
                return &file_fhd[i];
            }
        }
        KError("Not found file");
        return nullptr;
    }
}
