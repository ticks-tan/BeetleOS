/**
* @File ldr_entry.cc
* @Date 2023-04-04
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/

#include "initldr.h"

void ldr_kernel_entry()
{
    _Ldr::InitCursor();
    _Ldr::CloseCursor();
    _Ldr::ClearScreen(VGADP_DFVL);
    // 开始收集信息
    _Ldr::InitMachStartParam();
}
