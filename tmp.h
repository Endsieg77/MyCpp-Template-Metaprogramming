#pragma once

namespace TMP
{
#if __cplusplus >= 201709L
// RangeSum implementation details are hidden here:

namespace RangeSumDetails
{
    template <long long _From, long long _To, long long _Step, auto _F, bool _Stop, long long _Res = 0>
    struct RangeSumImpl:
        RangeSumImpl<
                _From + _Step,
                _To,
                _Step,
                _F,
                (_From + _Step >= _To && _Step > 0) ||
                (_From + _Step <= _To && _Step < 0),
                _Res + _F(_From)
            >
    { };

    template <long long _From, long long _To, long long _Step, auto _F, long long _Res>
    struct RangeSumImpl<_From, _To, _Step, _F, true, _Res>
    { static constexpr long long value = _Res; };
}

// TMP.RangeSum

template <long long _From, long long _To, long long _Step = 1, auto _F = [](long long &&_){ return _; }>
struct RangeSum:
    RangeSumDetails::RangeSumImpl<
        _From,
        _To,
        _Step,
        _F,
        (_From >= _To && _Step > 0) ||
        (_From <= _To && _Step < 0)>
{
    RangeSum() = delete;
};

template <long long _From, long long _To, auto _F>
struct RangeSum<_From, _To, 0, _F>
{ };

// Variable with params (After C++ 17)

template <long long _From, long long _To, long long _Step = 1, auto _F = [](long long &&_){return _;}>
constexpr long long RangeSum_v = RangeSum<_From, _To, _Step, _F>::value;

#else // _HAS_CXX20
namespace RangeSumDetails
{
    template <long long _From, long long _To, long long _Step, typename _F, bool _Stop>
    struct RangeSumImpl
    {
        static_assert(_Step, "Step cannot be set zero!");
        static constexpr long long
        value =
        _F::_call_(_From) +
        RangeSumImpl<
            _From + _Step,
            _To,
            _Step,
            _F,
            (_From + _Step >= _To && _Step > 0) ||
            (_From + _Step <= _To && _Step < 0)
        >::value;
    };

    template <long long _From, long long _To, long long _Step, typename _F>
    struct RangeSumImpl<_From, _To, _Step, _F, true>
    { static constexpr long long value = 0; };
}

template <long long _From, long long _To, long long _Step = 1, typename _F = Identity<>>
struct RangeSum:
    RangeSumDetails::RangeSumImpl<
        _From,
        _To,
        _Step,
        _F,
        (_From >= _To && _Step > 0) ||
        (_From <= _To && _Step < 0)>
{
    RangeSum() = delete;
    static constexpr long long _call_() { return RangeSum<_From, _To, _Step, _F>::value; }
};

template <long long _From, long long _To, long long _Step = 1, typename _F = Identity<>>
constexpr long long RangeSum_v = RangeSum<_From, _To, _Step, _F>::value;
#endif

// Compile time gcd implementation:

template <long long M, long long N>
struct gcd_type: gcd_type<N, M % N>
{ };

template <long long N>
struct gcd_type<N, 0>
{ static constexpr long long value = N; };

template <long long M, long long N>
constexpr long long gcd_type_v = gcd_type<M, N>::value;

template <long long M, long long N>
struct lcm_type
{
    static constexpr long long value = N / gcd_type_v<M, N> * M;
};

template <long long M, long long N>
constexpr long long lcm_type_v = lcm_type<M, N>::value;

// @Class Rational
template <long long _Q, long long _P = 1>
struct Rational
{
    static constexpr long long    denom     = _Q / gcd_type_v<_Q, _P>;
    static constexpr long long    num       = _P / gcd_type_v<_Q, _P>;
    static constexpr double value     = static_cast<double>(_Q) / _P;
    static std::string to_string()
    { return std::to_string(denom) + "/"s + std::to_string(num); }
};

template <long long _Q>
struct Rational<_Q>
{
    static constexpr long long    denom     = _Q;
    static constexpr long long    num       = 1;
    static constexpr double    value     = _Q;
    static std::string to_string()
    { return std::to_string(denom); }
};

// Compare Algorithms
namespace CompareDetails
{
    template <typename _Lhs, typename _Rhs>
    struct greaterImpl
    {
        static constexpr bool value = _Lhs::denom * _Rhs::num > _Rhs::denom * _Lhs::num;
    };

    template <typename _Lhs, typename _Rhs>
    struct lessImpl
    {
        static constexpr bool value = _Lhs::denom * _Rhs::num < _Rhs::denom * _Lhs::num;
    };

    template <typename _Lhs, typename _Rhs>
    struct equalImpl
    {
        static constexpr bool value = _Lhs::denom * _Rhs::num == _Rhs::denom * _Lhs::num;
    };
    template <typename _Lhs, typename _Rhs>

    struct greater_equalImpl
    {
        static constexpr bool value = greaterImpl<_Lhs, _Rhs>::value || equalImpl<_Lhs, _Rhs>::value;
    };

