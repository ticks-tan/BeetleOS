/**
* @File init_head.h
* @Date 2023-04-07
* @Description 初始化头部
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_INIT_LDR_INIT_HEAD_H
#define __BEETLE_OS_INIT_LDR_INIT_HEAD_H

#include "ldr_type.h"

__NO_MANGLE void init_ldr_header();

namespace _Ldr {

    void WriteRealIntSaveFile();

    _Base::Ptr<ImageOSFileHDes> FindFile(_Base::CPtr<char_t> _name);

    void WriteLdrKernelFile();

}

#endif // __BEETLE_OS_INIT_LDR_INIT_HEAD_H
