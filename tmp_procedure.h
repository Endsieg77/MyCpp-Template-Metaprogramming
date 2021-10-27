/**
 *  @file   myfunctional.h
 *  @author Offensive77
 *  @brief  My personally implemented Function template.
 *          Defined in namespace TMP.
 *  @modified: 2021/10/20 Wed.
 */

#ifndef _TMP_PROCEDURE_H_
#define _TMP_PROCEDURE_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

TMP_BEGIN

//template <typename _Tp>
//struct Function
//{
//    Function() = delete;
//};
//
//template <typename _Ret, typename... _Params>
//struct Function<_Ret(_Params...)>: Prototype<Function<_Ret(_Params...)>>
//{
//    using type        = Function<_Ret(_Params...)>;
//    using return_type = _Ret;
//    using value_type  = _Ret(*)(_Params...);
//public:
//#if __cplusplus >= 201703L && __cplusplus < 202002L
//    template <typename _Tp,
//              typename = typename std::enable_if_t<std::is_convertible_v<_Tp, value_type>>>
//    Function(_Tp
//#elif __cplusplus >= 202002L
//    Function(std::convertible_to<_Ret(*)(_Params...)> auto
//#endif
//      &&fp)
//        : _fp(std::move(fp)) { };
//    type &operator=(value_type &&fp) { _fp = fp; };
//    constexpr _Ret operator()(_Params&&... param) const
//    { return _fp(std::forward<_Params>(param)...); };
//
//    __TAGS__(Tags::procedure)
//private:
//    value_type _fp = nullptr;
//};

namespace DoDetails
{
    template <auto Procedure>
    struct DoIfImpl
    {
        static constexpr auto execute = Procedure;
    };

    struct __default__call__
    {
        static void execute(...) {}
    }; 
}

template <auto Procedure>
struct Do: Prototype<Do<Procedure>>
{
    Do() = delete;
    template <typename Cond>
    struct If
        : siebenzevan::If<Cond,
                          DoDetails::DoIfImpl<Procedure>,
                          DoDetails::__default__call__>::type
    { };
    __TAGS__(Tags::procedure)
};

TMP_END

#endif