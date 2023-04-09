/**
* @File mach_start_param.h
* @Date 2023-04-07
* @Description 收集机器信息并初始化
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

}

#endif // BEETLE_OS_INIT_LDR_MACH_START_PARAM_H
