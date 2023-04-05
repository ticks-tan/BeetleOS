/**
* @File base_template.h
* @Date 2023-04-05
* @Description OS中使用的基础宏
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/
#ifndef __BEETLE_OS_BASE_BASE_TEMPLATE_H
#define __BEETLE_OS_BASE_BASE_TEMPLATE_H

/*------------------------------  template  ---------------------------------------*/

namespace _Base {
    template<typename _Tp>
    using Ptr = _Tp*;

    template<typename _Tp>
    using Ref = _Tp&;


    // 移除类型 const
    template<typename _Tp>
    struct __RemoveConstHelper {
        typedef _Tp type;
    };
    template<typename _Tp>
    struct __RemoveConstHelper<const _Tp> {
        typedef _Tp type;
    };
    template<typename _Tp>
    struct RemoveConst {
        typedef typename __RemoveConstHelper<_Tp>::type type;
    };
    template<typename _Tp>
    using RemoveConst_T = typename RemoveConst<_Tp>::type;

    // 移除类型 volatile
    template<typename _Tp>
    struct __RemoveVolatileHelper {
        typedef _Tp type;
    };
    template<typename _Tp>
    struct __RemoveVolatileHelper<const _Tp> {
        typedef _Tp type;
    };
    template<typename _Tp>
    struct RemoveVolatile {
        typedef typename __RemoveVolatileHelper<_Tp>::type type;
    };
    template<typename _Tp>
    using RemoveVolatile_T = typename RemoveVolatile<_Tp>::type;

    // 移除 const 和 volatile
    template<typename _Tp>
    struct RemoveCV {
        typedef typename RemoveVolatile<typename RemoveConst<_Tp>::type>::type type;
    };
    template<typename _Tp>
    using RemoveCV_T = typename RemoveCV<_Tp>::type;


    template<typename _Tp, _Tp __v>
    struct IntegralConstant {
        static constexpr _Tp value = __v;

        typedef _Tp value_type;
        typedef IntegralConstant<_Tp, __v> type;

        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

    using TrueType = IntegralConstant<bool, true>;
    using FalseType = IntegralConstant<bool, false>;

    template<bool __v>
    using BoolConstant = IntegralConstant<bool, __v>;

    // 判断是否为 void 类型
    template<typename _Tp>
    struct __IsVoidHelper
            : public FalseType { };
    template<>
    struct __IsVoidHelper<void>
            : public TrueType { };
    template<typename _Tp>
    struct IsVoid
            : public __IsVoidHelper<RemoveCV_T<_Tp>>::type { };

