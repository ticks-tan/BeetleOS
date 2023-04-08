/**
* @File graph.h
* @Date 2023-04-02
* @Description 
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_INIT_LDR_GRAPH_H
#define __BEETLE_OS_INIT_LDR_GRAPH_H

#include "ldr_type.h"

namespace _Ldr
{
    void InitGraph(_Base::Ptr<MachInfo> _mbsp);

    void InitGraphInfo(_Base::Ptr<GraphInfo> _initp);

    u32_t vfartolineadr(u32_t _vfar);

    void init_kinitfvram(_Base::Ptr<MachInfo> _mbsp);

    void GetVBEMode(_Base::Ptr<MachInfo> _mbsp);

    void GetVBEModeInfo(_Base::Ptr<MachInfo> _mbsp);

    void SetVBEMode();

    void WriteBGAReg(u16_t _index, u16_t _data);

    u16_t ReadBGAReg(u16_t _index);

    u32_t GetBGADrive();

    u32_t chk_bgamaxver();

    void InitBGADrive(_Base::Ptr<MachInfo> _mbsp);

    u32_t Utf82Unicode(_Base::Ptr<utf8_t> _utf, _Base::Ptr<s32_t> _retuib);
}

#endif // __BEETLE_OS_INIT_LDR_GRAPH_H
