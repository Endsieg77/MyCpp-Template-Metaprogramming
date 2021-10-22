#ifndef _MY_BIND_H_
#define _MY_BIND_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

TMP_BEGIN

template <size_t _No>
struct _Placeholder
{ };

template <typename _Tp>
struct IsPlaceholder: False_type
{ };

template <size_t _No>
struct IsPlaceholder<_Placeholder<_No>>: True_type
{ };

namespace Placeholders
{
/**
 *  Predefined placeholders:
 */
    extern const _Placeholder<1>   _1;
    extern const _Placeholder<2>   _2;
    extern const _Placeholder<3>   _3;
    extern const _Placeholder<4>   _4;
    extern const _Placeholder<5>   _5;
    extern const _Placeholder<6>   _6;
    extern const _Placeholder<7>   _7;
    extern const _Placeholder<8>   _8;
    extern const _Placeholder<9>   _9;
    extern const _Placeholder<10> _10;
    extern const _Placeholder<11> _11;
    extern const _Placeholder<12> _12;
    extern const _Placeholder<13> _13;
    extern const _Placeholder<14> _14;
    extern const _Placeholder<15> _15;
    extern const _Placeholder<16> _16;
    extern const _Placeholder<17> _17;
    extern const _Placeholder<18> _18;
    extern const _Placeholder<19> _19;
    extern const _Placeholder<20> _20;
    extern const _Placeholder<21> _21;
    extern const _Placeholder<22> _22;
    extern const _Placeholder<23> _23;
    extern const _Placeholder<24> _24;
    extern const _Placeholder<25> _25;
    extern const _Placeholder<26> _26;
    extern const _Placeholder<27> _27;
    extern const _Placeholder<28> _28;
    extern const _Placeholder<29> _29;
}

// template <typename... Args>
// auto Bind(auto &_function, Args... arg)
// {

// }

TMP_END

#endif