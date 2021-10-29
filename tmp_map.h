/**
 *  @file   tmp_map.h
 *  @author Offensive77
 *  @brief  This header defines date structure the map in siebenzevan.
 *  @copyright reserved.
 */

#ifndef _TMP_MAP_H_
#define _TMP_MAP_H_
#ifndef TMP_BEGIN
#define TMP_BEGIN namespace TMP {
#endif
#ifndef TMP_END
#define TMP_END   }
#endif

TMP_BEGIN

template <typename... _Mapto>
struct Map
{ };

template <>
struct Map<>: MapPrototype
{
    using type    = Null;
    using next    = Null;
    using current = Null;
};

namespace ForDetails
{

template <typename Map, unsigned _Times>
struct ForImpl
{
    static std::ostream &print(std::ostream &os)
    {
        ReadMap<Map>(os) << std::endl;
        return ForImpl<Map, _Times - 1>::print(os);
    }
};

template <typename Map>
struct ForImpl<Map, 0>
{
    static std::ostream &print(std::ostream &os)
    { return os; }
};

};

template <typename _First,typename... _Mapto>
struct Map<_First, _Mapto...>: Map<_Mapto...>
{
    static_assert(Eval<IsPair<_First>>, "Elements of Map MUST be cons.");
    using type    = _First;
    using current = Map<_First, _Mapto...>;
    using next    = Map<_Mapto...>;
    struct shall
    {
        struct showItsMetainfo
        {
            static std::ostream &with(std::ostream &os)
            { return ReadMap<Map>(os); }
            struct once
            {
                static constexpr auto with = showItsMetainfo::with;
            };
            struct twice
            {
                static std::ostream &with(std::ostream &os)
                { return ForDetails::ForImpl<Map, 2>::print(os); }
            };
            template <unsigned _Times>
            struct _for
            {
                struct times
                {
                    static std::ostream &with(std::ostream &os) 
                    { return ForDetails::ForImpl<Map, _Times>::print(os); }
                };
            };
        };
    };
};

namespace ReadMapDetails
{
template <typename>
struct ReadHelper
{ };

template <typename... _Mapto>
struct ReadHelper<Map<_Mapto...>>
{ };

template <typename _First, typename... _Mapto>
struct ReadHelper<Map<_First, _Mapto...>>
{
    using map  = Map<_First, _Mapto...>;
    using type = typename map::type;
    static std::ostream &print(std::ostream &os)
    {
        os
          << " Key: "    << std::setw(20);
        metaprint<car<type>>(os);
        os
          << " Value: "  << std::setw(20);
        metaprint<cdr<type>>(os);
        os << std::endl;
        ReadHelper<Map<_Mapto...>>::print(os);
        return os;
    }
};

template <>
struct ReadHelper<Map<>>
{
    static std::ostream &print(std::ostream &os)
    {
        os << "======================  MAP END  ======================" << std::endl;
        return os;
    }
};
}

template <typename _Map,
          typename>
std::ostream &ReadMap(std::ostream &os)
{
    os << "====================== MAP BEGIN ======================" << std::endl;
    ReadMapDetails
      ::ReadHelper<_Map>
        ::print(os);
    return os;
}

TMP_END

#endif