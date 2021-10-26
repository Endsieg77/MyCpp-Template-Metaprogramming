#pragma GCC optimize(2)
#include "tmp.h"
#include <iostream>
#include <string_view>

using namespace std;
using namespace siebenzevan;

template <typename>
struct A {
    struct B {
        struct C {};
    };
};

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
    using symb = symbol("You really born singer.");

    cout << Eval<Sqrt<Rational<2>>> << endl;
    cout << Eval<Sqrt<Rational<414, 567>>> << endl;
    
    using _res =
      Cond<
          Case<And<Less<r2, r1>, Less<r4, r1>>, r1>,
          Case<Or<Less<r3, r2>, LessEqual<r4, r0>>, r2>,
          Case<Greater<r0, r4>, r4>,
          Else<r3>,
          Else<r4>>;

    using map =
      Map<
          cons<c2, r1>,
          cons<c1, r3>,
          cons<c3, r2>,
          cons<Plus<c1, c3>, r4>,
          cons<symbol("Hello, world."), c3>>;

    metaprint<symbol("wssb")>(cout) << endl;
    cout << Eval<map::is::map> << endl;
    cout << Eval<r1::is::rational> << endl;
    cout << Eval<r1::is::_not::rational> << endl;
    map::shall::showItsMetainfo::with(cout) << endl;
    map::shall::showItsMetainfo::twice::with(cout) << endl;
    map::shall::showItsMetainfo::_for<4>::times::with(cout) << endl;

    Do<[] (int x) { cout << "Test" << endl; }>
        ::If<It::is::False::that<
                r1::plus<r2>::is::_not::equal_to<r3>
            ::_and<
                map::is::_not::map::_or<map::is::map>>>>
        ::execute(1);

    return 0;
}