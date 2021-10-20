/**
 *  @file   tmp_complex.h
 *  @author Offensive77
 *  @brief  This header defines the complex number in TMP.
 *  @established: 2021/10/20 Wed.
 *  @modified:    2021/10/20 Wed.
 */

#ifndef _TMP_COMPLEX_H_
#define _TMP_COMPLEX_H_

TMP_BEGIN

template <typename _Re, typename _Im>
struct Complex
{
    Complex() = delete;
    using real = _Re;
    using imag = _Im;
    static std::string to_string()
    { return _Re::to_string() + '+' + _Im::to_string() + 'i'; }
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