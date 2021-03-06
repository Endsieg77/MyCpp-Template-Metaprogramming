/**
 *  @file tmp_print.h
 *  @author Offensive77
 *  @brief In this header I introduced the methods of output the
 *  TMP Objects, which i call metaprint, meaning it is the print
 *  of print. In fact it deserves the name.
 *  @copyright reserved.
 */
#ifndef _TMP_PRINT_H_
#define _TMP_PRINT_H_

TMP_BEGIN

template <typename _Map, typename = typename std::enable_if<Eval<IsMap<_Map>>>>
std::ostream &ReadMap(std::ostream &os);

namespace printNamespace
{
    template <typename _Tp, typename = void>
    struct printHelper
    { };

    template <typename _Tp>
    struct printHelper<_Tp,
                       typename std::enable_if<Eval<IsRational<_Tp>>>::type>
    {
        static std::ostream &print(std::ostream &os)
        {
            os << _Tp::to_string();
            return os;
        }
    };

    template <typename _Tp>
    struct printHelper<_Tp,
                       typename std::enable_if<Eval<IsPair<_Tp>>>::type>
    {
        static std::ostream &print(std::ostream &os)
        {
            os
              << "(cons ";
            printHelper<car<_Tp>>::print(os) 
              << " ";
            printHelper<cdr<_Tp>>::print(os)
              << ")";
            return os;
        }
    };

    template <typename _Tp>
    struct printHelper<_Tp,
                       typename std::enable_if<Eval<IsComplex<_Tp>>>::type>
    {
        static std::ostream &print(std::ostream &os)
        {
            os << _Tp::to_string();
            return os;
        }
    };

    template <typename _Tp>
    struct printHelper<_Tp,
                       typename std::enable_if<Eval<IsSymbol<_Tp>>>::type>
    {
        static std::ostream &print(std::ostream &os)
        {
            os << _Tp::value;
            return os;
        }
    };

    template <typename _Tp>
    struct printHelper<_Tp,
                       typename std::enable_if<Eval<IsMap<_Tp>>>::type>
    {
        static std::ostream &print(std::ostream &os)
        {
            ReadMap<_Tp>(os);
            return os;
        }
    };
}

template <typename _Tp>
std::ostream &metaprint(std::ostream &os)
{
    printNamespace::printHelper<_Tp>::print(os);
    return os;
}

TMP_END

#endif