/**
 *  @file   tmp_algorithms.h
 *  @author Offensive77
 *  @brief  This header defines the algorithms of CTMP.
 *  @modified: 2021/10/19 Tues.
 */

#ifndef _TMP_ALGORITHMS_H_
#define _TMP_ALGORITHMS_H_

TMP_BEGIN

/**
 *  @struct TMP.Null functions behind the curtain.
 */
struct Null
{
    Null() = delete;
};

/**
 *  @a Eval evaluates the template _Tp's value member.
 */
template <typename _Tp>
constexpr long long Eval = _Tp::value;

template <typename _Car, typename _Cdr = Null>
struct Pair
{
    Pair() = delete;
    using car = _Car;
    using cdr = _Cdr;
};

/** 
 *  @brief  scheme-style cons.
 *  @struct TMP.cons as elements combinator.
 *  @param _Car represents the first element,
 *  @param _Cdr the second.
 */
template <typename _Car, typename _Cdr>
struct cons: Pair<_Car, _Cdr>
{
    cons() = delete;
};

/** 
 *  @brief  scheme-style car
 *  @struct TMP.car yield first element of cons
 */
template <typename Cons>
struct car: Cons::car
{
    car() = delete;
};

/** 
 *  @brief  scheme-style cdr
 *  @struct TMP.cdr yield second element of cons
 */
template <typename Cons>
struct cdr: Cons::cdr
{
    cdr() = delete;
};

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
            _Res + _F(_From)>
    { };

    template <long long _From, long long _To, long long _Step, auto _F, long long _Res>
    struct RangeSumImpl<_From, _To, _Step, _F, true, _Res>
    { static constexpr long long value = _Res; };
}

/**
 *  @struct TMP.RangeSum calculates the sum of
 *          f(x) for all x in range(from, to, step)
 *  @param _F receives a cxx11 lambda expression,
 *         its default value the Id(x) transformation.
 *         when @param _F is enabled, you must explicitly
 *         assign a step for the template.
 */
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

/** 
 *  @struct TMP.RangeSum<from, to, 0> for conditions
 *          where step equals zero. It has no static
 *          value member.
 */
template <long long _From, long long _To, auto _F>
struct RangeSum<_From, _To, 0, _F>
{ };

// Variable with params (After C++ 17)
template <long long _From, long long _To, long long _Step = 1, auto _F = [](long long &&_){return _;}>
constexpr long long RangeSum_v = RangeSum<_From, _To, _Step, _F>::value;

#else // _HAS_NO_CXX20

template <int N = 0>
struct Identity
{
    static constexpr int value = N;
    static constexpr int _call_(int &&n) { return n; }
};

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

/** 
 *  @struct TMP.gcd_type is the compile-time
 *          gcd algorithm implementation.
 */
template <long long M, long long N>
struct gcd_type: gcd_type<N, M % N>
{
    gcd_type() = delete;
};

template <long long N>
struct gcd_type<N, 0>
{ static constexpr long long value = N; };

template <long long N>
struct gcd_type<0, N>
{ static constexpr long long value = N; };

template <long long M, long long N>
constexpr long long gcd_type_v = gcd_type<M, N>::value;

/** 
 *  @struct TMP.lcm_type is the compile-time
 *          lcm algorithm implementation.
 */
template <long long M, long long N>
struct lcm_type
{
    lcm_type() = delete;
    static constexpr long long value = N / gcd_type_v<M, N> * M;
};

template <long long M, long long N>
constexpr long long lcm_type_v = lcm_type<M, N>::value;

/** 
 *  @struct TMP.Rational implements the Rational template.
 *          It uses gcd_type for compile-time simplification.
 *  @param _Q is the numerator, @param _P the denominator.
 */