    template <typename _Lhs, typename _Rhs>
    struct less_equalImpl
    {
        static constexpr bool value = lessImpl<_Lhs, _Rhs>::value || equalImpl<_Lhs, _Rhs>::value;
    };
}

template <typename _Lhs, typename _Rhs>
struct greater: CompareDetails::greaterImpl<_Lhs, _Rhs>
{ };

template <typename _Lhs, typename _Rhs>
struct less: CompareDetails::lessImpl<_Lhs, _Rhs>
{ };

template <typename _Lhs, typename _Rhs>
struct equal: CompareDetails::equalImpl<_Lhs, _Rhs>
{ };

template <typename _Lhs, typename _Rhs>
struct greater_equal: CompareDetails::greater_equalImpl<_Lhs, _Rhs>
{ };

template <typename _Lhs, typename _Rhs>
struct less_equal: CompareDetails::less_equalImpl<_Lhs, _Rhs>
{ };

template <typename R>
struct negate
{
    static constexpr long long    denom     = -R::denom;
    static constexpr long long    num       = R::num;
    static constexpr double value     = -R::value;
    static std::string to_string()
    { return Rational<denom, num>::to_string(); }
};

    namespace AbsDetails
    {
    template <typename R, bool>
    struct absImpl: R
    { };

    template <typename R>
    struct absImpl<R, false>: negate<R>
    { };
    }

template <typename R>
struct abs: AbsDetails::absImpl<R, greater<R, Rational<0>>::value>
{ };

template <typename R>
struct square: Rational<R::denom * R::denom, R::num * R::num>
{ };

template <long long Q, long long P>
struct square<Rational<Q, P>>: Rational<Q * Q, P * P>
{ };

namespace BasicDetails
{
    template <typename...>
    struct ArithmeticBases
    { };

    template <long long _LP, long long _LQ, long long _RP, long long _RQ>
    struct ArithmeticBases<Rational<_LP, _LQ>, Rational<_RP, _RQ>>
    {
        static constexpr long long _de = lcm_type_v<_LQ, _RQ>;
        static constexpr long long __1 = _de / _LQ;
        static constexpr long long __2 = _de / _RQ;
        static constexpr long long _vl = __1 * _LP;
        static constexpr long long _vr = __2 * _RP;
    };

    template <typename _Lhs, typename _Rhs>
    struct ArithmeticBases<_Lhs, _Rhs>
    {
        static constexpr long long _de = lcm_type_v<_Lhs::num, _Rhs::num>;
        static constexpr long long __1 = _de / _Lhs::num;
        static constexpr long long __2 = _de / _Rhs::num;
        static constexpr long long _vl = __1 * _Lhs::denom;
        static constexpr long long _vr = __2 * _Rhs::denom;
    };

    template <typename _Lhs, typename _Rhs>
    struct plusImpl
    {
        using utils = BasicDetails::ArithmeticBases<_Lhs, _Rhs>;
        using type  = Rational<utils::_vl + utils::_vr, utils::_de>;
    };

    template <typename _Lhs, typename _Rhs>
    struct minusImpl
    {
        using utils = BasicDetails::ArithmeticBases<_Lhs, _Rhs>;
        using type  = Rational<utils::_vl - utils::_vr, utils::_de>;
    };

    template <typename _Lhs, typename _Rhs>
    struct multiplyImpl
    {
        using type  = Rational<_Lhs::denom * _Rhs::denom, _Lhs::num * _Rhs::num>;
    };

    template <typename _Lhs, typename _Rhs>
    struct divideImpl
    {
        using type  = Rational<_Lhs::denom * _Rhs::num, _Lhs::num * _Rhs::denom>;
    };
};

template <typename _Lhs, typename _Rhs>
struct plus: BasicDetails::plusImpl<_Lhs, _Rhs>::type
{ };

template <typename _Lhs, typename _Rhs>
struct minus: BasicDetails::minusImpl<_Lhs, _Rhs>::type
{ };

template <typename _Lhs, typename _Rhs>
struct multiply: BasicDetails::multiplyImpl<_Lhs, _Rhs>::type
{ };

template <typename _Lhs, typename _Rhs>
struct divide: BasicDetails::divideImpl<_Lhs, _Rhs>::type
{ };

template <typename _Lhs, typename _Rhs>
struct average: divide<plus<_Lhs, _Rhs>, Rational<2>>
{ };

namespace SqrtDetails
{
template <typename X>
struct sqrtImpl
{
    template <typename Guess>
    struct improve: average<Guess, divide<X, Guess>>
    { };

    template <typename Guess>
    struct good_enough
    {
        static constexpr bool value = less<abs<minus<square<Guess>, X>>, Rational<1, 0xffffff>>::value;
    };

    template <typename Guess, bool>
    struct guessImpl: guessImpl<improve<Guess>, good_enough<improve<Guess>>::value>
    { };

    template <typename Guess>
    struct guessImpl<Guess, true>: Guess
    { };

    template <typename Guess>
    struct guess: guessImpl<Guess, good_enough<Guess>::value>
    { };

    using type = guess<Rational<1>>;
};
}

template <typename X>
struct sqrt: SqrtDetails::sqrtImpl<X>::type
{ };

}