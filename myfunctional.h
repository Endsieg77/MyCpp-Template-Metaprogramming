/**
 *  @file   myfunctional.h
 *  @author Offensive77
 *  @brief  My personally implemented Function template.
 *          Defined in namespace TMP.
 *  @modified: 2021/10/20 Wed.
 */

#ifndef _MY_FUNCTIONAL_H_
#define _MY_FUNCTIONAL_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

TMP_BEGIN

template <typename _Tp>
class Function
{
    Function() = delete;
};

template <typename _Ret, typename... _Params>
class Function<_Ret(_Params...)>
{
    using type       = Function<_Ret(_Params...)>;
    using value_type = _Ret(*)(_Params...);
public:
#if __cplusplus >= 201103L && __cplusplus < 202002L
    template <typename _Tp,
              typename = typename std::enable_if<std::is_convertible<_Tp, value_type>::value>::type>
    Function(_Tp
#elif __cplusplus >= 202002L
    Function(std::convertible_to<_Ret(*)(_Params...)> auto
#endif
      &&fp)
        : _fp(std::move(fp)) { };
    type &operator=(value_type &&fp) { _fp = fp; };
    constexpr _Ret operator()(_Params&&... param) const
    { return _fp(std::forward<_Params>(param)...); };
private:
    value_type _fp = nullptr;
};

TMP_END

#endif