/**
 *  @file   tmp_algorithms.h
 *  @author Offensive77
 *  @brief  This header defines the algorithms of CTMP.
 *  @modified: 2021/10/21 Thurs.
 */

#ifndef _TMP_ALGORITHMS_H_
#define _TMP_ALGORITHMS_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

TMP_BEGIN

template <typename _Car, typename _Cdr = Null>
struct Pair: PairPrototype
{
    using type = Pair;
    using car  = _Car;
    using cdr  = _Cdr;
};

/** 
 *  @brief  scheme-style cons.
 *  @struct TMP.cons as elements combinator.
 *  @param _Car represents the first element,
 *  @param _Cdr the second.
 */
template <typename _Car, typename _Cdr>
struct cons: Pair<_Car, _Cdr>
{ };

/** 
 *  @brief  scheme-style car
 *  @struct TMP.car yield first element of cons
 */
template <typename Cons>
struct car: Cons::car
{
    static_assert(Eval<IsPair<Cons>>);
};

/** 
 *  @brief  scheme-style cdr
 *  @struct TMP.cdr yield second element of cons
 */
template <typename Cons>
struct cdr: Cons::cdr
{
    static_assert(Eval<IsPair<Cons>>);
};

#if __cplusplus >= 202004L

// RangeSum implementation details are hidden here:
namespace RangeSumDetails
{
    template <long long _From, long long _To, long long _Step, auto _F, bool _Stop, long long _Res = 0LL>
    struct RangeSumImpl:
        RangeSumImpl<
            _From + _Step,
            _To,
            _Step,
            _F,
            (_From + _Step >= _To && _Step > 0LL) ||
            (_From + _Step <= _To && _Step < 0LL),
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
template <long long _From, long long _To, long long _Step = 1LL, auto _F = [](long long &&_){ return _; }>
struct RangeSum:
    RangeSumDetails::RangeSumImpl<
        _From,
        _To,
        _Step,
        _F,
        (_From >= _To && _Step > 0LL) ||
        (_From <= _To && _Step < 0LL)>
{ };

/** 
 *  @struct TMP.RangeSum<from, to, 0> for conditions
 *          where step equals zero. It has no static
 *          value member.
 */
template <long long _From, long long _To, auto _F>
struct RangeSum<_From, _To, 0LL, _F>
{ };

template <long long _From, long long _To, long long _Step = 1LL, auto _F = [](long long &&_){return _;}>
constexpr long long RangeSum_v = RangeSum<_From, _To, _Step, _F>::value;

#else // _HAS_NO_CXX20

namespace RangeSumDetails
{
    template <long long _From, long long _To, long long _Step, template <long long> typename _F, bool _Stop>
    struct RangeSumImpl
    {
        static_assert(_Step, "Step cannot be set zero!");
        static constexpr long long
        value =
        _F<_From>::value +
        RangeSumImpl<
            _From + _Step,
            _To,
            _Step,
            _F,
            (_From + _Step >= _To && _Step > 0LL) ||
            (_From + _Step <= _To && _Step < 0LL)>
        ::value;
    };

    template <long long _From, long long _To, long long _Step, template <long long> typename _F>
    struct RangeSumImpl<_From, _To, _Step, _F, true>
    { static constexpr long long value = 0LL; };
}

template <long long _From, long long _To, long long _Step = 1, template <long long> typename _F = Integer>
struct RangeSum:
    RangeSumDetails::RangeSumImpl<
        _From,
        _To,
        _Step,
        _F,
        (_From >= _To && _Step > 0LL) ||
        (_From <= _To && _Step < 0LL)>
{ };

template <long long _From, long long _To, long long _Step = 1LL, template <long long> typename _F = Integer>
constexpr long long RangeSum_v = RangeSum<_From, _To, _Step, _F>::value;

#endif

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
struct If: IfDetails::IfImpl<_Boolean::value, _Then, _Else>, ConditionPrototype
{
    static_assert(_Boolean::is::boolean::value, "The If Predicate MUST be of boolean type.");
};

/**
 *  @struct TMP.Case
 *  @brief Cond structure's branches.
 */
template <typename _Pred, typename _Conseq>
struct Case: Pair<_Pred, _Conseq>, ConditionPrototype
{
    static_assert(Eval<IsBoolean<_Pred>>, "The Case Predicate MUST be of boolean type.");
};

/**
 *  @struct TMP.Else
 *  @brief The default choice of condition statement,
 *         Iin which it also causes logical short-circuit.
 */
template <typename _Else>
struct Else: cons<True_type, _Else>, ConditionPrototype
{ };

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
struct Cond: CondDetails::CondImpl<Pred_Conseq...>::type, ConditionPrototype
{ };

/**
 *  @struct TMP.Negate yields the opposition of Rational,
 *          which equals to Minus<Rational<0>, Rational<what>>
 *          to some degree.
 */
template <typename R>
struct Negate: RationalPrototype<Negate<R>>
{
    static constexpr long long num    = -R::num;
    static constexpr long long denom  =  R::denom;
    static constexpr double    value  = -R::value;
    static std::string to_string()
    { return Rational<num, denom>::to_string(); }
    __TAGS__(Rational<num, denom>::tag);
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
{ };

/**
 *  @struct TMP.Square yields square of Rational.
 */
template <typename R>
struct Square: Rational<R::num * R::num, R::denom * R::denom>
{ };

/**
 *  @namespace TMP.BasicDetails hides the implementation of
 *             the four basic arithmetic operator +, -, *, /.
 */
namespace ArithmeticDetails
{
    template <typename _Lhs, typename _Rhs>
    struct ArithBases
    {
        static constexpr long long _nu = lcm_type_v<_Lhs::denom, _Rhs::denom>;
        static constexpr long long _ml = _nu / _Lhs::denom;
        static constexpr long long _mr = _nu / _Rhs::denom;
        static constexpr long long _vl = _ml * _Lhs::num;
        static constexpr long long _vr = _mr * _Rhs::num;
    };

