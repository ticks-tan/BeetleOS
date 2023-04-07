/**
* @File base_string.h
* @Date 2023-04-05
* @Description OS使用的基础字符串类型
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_BASE_BASE_STRING_H
#define __BEETLE_OS_BASE_BASE_STRING_H

#include "kernel_base.h"

namespace _Base {
    static Ptr<char_t> strcopy(Ptr<char_t> _target, CPtr<char_t> _source)
    {
        while ((*_target++ = *_source++) != '\0')
        {}
        return _target;
    }

    static Ptr<char_t> strncopy(Ptr<char_t> _target, CPtr<char_t> _source, size_t _count, char_t _ch)
    {
        auto dest = _target;
        size_t i = 0;
        while (i < _count && (*dest++ = *_source++) != '\0') {
            ++i;
        }
        while (i < _count) {
            *dest++ = _ch;
            ++i;
        }
        return dest;
    }

    static Ptr<char_t> strncopy(Ptr<char_t> _target, CPtr<char_t> _source, size_t _count)
    {
        return strncopy(_target, _source, _count, '\0');
    }

    static inline s32_t strcmp(CPtr<char_t> _a, CPtr<char_t> _b)
    {
        while (*_a && *_b && (*_b == *_a)) {
            ++_b;
            ++_a;
        }
        return *_b - *_a;
    }

    static inline size_t memcopy(void* _target, void* _source, size_t _len)
    {
        if (nullptr == _target || nullptr == _source || _len < 1) {
            return 0;
        }
        auto target = Ptr<u8_t>(_target), source = Ptr<u8_t>(_source);
        // 避免内存重叠
        if (source < target) {
            for (auto i = ssize_t(_len - 1); i >= 0; --i) {
                target[i] = source[i];
            }
            return _len;
        }
        if (source > target) {
            for (ssize_t i = 0; i < _len; ++i) {
                target[i] = source[i];
            }
            return _len;
        }
        if (source == target) {
            return _len;
        }
        return 0;
    }
    static inline void memset(void* _target, u8_t _val, size_t _len)
    {
        auto target = _Base::Ptr<u8_t>(_target);
        for (size_t i = 0; i < _len; ++i) {
            target[i] = _val;
        }
    }

}

#endif // __BEETLE_OS_BASE_BASE_STRING_H
