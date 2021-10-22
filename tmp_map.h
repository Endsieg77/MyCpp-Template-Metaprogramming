/**
 *  @file   tmp_map.h
 *  @author Offensive77
 *  @brief  This header defines the map in TMP.
 *  @established: 2021/10/20 Fri.
 *  @modified:    2021/10/21 Fri.
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
struct Map<>: Null
{
    __TAGS__(Tags::map)
    using type    = Null;
    using next    = Null;
    using current = Null;
};

template <typename _First,typename... _Mapto>
struct Map<_First, _Mapto...>: Map<_Mapto...>
{
    static_assert(Eval<IsPair<_First>>, "Elements of Map MUST be cons.");
    using type    = _First;
    using current = Map<_First, _Mapto...>;
    using next    = Map<_Mapto...>;
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
    using type = map::type;
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
          typename = typename std::enable_if<Eval<IsMap<_Map>>>>
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