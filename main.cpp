#include <iostream>
#define __ENABLE_TMP_plusplus__
#include "./include/tmp.h"

using namespace std;
__ENABLE_CONVENIENT_TMP__

int main()
{
    let r0   = make_rat(0);
    let r1   = make_rat(4 _over 6);
    let r2   = make_rat(11 _over 4);
    let r3   = make_rat(15 _over 2);
    let r4   = make_int(1);
    let c1   = make_complex(make_rat(3 _over 4),  make_rat(1));
    let c2   = make_complex(make_rat(3 _over 4),  make_rat(-1));
    let c3   = make_complex(make_rat(19 _over 7), make_rat(-3 _over 11));
    let i1   = make_int(3);
    let symb = symbol("You really born singer.");

    display evaluate(_sqrt(make_rat(414 _over 567))) newline;
    
    let _res =
      cond(
          _case(r2 _is less_than (r1) __and (r4 _is less_than (r1))
                    _then r1),
          _case(r3 _is less_equal_than (r1)
                    _then r2),
          _case(r0 _is greater_than (r1)
                    _then r4),
          _else(r3));

    let map =
      make_map(
          _pair(c2 _with r1),
          _pair(c1 _with r3),
          _pair(c3 _with r2),
          _pair(c1 _plus(c3) _with r4),
          _pair(symbol("Hello, world.") _with c3));

    metadisplay(symbol("wssb")) newline;
    map _shall::showItsMetainfo::with (cout) newline;
    map _shall::showItsMetainfo::twice::with (cout) newline;
    map _shall::showItsMetainfo::_for<4>::times::with (cout) newline;

    static constexpr auto SomePrint = lambda() { metaprint<symbol("Wsgjb")>(cout) << endl; };

    let us =
      _Do(SomePrint)
        _If(It _is _false _that(
                r1 _plus(r2) _minus(r4) _is __not equal_to(r3)
            __and(
                    map _is __not _map
                __or(
                    map _is _map))));
    us instantly();

    return 0;
}