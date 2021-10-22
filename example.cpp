#pragma GCC optimize(2)
#include "tmp.h"
#include <iostream>
#include <string_view>

using namespace std;
using namespace TMP;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    using r0 = Rational<0>;
    using r1 = Rational<4, 6>;
    using r2 = Rational<11, 4>;
    using r3 = Rational<15, 2>;
    using r4 = Rational<1>;
    using c1 = Complex<Rational<3, 4>, Rational<1>>;
    using c2 = Complex<Rational<3, 4>, Rational<-1>>;
    using c3 = Complex<Rational<19, 7>, Rational<-3, 11>>;
    using i1 = Integer<3>;

    cout << Eval<Sqrt<Rational<2>>> << endl;
    cout << Eval<Sqrt<Rational<414, 567>>> << endl;

    using _if = If<Greater<r1, r2>, r1, r2>;
    cout << Eval<_if> << endl;
    
    using _res =
      Cond<
          Case<And<Less<r2, r1>, Less<r4, r1>>, r1>,
          Case<Or<Less<r3, r2>, LessEqual<r4, r0>>, r2>,
          Case<Greater<r0, r4>, r4>,
          Else<r3>,
          Else<r4>>;
        
    cout << Eval<_res> << endl;
    cout << c1::to_string() << ' ' << c2::to_string() << endl;
    cout << Plus<c1, c2>::to_string() << endl;
    cout << Minus<c1, c2>::to_string() << endl;
    cout << Divide<c1, c2>::to_string() << endl;
    cout << Multiply<c1, c2>::to_string() << endl;

    using map =
      Map<
          cons<c2, r1>,
          cons<c1, r3>,
          cons<c3, r2>,
          cons<Plus<c1, c3>, r4>>;
    ReadMap<map>(cout);

    metaprint<r2>(cout) << endl;
    metaprint<i1>(cout) << endl;
    metaprint<c3>(cout) << endl;
    metaprint<cons<r1, c3>>(cout) << endl;

    return 0;
}