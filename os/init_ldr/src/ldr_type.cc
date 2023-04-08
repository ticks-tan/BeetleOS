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

    _Base::Ptr<MachAcpiRsdp> MachAcpiRsdp::FindAcpiRsdpFromEbda()
    {
        auto find_addr = _Base::Ptr<void>(BIOS_ACPI_RSDP_ADDR);
        auto rsdp = MachAcpiRsdp::ScanRsdpFromEbda(find_addr, BIOS_ACPI_RSDP_AREA);
        if (nullptr != rsdp) {
            return rsdp;
        }
        find_addr = _Base::Ptr<void>(BIOS_ACPI_RSDP_OTHER_ADDR);
        rsdp = MachAcpiRsdp::ScanRsdpFromEbda(find_addr, BIOS_ACPI_RSDP_OTHER_AREA);
        if (nullptr != rsdp) {
            return rsdp;
        }
        return nullptr;
    }

    _Base::Ptr<MachAcpiRsdp> MachAcpiRsdp::ScanRsdpFromEbda(_Base::Ptr<void> _addr, u32_t _size)
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

}
