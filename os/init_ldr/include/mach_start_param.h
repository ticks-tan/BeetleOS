/**
* @File mach_start_param.h
* @Date 2023-04-07
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef BEETLE_OS_INIT_LDR_MACH_START_PARAM_H
#define BEETLE_OS_INIT_LDR_MACH_START_PARAM_H

#include "base_string.h"
#include "ldr_type.h"
#include "check_cpu.h"

namespace _Ldr {

    // 初始化并获取机器信息
    void InitMachStartParam();

    // 初始化机器信息结构
    void InitMachInfo(_Base::Ptr<MachInfo> _init);

    // 检查内核栈地址是否与内核文件地址冲突
    int CheckZoneAddrIsOk(u64_t _source_addr, u64_t _source_len, u64_t _kernel_addr, u64_t _kernel_len);

    // 检查内存是否满足要求
    int CheckAddrIsOk(_Base::Ptr<MachInfo> _mbsp, u64_t _check_addr, u64_t _check_size);



}

#endif // BEETLE_OS_INIT_LDR_MACH_START_PARAM_H