template <long long _Q, long long _P = 1>
struct Rational
{
    static_assert(_P, "Divide Zero Is Not Valid!");
    Rational() = delete;
    static constexpr long long  num   = _Q / gcd_type_v<_Q, _P>;
    static constexpr long long  denom = _P / gcd_type_v<_Q, _P>;
    static constexpr double     value = static_cast<double>(_Q) / _P;
    static std::string to_string()
    { return std::to_string(num) + "/" + std::to_string(denom); }
};

/** 
 *  @struct TMP.Rational<_Q> defines simple method to
 *          define integers.
 */
template <long long _Q>
struct Rational<_Q>
{
    static constexpr long long num     = _Q;
    static constexpr long long denom       = 1;
    static constexpr double    value     = _Q;
    static std::string to_string()
    { return std::to_string(num); }
};

template <typename R>
struct Numer
{
    Numer() = delete;
    static constexpr long long value = R::num;
};

template <typename R>
struct Denom
{
    Denom() = delete;
    static constexpr long long value = R::denom;
};

/** 
 *  @namespace TMP.CompareDetails hides the detail
 *             of compile-time comparations.
 */
namespace CompareDetails
{
    template <typename _Lhs, typename _Rhs>
    struct GreaterImpl
    {
        static constexpr bool value = _Lhs::num * _Rhs::denom > _Rhs::num * _Lhs::denom;
    };

    template <typename _Lhs, typename _Rhs>
    struct LessImpl
    {
        static constexpr bool value = _Lhs::num * _Rhs::denom < _Rhs::num * _Lhs::denom;
    };

    template <typename _Lhs, typename _Rhs>
    struct EqualImpl
    {
        static constexpr bool value = _Lhs::denom * _Rhs::num == _Rhs::denom * _Lhs::num;
    };

    template <typename _Lhs, typename _Rhs>
    struct NotEqualImpl
    {
        static constexpr bool value = _Lhs::denom * _Rhs::num != _Rhs::denom * _Lhs::num;
    };

    template <typename _Lhs, typename _Rhs>
    struct GreaterEqualImpl
    {
        static constexpr bool value = GreaterImpl<_Lhs, _Rhs>::value || EqualImpl<_Lhs, _Rhs>::value;
    };

    template <typename _Lhs, typename _Rhs>
    struct LessEqualImpl
    {
        static constexpr bool value = LessImpl<_Lhs, _Rhs>::value || EqualImpl<_Lhs, _Rhs>::value;
    };

    template <typename _Lhs, typename _Rhs>
    struct AndImpl
    {
        static constexpr bool value = _Lhs::value && _Rhs::value;
    };

    template <typename _Lhs, typename _Rhs>
    struct OrImpl
    {
        static constexpr bool value = _Lhs::value || _Rhs::value;
    };

    template <typename _Statement>
    struct NotImpl
    {
        static constexpr bool value = !_Statement::value;
    };
}

// Logical True and False
struct True_type
{
    True_type() = delete;
    static constexpr bool value = true;
};

struct False_type
{
    False_type() = delete;
    static constexpr bool value = true;
};

/**
 *  @struct TMP.Greater is the compile-time '>' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Greater: CompareDetails::GreaterImpl<_Lhs, _Rhs>
{
    Greater() = delete;
};

/**
 *  @struct TMP.Less is the compile-time '<' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Less: CompareDetails::LessImpl<_Lhs, _Rhs>
{
    Less() = delete;
};

/**
 *  @struct TMP.Equal is the compile-time '==' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Equal: CompareDetails::EqualImpl<_Lhs, _Rhs>
{
    Equal() = delete;
};

/**
 *  @struct TMP.NotEqual is the compile-time '!=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct NotEqual: CompareDetails::NotEqualImpl<_Lhs, _Rhs>
{
    NotEqual() = delete;
};

/**
 *  @struct TMP.GreaterEqual is the compile-time '>=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct GreaterEqual: CompareDetails::GreaterEqualImpl<_Lhs, _Rhs>
{
    GreaterEqual() = delete;
};

/**
 *  @struct TMP.LessEqual is the compile-time '<=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct LessEqual: CompareDetails::LessEqualImpl<_Lhs, _Rhs>
{
    LessEqual() = delete;
};

/**
 *  @struct TMP.And is the compile-time '&&' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct And: CompareDetails::AndImpl<_Lhs, _Rhs>
{
    And() = delete;
};

/**
 *  @struct TMP.Or is the compile-time '||' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Or: CompareDetails::OrImpl<_Lhs, _Rhs>
{
    Or() = delete;
};

/**
 *  @struct TMP.Not is the compile-time '!' for Rationals.
 */
