/**
 *  @file   tmp_rational.h
 *  @author Offensive77
 *  @brief  This header defines the rational number in TMP.
 *  @established: 2021/10/21 Thurs.
 *  @modified:    2021/10/21 Thurs.
 */

#ifndef _TMP_RATIONAL_H_
#define _TMP_RATIONAL_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

TMP_BEGIN

struct RationalPrototype: Prototype
{ };

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

struct Infinity: RationalPrototype
{
    Infinity() = delete;
    __TAGS__(Tags::rational)
    static constexpr long long num   = 1LL;
    static constexpr long long denom = 0LL;
};

struct NegInfinity: RationalPrototype
{
    NegInfinity() = delete;
    __TAGS__(Tags::rational)
    static constexpr long long num   = -1LL;
    static constexpr long long denom = 0LL;
};

/** 
 *  @struct TMP.Rational implements the Rational template.
 *          It uses gcd_type for compile-time simplification.
 *  @param _Q is the numerator, @param _P the denominator.
 */
template <long long _Q, long long _P = 1>
struct Rational: RationalPrototype
{
    static_assert(_P, "Divide Zero Exception!");
    Rational() = delete;
    static constexpr long long num   = _Q / gcd_type_v<_Q, _P>;
    static constexpr long long denom = _P / gcd_type_v<_Q, _P>;
    static constexpr double    value = static_cast<double>(_Q) / _P;

    static std::string to_string()
    {
        if
        #if __cplusplus >= 201703L
        constexpr
        #endif
        (denom == 1)
            return std::to_string(num);
        else
            return std::to_string(num) + "/" + std::to_string(denom);
    }

    using real = Rational;
    using imag = Rational<0>;
    __TAGS__(Tags::rational, (denom == 1ULL ? (tag_type)Tags::integer : 0ULL));
};

/** 
 *  @struct TMP.Rational<_Q> defines simple method to
 *          define integers.
 */
template <long long _Q>
struct Rational<_Q>: RationalPrototype
{
    Rational() = delete;
    static constexpr long long num   = _Q;
    static constexpr long long denom = 1LL;
    static constexpr long long value = _Q;

    static std::string to_string()
    { return std::to_string(value); }

    using real = Rational;
    using imag = Rational<0>;
    __TAGS__(Tags::rational, Tags::integer);
};

template <long long _Num>
struct Integer: Rational<_Num>
{
    __TAGS__(Tags::rational, Tags::integer);
    using real = Rational<_Num>;
    using imag = Rational<0>;
    Integer() = delete;
};

template <typename R>
struct Numer: Integer<R::num>
{
    static_assert(Eval<IsRational<R>>, "Arguement MUST be Rational.");
    Numer() = delete;
    __TAGS__(Tags::integer);
    static constexpr long long value = R::num;
};

template <typename R>
struct Denom: Integer<R::denom>
{
    static_assert(Eval<IsRational<R>>, "Arguement MUST be Rational.");
    Denom() = delete;
    __TAGS__(Tags::integer);
    static constexpr long long value = R::denom;
};

TMP_END

#endif