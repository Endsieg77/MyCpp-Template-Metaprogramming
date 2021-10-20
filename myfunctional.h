#ifndef _MY_FUNCTIONAL_H_
#define _MY_FUNCTIONAL_H_

namespace TMP
{
template <typename... _Tp>
class f_wrapper
{
    f_wrapper() = delete;
};

template <typename _Ret, typename... _Params>
class f_wrapper<_Ret(_Params...)>
{
    using type = f_wrapper<_Ret(_Params...)>;
public:
#if __cplusplus >= 201103L && __cplusplus < 202002L
    template <typename _Tp,
              typename = std::enable_if<std::is_convertible<_Tp, _Ret(*)(_Params...)>::value>::type>
    f_wrapper(_Tp
#elif __cplusplus >= 202002L
    f_wrapper(std::convertible_to<_Ret(*)(_Params...)> auto
#endif
      &&fp)
        : _fp(fp) { };
    type &operator=(_Ret(*fp)(_Params...)) { _fp = fp; };
    _Ret operator()(_Params... param) const { return _fp(param...); };
private:
    _Ret (*_fp)(_Params...);
};
};

#endif