template <typename _Statement>
struct Not: CompareDetails::NotImpl<_Statement>
{
    Not() = delete;
};

/**
 *  @struct If and Cond statement for TMP.
 */
namespace IfDetails
{
    template <bool _B, typename _Then, typename _Else>
    struct IfImpl: _Then
    {
        using type = _Then;
    };

    template <typename _Then, typename _Else>
    struct IfImpl<false, _Then, _Else>: _Else
    {
        using type = _Else;
    };
}

/**
 *  @struct TMP.If. 
 *  @brief This implements if...else structure
 *  @param Boolean has a static bool member called value.
 *  When Boolean::value is true. If::type is @param _Then's,
 *  else @param _Else's.
 */
template <typename _Boolean, typename _Then, typename _Else>
struct If: IfDetails::IfImpl<_Boolean::value, _Then, _Else>
{
    If() = delete;
};

/**
 *  @struct TMP.Case
 *  @brief Cond structure's branches.
 */
template <typename _Pred, typename _Conseq>
struct Case: Pair<_Pred, _Conseq>
{
    Case() = delete;
};

/**
 *  @struct TMP.Else
 *  @brief The default choice of condition statement,
 *         Iin which it also causes logical short-circuit.
 */
template <typename _Else>
struct Else: cons<True_type, _Else>
{
    Else() = delete;
};

namespace CondDetails
{
template <typename... Pred_Conseq>
struct CondImpl
{ };

template <typename _First, typename... Pred_Conseq>
struct CondImpl<_First, Pred_Conseq...>
{
    using type =
    typename
    If<typename _First::car,
       typename _First::cdr,
       typename CondImpl<Pred_Conseq...>::type>::type;
};

/**
 *  @struct _LstImpl. The last branch should not be
 *          seen as least important. On contrary, 
 *          It shall be dealt with more cautiously.
 */
template <bool, typename _Tp>
struct _LstImpl
{
    using type = _Tp;
};

template <typename _Tp>
struct _LstImpl<false, _Tp>
{
    using type = Null;
};

template <typename _LstButNotLeast>
struct CondImpl<_LstButNotLeast>
{
    using type =
        typename
        _LstImpl<static_cast<bool>(_LstButNotLeast::car::value),
                 typename _LstButNotLeast::cdr>::type;
};
}

template <typename... Pred_Conseq>
struct Cond: CondDetails::CondImpl<Pred_Conseq...>::type
{
    Cond() = delete;
};

/**
 *  @struct TMP.Negate yields the opposition of Rational.
 */
template <typename R>
struct Negate
{
    Negate() = delete;
    static constexpr long long num    = -R::num;
    static constexpr long long denom  =  R::denom;
    static constexpr double    value  = -R::value;
    static std::string to_string()
    { return Rational<num, denom>::to_string(); }
};

namespace AbsDetails
{
template <typename R, bool>
struct AbsImpl: R
{ };

template <typename R>
struct AbsImpl<R, false>: Negate<R>
{ };
}

/**
 *  @struct TMP.Abs yields absolute value of Rational.
 */
template <typename R>
struct Abs: AbsDetails::AbsImpl<R, Greater<R, Rational<0>>::value>
{
    Abs() = delete;
};

/**
 *  @struct TMP.Square yields square of Rational.
 */
