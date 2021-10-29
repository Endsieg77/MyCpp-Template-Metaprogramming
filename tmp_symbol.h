/**
 *  @file tmp_symbol.h
 *  @author @irrequietus contributes most of these.
 *  @brief The most content of this header are copied from the
 *  Internet 'coz I cannot handle part of techniques to implement
 *  the functions I need.
 */

#ifndef _TMP_SYMBOL_H_
#define _TMP_SYMBOL_H_

TMP_BEGIN

// from https://github.com/irrequietus/typestring
namespace SymbolDetails
{
template <char... _Char>
struct Symbol: SymbolPrototype<Symbol<_Char...>>
{
    Symbol() {}
    static constexpr char value[sizeof...(_Char) + 1] = { _Char ..., '\0' };
};

template <int N, int M>
constexpr char tygrab(char const (&c)[M]) noexcept {
    return c[N < M ? N : M - 1];
}

template <char... X>
auto typoke(Symbol<X...>) -> Symbol<X...>;

template <char... X, char... Y>
auto typoke(Symbol<X...>, Symbol<'\0'>, Symbol<Y>...) -> Symbol<X...>;

template <char A, char... X, char... Y>
auto typoke(Symbol<X...>, Symbol<A>, Symbol<Y>...) -> decltype(typoke(Symbol<X..., A>(), Symbol<Y>()...));

template <char... C>
auto typeek(Symbol<C...>) -> decltype(typoke(Symbol<C>()...));
}

#define TYPESTRING16(n, x)                                                                                      \
    SymbolDetails::tygrab<0x##n##0>(x), SymbolDetails::tygrab<0x##n##1>(x), SymbolDetails::tygrab<0x##n##2>(x), SymbolDetails::tygrab<0x##n##3>(x), \
    SymbolDetails::tygrab<0x##n##4>(x), SymbolDetails::tygrab<0x##n##5>(x), SymbolDetails::tygrab<0x##n##6>(x), SymbolDetails::tygrab<0x##n##7>(x), \
    SymbolDetails::tygrab<0x##n##8>(x), SymbolDetails::tygrab<0x##n##9>(x), SymbolDetails::tygrab<0x##n##A>(x), SymbolDetails::tygrab<0x##n##B>(x), \
    SymbolDetails::tygrab<0x##n##C>(x), SymbolDetails::tygrab<0x##n##D>(x), SymbolDetails::tygrab<0x##n##E>(x), SymbolDetails::tygrab<0x##n##F>(x)

#define TYPESTRING32(n, x) TYPESTRING16(n##0, x), TYPESTRING16(n##1, x)

#define symbol(x) decltype(SymbolDetails::typeek(SymbolDetails::Symbol<TYPESTRING32(, x)>()))

TMP_END

#endif