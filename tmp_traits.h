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

/**
 *  Universal tag type.
 */
using tag_type = unsigned long long;

/**
 *  @enum All tags are defined in this enumeration.
 */
enum class Tags: tag_type
{
    null      = 0ULL,
    rational  = 1ULL,
    integer   = 1ULL << 1ULL,
    boolean   = 1ULL << 2ULL,
    condition = 1ULL << 3ULL,
    loop      = 1ULL << 4ULL,
    complex   = 1ULL << 5ULL,
    container = 1ULL << 6ULL,
    pair      = 1ULL << 7ULL,
    map       = 1ULL << 8ULL,
    symbol    = 1ULL << 9ULL,
    procedure = 1ULL << 10ULL,
};

template<typename... Tag>
inline constexpr tag_type tag_helper(Tag&&... tags)
{
    return ((tag_type)tags | ...);
}

template <typename _Tp>
struct IsNull: LogicalPrototype<IsNull<_Tp>>
{
    IsNull() = delete;
    static constexpr bool value = _Tp::tag == 0;
};

template <typename _Tp>
struct IsNotNull: LogicalPrototype<IsNotNull<_Tp>>
{
    IsNotNull() = delete;
    static constexpr bool value = !IsNull<_Tp>::value;
};

template <typename _Tp>
struct IsRational: LogicalPrototype<IsRational<_Tp>>
{
    IsRational() = delete;
    __HAS_TAG__(Tags::rational)
};

template <typename _Tp>
struct IsNotRational: LogicalPrototype<IsNotRational<_Tp>>
{
    IsNotRational() = delete;
    static constexpr bool value = !IsRational<_Tp>::value;
};

template <typename _Tp>
struct IsInteger: LogicalPrototype<IsInteger<_Tp>>
{
    IsInteger() = delete;
    __HAS_TAG__(Tags::integer)
};

template <typename _Tp>
struct IsNotInteger: LogicalPrototype<IsNotInteger<_Tp>>
{
    IsNotInteger() = delete;
    static constexpr bool value = !IsInteger<_Tp>::value;
};

template <typename _Tp>
struct IsBoolean: LogicalPrototype<IsBoolean<_Tp>>
{
    IsBoolean() = delete;
    __HAS_TAG__(Tags::boolean)
};

template <typename _Tp>
struct IsNotBoolean: LogicalPrototype<IsNotBoolean<_Tp>>
{
    IsNotBoolean() = delete;
    static constexpr bool value = !IsBoolean<_Tp>::value;
};

template <typename _Tp>
struct IsCondition: LogicalPrototype<IsCondition<_Tp>>
{
    IsBoolean() = delete;
    __HAS_TAG__(Tags::condition)
};

template <typename _Tp>
struct IsNotCondition: LogicalPrototype<IsNotCondition<_Tp>>
{
    IsNotCondition() = delete;
    static constexpr bool value = !IsCondition<_Tp>::value;
};

template <typename _Tp>
struct IsLoop: LogicalPrototype<IsLoop<_Tp>>
{
    IsBoolean() = delete;
    __HAS_TAG__(Tags::loop)
};

template <typename _Tp>
struct IsNotLoop: LogicalPrototype<IsNotLoop<_Tp>>
{
    IsNotLoop() = delete;
    static constexpr bool value = !IsLoop<_Tp>::value;
};

template <typename _Tp>
struct IsComplex: LogicalPrototype<IsComplex<_Tp>>
{
    __HAS_TAG__(Tags::complex)
};

template <typename _Tp>
struct IsNotComplex: LogicalPrototype<IsNotComplex<_Tp>>
{
    IsNotComplex() = delete;
    static constexpr bool value = !IsComplex<_Tp>::value;
};

template <typename _Tp>
struct IsContainer: LogicalPrototype<IsContainer<_Tp>>
{
    __HAS_TAG__(Tags::container)
};

template <typename _Tp>
struct IsNotContainer: LogicalPrototype<IsNotContainer<_Tp>>
{
    IsNotContainer() = delete;
    static constexpr bool value = !IsContainer<_Tp>::value;
};

template <typename _Tp>
struct IsPair: LogicalPrototype<IsPair<_Tp>>
{
    __HAS_TAG__(Tags::pair)
};

template <typename _Tp>
struct IsNotPair: LogicalPrototype<IsNotPair<_Tp>>
{
    IsNotPair() = delete;
    static constexpr bool value = !IsPair<_Tp>::value;
};

template <typename _Tp>
struct IsMap: LogicalPrototype<IsMap<_Tp>>
{
    __HAS_TAG__(Tags::map)
};

template <typename _Tp>
struct IsNotMap: LogicalPrototype<IsNotMap<_Tp>>
{
    IsNotMap() = delete;
    static constexpr bool value = !IsMap<_Tp>::value;
};

template <typename _Tp>
struct IsSymbol: LogicalPrototype<IsSymbol<_Tp>>
{
    __HAS_TAG__(Tags::symbol)
};

template <typename _Tp>
struct IsNotSymbol: LogicalPrototype<IsNotSymbol<_Tp>>
{
    IsNotSymbol() = delete;
    static constexpr bool value = !IsSymbol<_Tp>::value;
};

template <typename _Tp>
struct IsProcedure: LogicalPrototype<IsProcedure<_Tp>>
{
    __HAS_TAG__(Tags::procedure)
};

template <typename _Tp>
struct IsNotProcedure: LogicalPrototype<IsNotProcedure<_Tp>>
{
    IsNotProcedure() = delete;
    static constexpr bool value = !IsProcedure<_Tp>::value;
};

template <typename _L>
struct IsTrue
{
    static_assert(Eval<typename _L::is::boolean>, "Only Logical values can be true or false!");
    static constexpr bool value = Eval<_L>;
};

template <typename _L>
struct IsFalse
{
    static_assert(Eval<typename _L::is::boolean>, "Only Logical values can be true or false!");
    static constexpr bool value = !Eval<_L>;
};

TMP_END

#endif