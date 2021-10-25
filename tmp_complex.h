/**
 *  @file   tmp_complex.h
 *  @author Offensive77
 *  @brief  This header defines the complex number in TMP.
 *  @established: 2021/10/20 Wed.
 *  @modified:    2021/10/21 Thurs.
 */

#ifndef _TMP_COMPLEX_H_
#define _TMP_COMPLEX_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

#include <complex>

TMP_BEGIN

namespace toStringDetails
{
    template <typename Complex>
    std::string toStringImpl()
    {
        using real = typename Complex::real;
        using imag = typename Complex::imag;
        std::string real_part = "", imag_part = "";

        if __CXX17_IF_CONSTEXPR__
        (Eval<NotEqual<real, Rational<0LL>>>)
            real_part = real::to_string();
        if __CXX17_IF_CONSTEXPR__
        (Eval<Greater<imag, Rational<0LL>>>)
        {
            if __CXX17_IF_CONSTEXPR__
            (Eval<NotEqual<imag, Rational<1LL>>>)
                imag_part = '+' + imag::to_string() + 'i';
            else
                imag_part = "+i";
        }
        else if __CXX17_IF_CONSTEXPR__
        (Eval<Less<imag, Rational<0LL>>>)
        {
            if __CXX17_IF_CONSTEXPR__
            (Eval<NotEqual<imag, Rational<-1LL>>>)
                imag_part = imag::to_string() + 'i';
            else
                imag_part = "-i";
        }

        return real_part + imag_part;
    }
}

template <typename _Re = Rational<0LL>, typename _Im = Rational<0LL>>
struct Complex: Prototype<Complex<_Re, _Im>>
{
    Complex() = delete;
    using real = _Re;
    using imag = _Im;
    __TAGS__(Tags::complex);
    static std::string to_string()
    { return toStringDetails::toStringImpl<Complex>(); }
    static constexpr std::complex value = std::complex((double)real::value, (double)imag::value);
};

template <typename C>
struct Real: C::real
{
    Real() = delete;
};

template <typename C>
struct Imag: C::imag
{
    Imag() = delete;
};

TMP_END

#endif