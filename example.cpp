#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <string_view>
#include "tmp.h"

using namespace std;
using namespace TMP;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    using r0 = TMP::Rational<0>;
    using r1 = TMP::Rational<4, 6>;
    using r2 = TMP::Rational<11, 4>;
    using r3 = TMP::Rational<15, 2>;
    using r4 = TMP::Rational<1>;

    cout << TMP::Sqrt<TMP::Rational<1191ll, 443ll>>::value << endl;

    using _if = TMP::If<Greater<r1, r2>, r1, r2>;
    cout << _if::value << endl;
    
    using _res =
    Cond<
        Case<And<Less<r2, r1>, Less<r4, r1>>, r1>,
        Case<Or<Less<r3, r2>, Not<LessEqual<r4, r0>>>, r2>,
        Case<Greater<r0, r4>, r4>,
        Else<r3>>;
        
    cout << _res::value << endl;

    return 0;
}