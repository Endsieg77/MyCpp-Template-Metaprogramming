/**
 *  @file   tmp_traits.h
 *  @author Offensive77
 *  @brief  Traits for my templates.
 *  @copyright reserved.
 */

#ifndef _TMP_TRAITS_H_
#define _TMP_TRAITS_H_

#define __TAGS__(...) static constexpr tag_type tag = tag_helper(__VA_ARGS__);
#define __HAS_TAG__(_tag_) bool(_Tp::tag & (tag_type)(_tag_))

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

/**
 *  tag_helper uses C++ 17 fold expression to parse the
 *  outcome of its input value's bitwise OR.
 */
template<typename... Tag>
inline constexpr tag_type tag_helper(Tag&&... tags)
{
    return ((tag_type)tags | ...);
}

/**
 *  My type traits, dependent on SFINAE (std::enable_if)
 */

template <typename _Tp, typename = void>
struct IsNull: LogicalPrototype<IsNull<_Tp>>
{
    IsNull() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsNull<_Tp,
              std::enable_if_t<__HAS_TAG__(Tags::null)>>
    : LogicalPrototype<IsNull<_Tp>>
{
    IsNull() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotNull: LogicalPrototype<IsNotNull<_Tp>>
{
    IsNotNull() = delete;
    static constexpr bool value = !IsNull<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsRational: LogicalPrototype<IsRational<_Tp>>
{
    IsRational() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsRational<_Tp,
                  std::enable_if_t<__HAS_TAG__(Tags::rational)>>
    : LogicalPrototype<IsRational<_Tp>>
{
    IsRational() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotRational: LogicalPrototype<IsNotRational<_Tp>>
{
    IsNotRational() = delete;
    static constexpr bool value = !IsRational<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsInteger: LogicalPrototype<IsInteger<_Tp>>
{
    IsInteger() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsInteger<_Tp,
                 std::enable_if_t<__HAS_TAG__(Tags::integer)>>
    : LogicalPrototype<IsInteger<_Tp>>
{
    IsInteger() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotInteger: LogicalPrototype<IsNotInteger<_Tp>>
{
    IsNotInteger() = delete;
    static constexpr bool value = !IsInteger<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsBoolean: LogicalPrototype<IsBoolean<_Tp>>
{
    IsBoolean() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsBoolean<_Tp,
                 std::enable_if_t<__HAS_TAG__(Tags::boolean)>>
    : LogicalPrototype<IsBoolean<_Tp>>
{
    IsBoolean() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotBoolean: LogicalPrototype<IsNotBoolean<_Tp>>
{
    IsNotBoolean() = delete;
    static constexpr bool value = !IsBoolean<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsCondition: LogicalPrototype<IsCondition<_Tp>>
{
    IsCondition() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsCondition<_Tp, 
                   std::enable_if_t<__HAS_TAG__(Tags::condition)>>
    : LogicalPrototype<IsCondition<_Tp>>
{
    IsCondition() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotCondition: LogicalPrototype<IsNotCondition<_Tp>>
{
    IsNotCondition() = delete;
    static constexpr bool value = !IsCondition<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsLoop: LogicalPrototype<IsLoop<_Tp>>
{
    IsLoop() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsLoop<_Tp, 
              std::enable_if_t<__HAS_TAG__(Tags::loop)>>
    : LogicalPrototype<IsLoop<_Tp>>
{
    IsLoop() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotLoop: LogicalPrototype<IsNotLoop<_Tp>>
{
    IsNotLoop() = delete;
    static constexpr bool value = !IsLoop<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsComplex: LogicalPrototype<IsComplex<_Tp>>
{
    IsComplex() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsComplex<_Tp, 
                 std::enable_if_t<__HAS_TAG__(Tags::complex)>>
    : LogicalPrototype<IsComplex<_Tp>>
{
    IsComplex() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotComplex: LogicalPrototype<IsNotComplex<_Tp>>
{
    IsNotComplex() = delete;
    static constexpr bool value = !IsComplex<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsContainer: LogicalPrototype<IsContainer<_Tp>>
{
    IsContainer() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsContainer<_Tp, 
                   std::enable_if_t<__HAS_TAG__(Tags::container)>>
    : LogicalPrototype<IsContainer<_Tp>>
{
    IsContainer() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsNotContainer: LogicalPrototype<IsNotContainer<_Tp>>
{
    IsNotContainer() = delete;
    static constexpr bool value = !IsContainer<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsPair: LogicalPrototype<IsPair<_Tp>>
{
    IsPair() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsPair<_Tp, 
              std::enable_if_t<__HAS_TAG__(Tags::pair)>>
    : LogicalPrototype<IsPair<_Tp>>
{
    IsPair() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotPair: LogicalPrototype<IsNotPair<_Tp>>
{
    IsNotPair() = delete;
    static constexpr bool value = !IsPair<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsMap: LogicalPrototype<IsMap<_Tp>>
{
    IsMap() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsMap<_Tp, 
             std::enable_if_t<__HAS_TAG__(Tags::map)>>
    : LogicalPrototype<IsMap<_Tp>>
{
    IsMap() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotMap: LogicalPrototype<IsNotMap<_Tp>>
{
    IsNotMap() = delete;
    static constexpr bool value = !IsMap<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsSymbol: LogicalPrototype<IsSymbol<_Tp>>
{
    IsSymbol() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsSymbol<_Tp, 
                std::enable_if_t<__HAS_TAG__(Tags::symbol)>>
    : LogicalPrototype<IsSymbol<_Tp>>
{
    IsSymbol() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotSymbol: LogicalPrototype<IsNotSymbol<_Tp>>
{
    IsNotSymbol() = delete;
    static constexpr bool value = !IsSymbol<_Tp>::value;
};

template <typename _Tp, typename = void>
struct IsProcedure: LogicalPrototype<IsProcedure<_Tp>>
{
    IsProcedure() = delete;
    static constexpr bool value = false;
};

template <typename _Tp>
struct IsProcedure<_Tp, 
                   std::enable_if_t<__HAS_TAG__(Tags::procedure)>>
    : LogicalPrototype<IsProcedure<_Tp>>
{
    IsProcedure() = delete;
    static constexpr bool value = true;
};

template <typename _Tp>
struct IsNotProcedure: LogicalPrototype<IsNotProcedure<_Tp>>
{
    IsNotProcedure() = delete;
    static constexpr bool value = !IsProcedure<_Tp>::value;
};

template <typename _L>
struct IsTrue: LogicalPrototype<IsTrue<_L>>
{
    static_assert(Eval<typename _L::is::boolean>, "Only Logical values can be true or false!");
    static constexpr bool value = Eval<_L>;
};

template <typename _L>
struct IsFalse: LogicalPrototype<IsFalse<_L>>
{
    static_assert(Eval<typename _L::is::boolean>, "Only Logical values can be true or false!");
    static constexpr bool value = !Eval<_L>;
};

TMP_END

#endif