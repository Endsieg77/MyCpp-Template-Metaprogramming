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
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

#include <string>
#include <utility>
#include "tmp_traits.h"
#include "tmp_algorithms.h"
#include "myfunctional.h"
#include "tmp_complex.h"

#endif