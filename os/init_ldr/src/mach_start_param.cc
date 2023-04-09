/**
* @File mach_start_param.cc
* @Date 2023-04-07
* @Description 收集机器信息并初始化
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
        auto mach_info = Ptr<MachInfo>(MACH_INFO_ADDR);  // 物理内存 1MB 位置
        // 初始化机器信息结构体
        MachInfo::Init(mach_info);
        // 检查CPU
        if (!CheckCpu(mach_info)) {
            // TODO 停止加载内核
        }
        // 获取并检查内存视图
        if (!InitMemoryView(mach_info)) {
            // TODO 停止加载内核
        }
        // 初始化内核 C++ 栈空间
        if (!InitKernelStackAddr(mach_info)) {
            // TODO 停止加载内核
        }
        // 移动内核镜像文件到高地址
        if (!InitKernelFile(mach_info)) {
            // TODO 停止加载内核
        }
        // 移动 E820 内存数组到高地址
        if (!InitE820Map(mach_info)) {
            // TODO 停止加载内核
        }
        // 初始化MMU页表
        // 让虚拟地址 0xffff800000000000～0xffff800400000000 和虚拟地址：0～0x400000000
        // 都映射到物理内存 0～0x400000000
        if (!InitMMUPage(mach_info)) {
            // TODO 停止加载内核
        }
    }

}