template <typename R>
struct Square: Rational<R::num * R::num, R::denom * R::denom>
{
    Square() = delete;
};

/**
 *  @namespace TMP.BasicDetails hides the implementation of
 *             the four basic arithmetic operator +, -, *, /.
 */
namespace BasicDetails
{
    template <typename _Lhs, typename _Rhs>
    struct ArithmeticBases
    {
        static constexpr long long _nu = lcm_type_v<_Lhs::denom, _Rhs::denom>;
        static constexpr long long _ml = _nu / _Lhs::denom;
        static constexpr long long _mr = _nu / _Rhs::denom;
        static constexpr long long _vl = _ml * _Lhs::num;
        static constexpr long long _vr = _mr * _Rhs::num;
    };

    template <typename _Lhs, typename _Rhs>
    struct PlusImpl
    {
        using utils = ArithmeticBases<_Lhs, _Rhs>;
        using type  = Rational<utils::_vl + utils::_vr, utils::_nu>;
    };

    template <typename _Lhs, typename _Rhs>
    struct MinusImpl
    {
        using utils = ArithmeticBases<_Lhs, _Rhs>;
        using type  = Rational<utils::_vl - utils::_vr, utils::_nu>;
    };

    template <typename _Lhs, typename _Rhs>
    struct MultiplyImpl
    {
        using type  = Rational<_Lhs::num * _Rhs::num, _Lhs::denom * _Rhs::denom>;
    };

    template <typename _Lhs, typename _Rhs>
    struct DivideImpl
    {
        using type  = Rational<_Lhs::num * _Rhs::denom, _Lhs::denom * _Rhs::num>;
    };
};

template <typename _Lhs, typename _Rhs>
struct Plus: BasicDetails::PlusImpl<_Lhs, _Rhs>::type
{
    Plus() = delete;
};

template <typename _Lhs, typename _Rhs>
struct Minus: BasicDetails::MinusImpl<_Lhs, _Rhs>::type
{
    Minus() = delete;
};

template <typename _Lhs, typename _Rhs>
struct Multiply: BasicDetails::MultiplyImpl<_Lhs, _Rhs>::type
{
    Multiply() = delete;
};

template <typename _Lhs, typename _Rhs>
struct Divide: BasicDetails::DivideImpl<_Lhs, _Rhs>::type
{
    Divide() = delete;
};

template <typename R>
struct Increment: Plus<R, Rational<1>>
{
    Increment() = delete;
};

template <typename R>
struct Decrement: Minus<R, Rational<1>>
{
    Decrement() = delete;
};

template <typename _Lhs, typename _Rhs>
struct Average: Divide<Plus<_Lhs, _Rhs>, Rational<2>>
{
    Average() = delete;
};

/** 
 *  This implementation too some degree draws
 *  on the thinking of SICP. MIT, Using Heron
 *  Method.
 */
namespace SqrtDetails
{
template <typename X, long long precision = 0xffffff>
struct SqrtImpl
{
    template <typename Guess>
    struct improve: Average<Guess, Divide<X, Guess>>
    { };

    template <typename Guess>
    struct good_enough
    {
        static constexpr bool
        value
        = Less<Abs<Minus<Guess, Divide<X, Guess>>>, Rational<1, precision>>::value;
    };

    template <typename Guess>
    struct _try: If<good_enough<Guess>, Guess, _try<improve<Guess>>>::type
    { };

    using type = _try<Rational<(long long)X::value>>;
};
}

/**
 *  @struct TMP.Sqrt Compile-time Square root. Yahooooo!
 *  It receives @param X.
 *  @return square root of X by its value member.
 *  If the form of X is too complicated, the program may
 *  meet with an integer overflow.
 *  @param precision means the result will fall on the area
 *  O(answer, 1/@param precision)
 */
template <typename X, long long precision = 0xffffff>
struct Sqrt: SqrtDetails::SqrtImpl<X, precision>::type
{
    Sqrt() = delete;
};

TMP_END

#endif