    // 判断是否为char类型
    template<typename _Tp>
    struct __IsCharHelper
            : public FalseType { };
    template<>
    struct __IsCharHelper<char>
            : public TrueType { };
    template<typename _Tp>
    struct IsChar
            : public __IsCharHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为uchar类型
    template<typename _Tp>
    struct __IsUCharHelper
            : public FalseType { };
    template<>
    struct __IsUCharHelper<unsigned char>
            : public TrueType { };
    template<typename _Tp>
    struct IsUChar
            : public __IsUCharHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为bool类型
    template<typename _Tp>
    struct __IsBoolHelper
            : public FalseType { };
    template<>
    struct __IsBoolHelper<bool>
            : public TrueType { };
    template<typename _Tp>
    struct IsBool
            : public __IsBoolHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为signed char类型
    template<typename _Tp>
    struct __IsSCharHelper
            : public FalseType { };
    template<>
    struct __IsSCharHelper<signed char>
            : public TrueType { };
    template<typename _Tp>
    struct IsSChar
            : public __IsSCharHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为char16类型
    template<typename _Tp>
    struct __IsChar16Helper
            : public FalseType { };
    template<>
    struct __IsChar16Helper<char16_t>
            : public TrueType { };
    template<typename _Tp>
    struct IsChar16
            : public __IsChar16Helper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为char32类型
    template<typename _Tp>
    struct __IsChar32Helper
            : public FalseType { };
    template<>
    struct __IsChar32Helper<char32_t>
            : public TrueType { };
    template<typename _Tp>
    struct IsChar32
            : public __IsChar32Helper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为short类型
    template<typename _Tp>
    struct __IsShortHelper
            : public FalseType { };
    template<>
    struct __IsShortHelper<short>
            : public TrueType { };
    template<typename _Tp>
    struct IsShort
            : public __IsShortHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为unsigned short类型
    template<typename _Tp>
    struct __IsUShortHelper
            : public FalseType { };
    template<>
    struct __IsUShortHelper<unsigned short>
            : public TrueType { };
    template<typename _Tp>
    struct IsUShort
            : public __IsUShortHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为int类型
    template<typename _Tp>
    struct __IsIntHelper
            : public FalseType { };
    template<>
    struct __IsIntHelper<int>
            : public TrueType { };
    template<typename _Tp>
    struct IsInt
            : public __IsIntHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为unsigned int类型
    template<typename _Tp>
    struct __IsUIntHelper
            : public FalseType { };
    template<>
    struct __IsUIntHelper<unsigned int>
            : public TrueType { };
    template<typename _Tp>
    struct IsUInt
            : public __IsUIntHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为long类型
    template<typename _Tp>
    struct __IsLongHelper
            : public FalseType { };
    template<>
    struct __IsLongHelper<long>
            : public TrueType { };
    template<typename _Tp>
    struct IsLong
            : public __IsLongHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为unsigned long类型
    template<typename _Tp>
    struct __IsULongHelper
            : public FalseType { };
    template<>
    struct __IsULongHelper<long>
            : public TrueType { };
    template<typename _Tp>
    struct IsULong
            : public __IsULongHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为long long类型
    template<typename _Tp>
    struct __IsLLongHelper
            : public FalseType { };
    template<>
    struct __IsLLongHelper<long long>
            : public TrueType { };
    template<typename _Tp>
    struct IsLLong
            : public __IsLLongHelper<RemoveCV_T<_Tp>>::type {  };

    // 判断是否为unsigned long long类型
    template<typename _Tp>
    struct __IsULLongHelper
            : public FalseType { };
    template<>
    struct __IsULLongHelper<unsigned long long>
            : public TrueType { };
    template<typename _Tp>
    struct IsULLong
            : public __IsULLongHelper<RemoveCV_T<_Tp>>::type {  };

    // 是否为数字类型
    template<typename _Tp>
    struct __IsIntegralHelper
            : public FalseType { };
    template<>
    struct __IsIntegralHelper<bool>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<char>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<signed char>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<unsigned char>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<wchar_t>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<char16_t>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<char32_t>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<short>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<unsigned short>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<int>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<unsigned int>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<long>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<unsigned long>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<long long>
            : public TrueType { };
    template<>
    struct __IsIntegralHelper<unsigned long long>
            : public TrueType { };

    template<typename _Tp>
    struct IsIntegral
            : public __IsIntegralHelper<RemoveCV_T<_Tp>>::type { };


    // 判断类型是否为 float
    template<typename _Tp>
    struct __IsFloatHelper
            : public FalseType { };
    template<>
    struct __IsFloatHelper<float>
            : public TrueType { };
    template<typename _Tp>
    struct IsFloat
            : public __IsFloatHelper<RemoveCV_T<_Tp>>::type { };

    // 判断类型是否为 double
    template<typename _Tp>
    struct __IsDoubleHelper
            : public FalseType { };
    template<>
    struct __IsDoubleHelper<double>
            : public TrueType { };
    template<>
    struct __IsDoubleHelper<long double>
            : public TrueType { };
    template<typename _Tp>
    struct IsDouble
            : public __IsDoubleHelper<RemoveCV_T<_Tp>>::type { };

    // 判断类型是否为浮点类型
    template<typename _Tp>
    struct __IsFloatPointerHelper
            : public FalseType { };
    template<>
    struct __IsFloatPointerHelper<float>
            : public TrueType { };
    template<>
    struct __IsFloatPointerHelper<double>
            : public TrueType { };
    template<>
    struct __IsFloatPointerHelper<long double>
            : public TrueType { };
    template<typename _Tp>
    struct IsFloatPointer
            : public __IsFloatPointerHelper<RemoveCV_T<_Tp>>::type { };


}

#endif // __BEETLE_OS_BASE_BASE_TEMPLATE_H
