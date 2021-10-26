/**
 *  @file   tmp_prototype.h
 *  @author Offensive77
 *  @brief  Include this header to obtain all TMP facilities
 *          in my standard library.
 *  @established: 2021/10/25 Mon.
 *  @modified: 2021/10/25 Mon.
 */

#ifndef _TMP_PROTOTYPE_H_
#define _TMP_PROTOTYPE_H_

#ifndef TMP_BEGIN
#define TMP_BEGIN namespace siebenzevan {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

TMP_BEGIN

template <typename _Tp>
struct Prototype
{
    struct is
    {
        using null      = IsNull<_Tp>;
        using rational  = IsRational<_Tp>;
        using integer   = IsInteger<_Tp>;
        using boolean   = IsBoolean<_Tp>;
        using condition = IsCondition<_Tp>;
        using loop      = IsLoop<_Tp>;
        using complex   = IsComplex<_Tp>;
        using container = IsContainer<_Tp>;
        using map       = IsMap<_Tp>;
        using symbol    = IsSymbol<_Tp>;
        using procedure = IsProcedure<_Tp>;
        /*!Not*/
        struct _not
        {
            using null      = IsNotNull<_Tp>;
            using rational  = IsNotRational<_Tp>;
            using integer   = IsNotInteger<_Tp>;
            using boolean   = IsNotBoolean<_Tp>;
            using condition = IsNotCondition<_Tp>;
            using loop      = IsNotLoop<_Tp>;
            using complex   = IsNotComplex<_Tp>;
            using container = IsNotContainer<_Tp>;
            using map       = IsNotMap<_Tp>;
            using symbol    = IsNotSymbol<_Tp>;
            using procedure = IsNotProcedure<_Tp>;
        };
    };
};

/**
 *  @struct TMP.Null functions behind the curtain.
 */
struct Null: Prototype<Null>
{
    Null() = delete;
    __TAGS__(Tags::null)
};

struct PairPrototype: Prototype<PairPrototype>
{
    __TAGS__(Tags::pair)
};

struct ConditionPrototype: Prototype<ConditionPrototype>
{
    __TAGS__(Tags::condition)
};

template <typename _L1>
struct LogicalPrototype: Prototype<LogicalPrototype<_L1>>
{
    __TAGS__(Tags::boolean)
    template <typename _L2>
    struct _and: And<_L1, _L2>
    { };
    template <typename _L2>
    struct _or: Or<_L1, _L2>
    { };
    struct is: Prototype<LogicalPrototype<_L1>>::is
    {
        struct True: IsTrue<_L1> {};
        struct False: IsFalse<_L1> {};
    };
};

struct It
{
    struct is
    {
        struct True
        {
            template <typename _L>
            struct that: IsTrue<_L> {};
        };
        struct False
        {
            template <typename _L>
            struct that: IsFalse<_L> {};
        };
    };
};

template <typename _R1>
struct RationalPrototype: Prototype<RationalPrototype<_R1>>
{
    __TAGS__(Tags::rational)
    template <typename _R2>
    struct plus: Plus<_R1, _R2>
    { };
    template <typename _R2>
    struct minus: Minus<_R1, _R2>
    { };
    template <typename _R2>
    struct multiply: Multiply<_R1, _R2>
    { };
    template <typename _R2>
    struct divide: Divide<_R1, _R2>
    { };
    struct is: Prototype<RationalPrototype<_R1>>::is
    {
        template <typename _R2>
        struct equal_to: Equal<_R1, _R2> { };
        template <typename _R2>
        struct greater_equal_than: GreaterEqual<_R1, _R2> { };
        template <typename _R2>
        struct less_equal_than: LessEqual<_R1, _R2> { };
        template <typename _R2>
        struct greater_than: Greater<_R1, _R2> { };
        template <typename _R2>
        struct less_than: Less<_R1, _R2> { };
        struct _not: Prototype<RationalPrototype<_R1>>::is::_not
        {
            template <typename _R2>
            struct equal_to: Not<Equal<_R1, _R2>> { };
            template <typename _R2>
            struct greater_equal_than: Not<GreaterEqual<_R1, _R2>> { };
            template <typename _R2>
            struct less_equal_than: Not<LessEqual<_R1, _R2>> { };
            template <typename _R2>
            struct greater_than: Not<GreaterEqual<_R1, _R2>> { };
            template <typename _R2>
            struct less_than: Not<Less<_R1, _R2>> { };
        };
    };
};

struct MapPrototype: Prototype<MapPrototype>
{
    __TAGS__(Tags::map)
};

template <typename _Symb>
struct SymbolPrototype: Prototype<_Symb>
{
    __TAGS__(Tags::symbol)
};

TMP_END

#endif