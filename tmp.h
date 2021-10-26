/**
 *  @file   tmp.h
 *  @author Offensive77
 *  @brief  Include this header to obtain all TMP facilities
 *          in my standard library.
 *  @modified: 2021/10/20 Wed.
 */

#ifndef _TMP_H_
#define _TMP_H_

#define __ENABLE_CONVENIENT_TMP__ using namespace TMP;
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace siebenzevan {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

#if __cplusplus >= 201703L
#define __CXX17_IF_CONSTEXPR__ constexpr
#else
#define __CXX17_IF_CONSTEXPR__
#endif

#if __cplusplus >= 201103L
#define __CXX11_CONSTEXPR__ constexpr
#else
#define __CXX11_CONSTEXPR__
#endif

TMP_BEGIN

/**
 *  @struct Eval evaluates the template _Tp's value member.
 */
template <typename _Tp>
constexpr auto Eval = _Tp::value;

TMP_END

#include <iosfwd>
#include <iomanip>
#include <string>
#include <utility>
#include "tmp_traits.h"
#include "tmp_prototype.h"
#include "tmp_symbol.h"
#include "tmp_comparisons.h"
#include "tmp_rational.h"
#include "tmp_complex.h"
#include "tmp_algorithms.h"
#include "tmp_procedure.h"
#include "mybind.h"
#include "tmp_print.h"
#include "tmp_map.h"

#endif