    template <typename _Lhs, typename _Rhs>
    struct ComplexBases
    {
        using _lr = typename _Lhs::real;
        using _li = typename _Lhs::imag;
        using _rr = typename _Rhs::real;
        using _ri = typename _Rhs::imag;
    };

    template <typename _Lhs, typename _Rhs, typename = void>
    struct PlusImpl
    { };

    template <typename _Lhs, typename _Rhs>
    struct PlusImpl<_Lhs, _Rhs,
                    std::enable_if_t<IsRational<_Lhs>::value && IsRational<_Rhs>::value>>
        : Rational<ArithBases<_Lhs, _Rhs>::_vl + ArithBases<_Lhs, _Rhs>::_vr,
                   ArithBases<_Lhs, _Rhs>::_nu>
    {
        using utils = ArithBases<_Lhs, _Rhs>;
        using type  = Rational<utils::_vl + utils::_vr, utils::_nu>;
    };

    template <typename _Lhs, typename _Rhs>
    struct PlusImpl<_Lhs, _Rhs,
                    std::enable_if_t<IsComplex<_Lhs>::value && IsComplex<_Rhs>::value>>
    {
        using utils = ComplexBases<_Lhs, _Rhs>;
        using real  = PlusImpl<typename utils::_lr, typename utils::_rr>;
        using imag  = PlusImpl<typename utils::_li, typename utils::_ri>;
        using type  = Complex<real, imag>;
    };

    template <typename _Lhs, typename _Rhs, typename = void>
    struct MinusImpl
    { };

    template <typename _Lhs, typename _Rhs>
    struct MinusImpl<_Lhs, _Rhs,
                     std::enable_if_t<IsRational<_Lhs>::value && IsRational<_Rhs>::value>>
        : Rational<ArithBases<_Lhs, _Rhs>::_vl - ArithBases<_Lhs, _Rhs>::_vr,
                   ArithBases<_Lhs, _Rhs>::_nu>
    {
        using utils = ArithBases<_Lhs, _Rhs>;
        using type  = Rational<utils::_vl - utils::_vr, utils::_nu>;
    };

    template <typename _Lhs, typename _Rhs>
    struct MinusImpl<_Lhs, _Rhs,
                     std::enable_if_t<IsComplex<_Lhs>::value && IsComplex<_Rhs>::value>>
    {
        using utils = ComplexBases<_Lhs, _Rhs>;
        using real  = MinusImpl<typename utils::_lr, typename utils::_rr>;
        using imag  = MinusImpl<typename utils::_li, typename utils::_ri>;
        using type  = Complex<real, imag>;
    };

    template <typename _Lhs, typename _Rhs, typename = void>
    struct MultiplyImpl
    { };

    template <typename _Lhs, typename _Rhs>
    struct MultiplyImpl<_Lhs, _Rhs,
                        std::enable_if_t<IsRational<_Lhs>::value && IsRational<_Rhs>::value>>
            : Rational<_Lhs::num * _Rhs::num, _Lhs::denom * _Rhs::denom>
    {
        using type  = Rational<_Lhs::num * _Rhs::num, _Lhs::denom * _Rhs::denom>;
    };

