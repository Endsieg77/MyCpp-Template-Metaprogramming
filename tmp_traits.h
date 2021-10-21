/**
 *  @file   tmp_traits.h
 *  @author Offensive77
 *  @brief  Traits for my templates.
 *  @modified: 2021/10/20 Wed.
 */

#ifndef _TMP_TRAITS_H_
#define _TMP_TRAITS_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

#define __TAGS__(...) static constexpr tag_type tag = tag_helper(__VA_ARGS__);
#define __HAS_TAG__(_tag_) static constexpr bool value = _Tp::tag & (tag_type)(_tag_);

TMP_BEGIN

/**
 *  Universal tag type.
 */
using tag_type = unsigned long long;

/**
 *  @enum All tags are defined in this enumeration.
 */
enum class Tags: tag_type
{
    rational  = 1ULL,
    integer   = 1ULL << 1ULL,
    boolean   = 1ULL << 2ULL,
    condition = 1ULL << 3ULL,
    loop      = 1ULL << 4ULL,
    complex   = 1ULL << 5ULL,
    container = 1ULL << 6ULL,
};

template<typename... Tag>
inline constexpr tag_type tag_helper(Tag&&... tags)
{
    return ((tag_type)tags | ...);
}

template <typename _Tp>
struct IsRational
{
    IsRational() = delete;
    __HAS_TAG__(Tags::rational)
};

template <typename _Tp>
struct IsInteger
{
    IsInteger() = delete;
    __HAS_TAG__(Tags::integer)
};

template <typename _Tp>
struct IsBoolean
{
    IsBoolean() = delete;
    __HAS_TAG__(Tags::boolean)
};

template <typename _Tp>
struct IsCondition
{
    IsBoolean() = delete;
    __HAS_TAG__(Tags::condition)
};

template <typename _Tp>
struct IsLoop
{
    IsBoolean() = delete;
    __HAS_TAG__(Tags::loop)
};

template <typename _Tp>
struct IsComplex
{
    __HAS_TAG__(Tags::complex)
};

template <typename _Tp>
struct Container
{
    __HAS_TAG__(Tags::container)
};

TMP_END

#endif