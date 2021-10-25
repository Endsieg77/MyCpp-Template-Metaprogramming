/**
 *  @file   tmp_comparisons.h
 *  @author Offensive77
 *  @brief  This header defines the comparisons in TMP.
 *  @established: 2021/10/21 Thurs.
 *  @modified:    2021/10/21 Thurs.
 */

#ifndef _TMP_COMPARISONS_H_
#define _TMP_COMPARISONS_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

TMP_BEGIN

/** 
 *  @namespace TMP.CompareDetails hides the detail
 *             of compile-time comparations.
 */
namespace CompareDetails
{
    template <typename _Lhs, typename _Rhs, bool _isAllRational = true>
    struct GreaterImpl
    {
        static constexpr bool value = _Lhs::num * _Rhs::denom > _Rhs::num * _Lhs::denom;
    };

    template <typename _Lhs, typename _Rhs>
    struct GreaterImpl<_Lhs, _Rhs, false>
    { };

    template <typename _Lhs, typename _Rhs, bool _isAllRational = true>
    struct LessImpl
    {
        static constexpr bool value = _Lhs::num * _Rhs::denom < _Rhs::num * _Lhs::denom;
    };

    template <typename _Lhs, typename _Rhs>
    struct LessImpl<_Lhs, _Rhs, false>
    { };

    template <typename _Lhs, typename _Rhs, bool _isAllRational = true>
    struct EqualImpl
    {
        static constexpr bool value = _Lhs::denom * _Rhs::num == _Rhs::denom * _Lhs::num;
    };

    template <typename _Lhs, typename _Rhs>
    struct EqualImpl<_Lhs, _Rhs, false>
    { };

    template <typename _Lhs, typename _Rhs, bool _isAllRational = true>
    struct NotEqualImpl
    {
        static constexpr bool value = _Lhs::denom * _Rhs::num != _Rhs::denom * _Lhs::num;
    };

    template <typename _Lhs, typename _Rhs>
    struct NotEqualImpl<_Lhs, _Rhs, false>
    { };

    template <typename _Lhs, typename _Rhs, bool _isAllRational = true>
    struct GreaterEqualImpl
    {
        static constexpr bool value = GreaterImpl<_Lhs, _Rhs>::value || EqualImpl<_Lhs, _Rhs>::value;
    };

    template <typename _Lhs, typename _Rhs>
    struct GreaterEqualImpl<_Lhs, _Rhs, false>
    { };

    template <typename _Lhs, typename _Rhs, bool _isAllRational = true>
    struct LessEqualImpl
    {
        static constexpr bool value = LessImpl<_Lhs, _Rhs>::value || EqualImpl<_Lhs, _Rhs>::value;
    };

    template <typename _Lhs, typename _Rhs>
    struct LessEqualImpl<_Lhs, _Rhs, false>
    { };

    template <typename _Lhs, typename _Rhs, bool _isAllBoolean = true>
    struct AndImpl
    {
        static constexpr bool value = _Lhs::value && _Rhs::value;
    };

    template <typename _Lhs, typename _Rhs>
    struct AndImpl<_Lhs, _Rhs, false>
    { };

    template <typename _Lhs, typename _Rhs, bool _isAllBoolean = true>
    struct OrImpl
    {
        static constexpr bool value = _Lhs::value || _Rhs::value;
    };

    template <typename _Lhs, typename _Rhs>
    struct OrImpl<_Lhs, _Rhs, false>
    { };

    template <typename _Statement, bool _isBoolean = true>
    struct NotImpl
    {
        static constexpr bool value = !_Statement::value;
    };

    template <typename _Statement>
    struct NotImpl<_Statement, false>
    { };
}

// Logical True and False
struct LogicalPrototype: Prototype<LogicalPrototype>
{
    __TAGS__(Tags::boolean)
};

struct True_type: LogicalPrototype
{
    True_type() = delete;
    static constexpr bool   value = true;
};

struct False_type: LogicalPrototype
{
    False_type() = delete;
    static constexpr bool value = true;
};

/**
 *  @struct TMP.Greater is the compile-time '>' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Greater
    : LogicalPrototype,
      CompareDetails
        ::GreaterImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
{
    Greater() = delete;
};

/**
 *  @struct TMP.Less is the compile-time '<' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Less
    :  LogicalPrototype,
       CompareDetails
        ::LessImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
     
{
    Less() = delete;
};

/**
 *  @struct TMP.Equal is the compile-time '==' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Equal
    : LogicalPrototype,
      CompareDetails
        ::EqualImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
     
{
    Equal() = delete;
};

/**
 *  @struct TMP.NotEqual is the compile-time '!=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct NotEqual
    : LogicalPrototype,
      CompareDetails
        ::NotEqualImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
     
{
    NotEqual() = delete;
};

/**
 *  @struct TMP.GreaterEqual is the compile-time '>=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct GreaterEqual
    : LogicalPrototype,
      CompareDetails
        ::GreaterEqualImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
      
{
    GreaterEqual() = delete;
};

/**
 *  @struct TMP.LessEqual is the compile-time '<=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct LessEqual
    : LogicalPrototype, 
      CompareDetails
        ::LessEqualImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
      
{
    LessEqual() = delete;
};

/**
 *  @struct TMP.And is the compile-time '&&' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct And
    : LogicalPrototype,
      CompareDetails
        ::AndImpl<_Lhs, _Rhs, Eval<IsBoolean<_Lhs>> && Eval<IsBoolean<_Rhs>>>
      
{
    And() = delete;
};

/**
 *  @struct TMP.Or is the compile-time '||' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Or
    : LogicalPrototype,
      CompareDetails
        ::OrImpl<_Lhs, _Rhs, Eval<IsBoolean<_Lhs>> && Eval<IsBoolean<_Rhs>>>
      
{
    Or() = delete;
};

/**
 *  @struct TMP.Not is the compile-time '!' for Rationals.
 */
template <typename _Statement>
struct Not
    : LogicalPrototype,
      CompareDetails
        ::NotImpl<_Statement, Eval<IsBoolean<_Statement>>>
      
{
    Not() = delete;
};

TMP_END

#endif