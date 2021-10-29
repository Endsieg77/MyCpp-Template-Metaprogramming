/**
 *  @file   tmp_comparisons.h
 *  @author Offensive77
 *  @brief  This header defines the comparison ops in siebenzevan.
 *  e.g. greater, less, equal...
 *  @copyright reserved.
 */

#ifndef _TMP_COMPARISONS_H_
#define _TMP_COMPARISONS_H_

TMP_BEGIN

/** 
 *  @namespace siebenzevan.CompareDetails hides the detail
 *  of compile-time comparations.
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

/**
 *  @struct Logical True
 */
struct True_type: LogicalPrototype<True_type>
{
    static constexpr bool value = true;
};

/**
 *  @struct Logical False
 */
struct False_type: LogicalPrototype<False_type>
{
    static constexpr bool value = true;
};

/**
 *  @struct siebenzevan.Greater is the compile-time '>' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Greater
    : LogicalPrototype<Greater<_Lhs, _Rhs>>,
      CompareDetails
        ::GreaterImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
{ };

/**
 *  @struct siebenzevan.Less is the compile-time '<' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Less
    :  LogicalPrototype<Less<_Lhs, _Rhs>>,
       CompareDetails
        ::LessImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
     
{ };

/**
 *  @struct siebenzevan.Equal is the compile-time '==' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Equal
    : LogicalPrototype<Equal<_Lhs, _Rhs>>,
      CompareDetails
        ::EqualImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
     
{ };

/**
 *  @struct siebenzevan.NotEqual is the compile-time '!=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct NotEqual
    : LogicalPrototype<NotEqual<_Lhs, _Rhs>>,
      CompareDetails
        ::NotEqualImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
     
{ };

/**
 *  @struct siebenzevan.GreaterEqual is the compile-time '>=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct GreaterEqual
    : LogicalPrototype<GreaterEqual<_Lhs, _Rhs>>,
      CompareDetails
        ::GreaterEqualImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
      
{ };

/**
 *  @struct siebenzevan.LessEqual is the compile-time '<=' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct LessEqual
    : LogicalPrototype<LessEqual<_Lhs, _Rhs>>, 
      CompareDetails
        ::LessEqualImpl<_Lhs, _Rhs, Eval<IsRational<_Lhs>> && Eval<IsRational<_Rhs>>>
      
{ };

/**
 *  @struct siebenzevan.And is the compile-time '&&' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct And
    : LogicalPrototype<And<_Lhs, _Rhs>>,
      CompareDetails
        ::AndImpl<_Lhs, _Rhs, Eval<IsBoolean<_Lhs>> && Eval<IsBoolean<_Rhs>>>
      
{ };

/**
 *  @struct siebenzevan.Or is the compile-time '||' for Rationals.
 */
template <typename _Lhs, typename _Rhs>
struct Or
    : LogicalPrototype<Or<_Lhs, _Rhs>>,
      CompareDetails
        ::OrImpl<_Lhs, _Rhs, Eval<IsBoolean<_Lhs>> && Eval<IsBoolean<_Rhs>>>
      
{ };

/**
 *  @struct siebenzevan.Not is the compile-time '!' for Rationals.
 */
template <typename _Statement>
struct Not
    : LogicalPrototype<Not<_Statement>>,
      CompareDetails
        ::NotImpl<_Statement, Eval<IsBoolean<_Statement>>>
      
{ };

TMP_END

#endif