    template <typename _Lhs, typename _Rhs>
    struct MultiplyImpl<_Lhs, _Rhs,
                        std::enable_if_t<IsComplex<_Lhs>::value && IsComplex<_Rhs>::value>>
    {
        using utils = ComplexBases<_Lhs, _Rhs>;
        using real  = MinusImpl<MultiplyImpl<typename utils::_lr, typename utils::_rr>,
                                MultiplyImpl<typename utils::_li, typename utils::_ri>>;
        using imag  = PlusImpl <MultiplyImpl<typename utils::_lr, typename utils::_ri>,
                                MultiplyImpl<typename utils::_li, typename utils::_rr>>;
        using type  = Complex<real, imag>;
    };

    template <typename _Lhs, typename _Rhs, typename = void>
    struct DivideImpl
    { };

    template <typename _Lhs, typename _Rhs>
    struct DivideImpl<_Lhs, _Rhs,
                      std::enable_if_t<IsRational<_Lhs>::value && IsRational<_Rhs>::value>>
        : Rational<_Lhs::num * _Rhs::denom, _Lhs::denom * _Rhs::num>
    {
        using type  = Rational<_Lhs::num * _Rhs::denom, _Lhs::denom * _Rhs::num>;
    };

    template <typename _Lhs, typename _Rhs>
    struct DivideImpl<_Lhs, _Rhs,
                      std::enable_if_t<IsComplex<_Lhs>::value && IsComplex<_Rhs>::value>>
    {
        using utils = ComplexBases<_Lhs, _Rhs>;
        using cden  = PlusImpl <Square<typename utils::_rr>,
                                Square<typename utils::_ri>>;
        using rnum  = PlusImpl <MultiplyImpl<typename utils::_lr, typename utils::_rr>,
                                MultiplyImpl<typename utils::_li, typename utils::_ri>>;
        using inum  = MinusImpl<MultiplyImpl<typename utils::_li, typename utils::_rr>,
                                MultiplyImpl<typename utils::_lr, typename utils::_ri>>;
        using real  = typename DivideImpl<rnum, cden>::type;
        using imag  = typename DivideImpl<inum, cden>::type;
        using type  = Complex<real, imag>;
    };
};

template <typename _Lhs, typename _Rhs>
struct Plus: ArithmeticDetails::PlusImpl<_Lhs, _Rhs>::type
{ };

template <typename _Lhs, typename _Rhs>
struct Minus: ArithmeticDetails::MinusImpl<_Lhs, _Rhs>::type
{ };

template <typename _Lhs, typename _Rhs>
struct Multiply: ArithmeticDetails::MultiplyImpl<_Lhs, _Rhs>::type
{ };

template <typename _Lhs, typename _Rhs>
struct Divide: ArithmeticDetails::DivideImpl<_Lhs, _Rhs>::type
{ };

template <typename R>
struct Increment: Plus<R, Rational<1LL>>
{ };

template <typename R>
struct Decrement: Minus<R, Rational<1LL>>
{ };

template <typename _Lhs, typename _Rhs>
struct Average: Divide<Plus<_Lhs, _Rhs>, Rational<2LL>>
{ };

/**
 *  @enum SqrtConstants is an enumeration class
 *        where resides some preset constants
 *        for @struct Sqrt & its hidden
 *        implementation @struct SqrtImpl.
 */
enum class SqrtConstants: long long
{
    first_try = 1LL,
    tolerance = 0xffffffLL,
};

/** 
 *  This implementation too some degree draws
 *  on the thinking of SICP. MIT, Using Heron
 *  Method.
 */
namespace SqrtDetails
{
template <typename X, long long precision>
struct SqrtImpl
{
    static_assert(Eval<GreaterEqual<X, Rational<0>>>, "Only Allows Non-negative X");
    __TAGS__(Tags::rational)

    template <typename Guess>
    struct improve: Average<Guess, Divide<X, Guess>>
    { __TAGS__(Tags::rational) };

    template <typename Guess>
    struct good_enough
        : Less<Abs<Minus<Guess, Divide<X, Guess>>>, Rational<1, precision>>
    { };

    template <typename Guess>
    struct __try__: If<good_enough<Guess>, Guess, __try__<improve<Guess>>>::type
    { __TAGS__(Tags::rational) };

    using type = __try__<Rational<(long long)SqrtConstants::first_try>>;
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
template <typename X, long long precision = (long long)SqrtConstants::tolerance>
struct Sqrt: SqrtDetails::SqrtImpl<X, (long long)precision>::type
{ };

TMP_END

#endif