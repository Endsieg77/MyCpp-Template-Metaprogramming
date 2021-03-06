/**
 *  @file   tmp_rational.h
 *  @author Offensive77
 *  @brief  This header defines the rational number in TMP,
 *  along with the compile-time gcd, lc, the Infinity and
 *  the Negative Infinity. Though less than one time did I
 *  ever used them lol.
 *  @copyright reserved.
 */

#ifndef _TMP_RATIONAL_H_
#define _TMP_RATIONAL_H_

TMP_BEGIN

inline
static constexpr long long __abs__(long long _x)
{
    return
    _x > 0 ? _x: -_x;
}

/** 
 *  @struct siebenzevan.gcd_type is the compile-time
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
 *  @struct siebenzevan.lcm_type is the compile-time
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

struct Infinity: RationalPrototype<Infinity>
{
    static constexpr long long num   = 1LL;
    static constexpr long long denom = 0LL;
};

struct NegInfinity: RationalPrototype<NegInfinity>
{
    static constexpr long long num   = -1LL;
    static constexpr long long denom = 0LL;
};

/** 
 *  @struct siebenzevan.Rational implements the Rational template.
 *          It uses gcd_type for compile-time simplification.
 *  @param _Q is the numerator, @param _P the denominator.
 */
template <long long _Q, long long _P = 1LL>
struct Rational: RationalPrototype<Rational<_Q, _P>>
{
    static_assert(_P, "Divide Zero Exception!");
private:
    enum __trivial: long long
    {
        __gcd_res         = gcd_type_v<_Q, _P>,
        smaller_than_zero = (_Q < 0 && _P > 0) || (_P < 0 && _Q > 0),
        num_res           = smaller_than_zero ? -__abs__(_Q) / __abs__(__gcd_res) : _Q / __gcd_res,
        denom_res         = smaller_than_zero ?  __abs__(_P) / __abs__(__gcd_res) : _P / __gcd_res,
    };
public:
    static constexpr long long num   = __trivial::num_res;
    static constexpr long long denom = __trivial::denom_res;
    static constexpr double    value = static_cast<double>(_Q) / _P;

    static std::string to_string()
    {
        if __CXX17_IF_CONSTEXPR__
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
 *  @struct siebenzevan.Rational<_Q> defines simple method to
 *          define integers.
 */
template <long long _Q>
struct Rational<_Q>: RationalPrototype<Rational<_Q>>
{
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
};

template <typename R>
struct Numer: Integer<R::num>
{
    static_assert(Eval<IsRational<R>>, "Arguement MUST be Rational.");
    __TAGS__(Tags::integer);
    static constexpr long long value = R::num;
};

template <typename R>
struct Denom: Integer<R::denom>
{
    static_assert(Eval<IsRational<R>>, "Arguement MUST be Rational.");
    __TAGS__(Tags::integer);
    static constexpr long long value = R::denom;
};

using Zero      = Rational<0>;
using One       = Rational<1>;
using Two       = Rational<2>;
using Three     = Rational<3>;
using Four      = Rational<4>;
using Five      = Rational<5>;
using Six       = Rational<6>;
using Seven     = Rational<7>;
using Eight     = Rational<8>;
using Nine      = Rational<9>;
using Ten       = Rational<10>;
using Eleven    = Rational<11>;
using Twelve    = Rational<12>;
using Thirteen  = Rational<13>;
using Fourteen  = Rational<14>;
using Fifteen   = Rational<15>;
using Sixteen   = Rational<16>;
using Seventeen = Rational<17>;
using Eighteen  = Rational<18>;
using Nineteen  = Rational<19>;
using Twenty    = Rational<20>;
using Thirty    = Rational<30>;
using Forty     = Rational<40>;
using Fifty     = Rational<50>;
using Sixty     = Rational<60>;
using Seventy   = Rational<70>;
using Eighty    = Rational<80>;
using Ninety    = Rational<90>;
using Hundred   = Rational<100>;
using Thousand  = Rational<1000>;

template <typename R>
using Twenty_   = Twenty::plus<R>;

template <typename R>
using Thirty_   = Thirty::plus<R>;

template <typename R>
using Forty_   = Forty::plus<R>;

template <typename R>
using Fifty_   = Fifty::plus<R>;

template <typename R>
using Sixty_   = Sixty::plus<R>;

template <typename R>
using Seventy_ = Seventy::plus<R>;

template <typename R>
using Eighty_ = Eighty::plus<R>;

template <typename R>
using Ninety_ = Ninety::plus<R>;

template <long long Q, long long P = 1>
constexpr double Rational_v = Rational<Q, P>::value;

template <long long _Num>
constexpr long long Integer_v = Integer<_Num>::value;

TMP_END

#endif