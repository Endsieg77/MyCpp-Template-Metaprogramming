/**
 *  @file   tmp.h
 *  @author Offensive77
 *  @brief  Include this header to obtain all TMP facilities
 *          in my standard library.
 *  @modified: 2021/10/20 Wed.
 */

#ifndef _TMP_H_
#define _TMP_H_

#define let using
#define __ENABLE_CONVENIENT_TMP__ using namespace siebenzevan;
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

template <typename _L1> struct LogicalPrototype;
template <typename _L1, typename _L2> struct And;
template <typename _L1, typename _L2> struct Or;
struct True_type;
struct False_type;
template <typename _Boolean, typename _Then, typename _Else> struct If;

/**
 *  Comparisons declaration:
 */
template <typename _R1, typename _R2> struct Equal;
template <typename _R1, typename _R2> struct GreaterEqual;
template <typename _R1, typename _R2> struct LessEqual;
template <typename _R1, typename _R2> struct Greater;
template <typename _R1, typename _R2> struct Less;
template <typename _Statement> struct Not;

/**
 *  Basic Arithmetics declaration:
 */
template <typename _R1, typename _R2> struct Plus;
template <typename _R1, typename _R2> struct Minus;
template <typename _R1, typename _R2> struct Multiply;
template <typename _R1, typename _R2> struct Divide;

TMP_END

#include <iosfwd>
#include <iomanip>
#include <string>
#include <utility>
#include "tmp_defs.h"
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