/**
* @File mach_start_param.cc
* @Date 2023-04-07
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/

#include "mach_start_param.h"

namespace _Ldr {

    using namespace _Base;

    void InitMachStartParam()
    {
        auto mbsp = Ptr<MachInfo>(MACH_INFO_ADDR);  // 1MB 位置
        MachInfo::Init(mbsp);
        // TODO 剩下的初始化
    }

    int CheckZoneAddrIsOk(u64_t _source_addr, u64_t _source_len, u64_t _kernel_addr, u64_t _kernel_len)
    {

    }

    int CheckAddrIsOk(_Base::Ptr<MachInfo> _mbsp, u64_t _check_addr, u64_t _check_size)
    {

    }

}