/**
 *  @file   tmp_condition_statement.h
 *  @author Offensive77
 *  @brief  TMP condition statement If and Cond are defined here.
 *  @modified: 2021/10/19 Tues.
 */

#ifndef _TMP_CONDITION_STATEMENT_H_
#define _TMP_CONDITION_STATEMENT_H_

namespace TMP
{
namespace IfDetails
{
    template <bool _B, typename _Then, typename _Else>
    struct IfImpl: _Then
    {
        using type = _Then;
    };

    template <typename _Then, typename _Else>
    struct IfImpl<false, _Then, _Else>: _Else
    {
        using type = _Else;
    };
}

template <typename _Boolean, typename _Then, typename _Else>
struct If: IfDetails::IfImpl<_Boolean::value, _Then, _Else>
{
    If() = delete;
};

template <typename _Car, typename _Cdr>
struct Case: Pair<_Car, _Cdr>
{
    Case() = delete;
};

template <typename _Else>
struct Else: cons<Rational<true>, _Else>
{
    Else() = delete;
};

namespace CondDetails
{
template <typename... Pred_Conseq>
struct CondImpl
{ };

template <typename _First, typename... Pred_Conseq>
struct CondImpl<_First, Pred_Conseq...>
{
    using type =
    If<typename _First::car,
       typename _First::cdr,
       typename CondImpl<Pred_Conseq...>::type>::type;
};

template <bool, typename _Tp>
struct _LstImpl
{
    using type = _Tp;
};

template <typename _Tp>
struct _LstImpl<false, _Tp>
{
    using type = Null;
};

template <typename _LstButNotLeast>
struct CondImpl<_LstButNotLeast>
{
    using type =
        _LstImpl<static_cast<bool>(_LstButNotLeast::car::value),
             typename _LstButNotLeast::cdr>::type;
};
}

template <typename... Pred_Conseq>
struct Cond: CondDetails::CondImpl<Pred_Conseq...>::type
{
    Cond() = delete;
};

}

#endif