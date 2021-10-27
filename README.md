# MyCpp-Template-Metaprogramming
My Library for simple CTMP

Before we start, make sure your C++ Standard is over C++20.

## Start

```cpp
#include "tmp.h"
```
to get started.

And
```cpp
using namespace siebenzevan;
```

to make TMP more convenient for you.

## Use `typedef`s as variable definitions

Like this:

```cpp
using r0   = Rational<0>;
using r1   = Rational<4, 6>; // it would be reduced at compile time
using r2   = Rational<11, 4>;
using r3   = Rational<15, 2>;
using r4   = Rational<1>;
using symb = symbol("Hello, world"); // symb is a symbol.
```

or with macro `let`
```cpp
let symb = symbol("You really born singer.");
```

## `Traits`

We add to tags to template by macro `__TAGS__(...)`.
`__TAGS__(Tags::rational, Tags::integer)` will endow
the template with traits `IsRational` & `IsInteger`.
Careful that `__TAGS__(...)` will overwrite each other,
and the final result depends on the last `__TAGS__(...)`
in the inheritance hierarchy.

## `RangeSum`

Given an unary lambda function *f* , `RangeSum_v<from, to, step, f> `applies *f* to all *x* in `range(from, to, step)` and calculates the sum of *f*(*x*).

*f* has a preset value similar to the Id(*x*). If we would like to customize our *f*, we must assign a value for *step*.

```cpp
cout << RangeSum_v<114, 514, 19, [](int &&_19810)
        {
            return _19810 * _19810 * _19810;
        }> << endl;
cout << RangeSum_v<114, 514> << endl;
```

## Compile-time Square Root

Sounds really cooool? Yes. I take pride in this, too.

In fact, the *SICP* inspires me a lot in writing this feature.

An example:

```cpp
cout << Sqrt<Rational<1191ll, 443ll>>::value << endl;
```

Take care. Number **too great** may cause an **integer overflow**.

We can also assign a precision in the second parameter of Sqrt.

```cpp
Sqrt<Rational<1191ll, 443ll>, 0xffff>::value
```

Which means the error would fall on the O(*answer*, 1/0xffff).

## Basic Arithmetic Operations

`Plus<_Lhs, _Rhs>`, `Minus<_Lhs, _Rhs>`, `Multiply<_Lhs, _Rhs>`, `Divide<_Lhs, _Rhs>`

They receive Rational as their parameters.

## Condition Statement `If` and `Cond`

`If` statement receive 3 params. The first yields a boolean value. If the `first::value` is true, then `If::type` is defined the second, else the third.

Ideally, `Cond` statement should receive several `Case`s and at most one `Else` at last. But in C++ this was not easy to simulate. (In lieu of this, all the `Case`s and `Else`s after the first `Else` would be short-circuited. Though they're recursively deduced in fact at compile-time.)

Here are some examples:

```cpp
using _if = If<Greater<r1, r2>, r1, r2>;
cout << _if::value << endl;
using _res =
Cond<
    Case<And<Less<r2, r1>, Less<r4, r1>>, r1>,
    Case<Or<Less<r3, r2>, Not<LessEqual<r4, r0>>>, r2>,
    Case<Greater<r0, r4>, r4>,
    Else<r3>>;
cout << _res::value << endl;
```

## Complex Numbers

```cpp
using c1 = Complex<Rational<3, 4>, Rational<1>>;
using c2 = Complex<Rational<3, 4>, Rational<-1>>;
using c3 = Complex<Rational<19, 7>, Rational<-3, 11>>;
```

They have their own `Plus`, `Minus`, `Multiply`, `Divide` implementation.

## Data Structure `Map`

We define `Map` like this:

```cpp
    using map =
    Map<
        cons<c2, r1>,
        cons<c1, r3>,
        cons<c3, r2>,
        cons<Plus<c1, c3>, r4>>;
```

And we can get to know the data stored in one map by
`ReadMap<[Map Name]>([Output Device(std::ostream &)])`

e.g.

```cpp
ReadMap<map>(std::cout);
```

## `metaprint` is now supported

We can now print Object's information like this,
```cpp
metaprint<r2>(cout) << endl;
metaprint<i1>(cout) << endl;
metaprint<c3>(cout) << endl;
metaprint<cons<r1, c3>>(cout) << endl;
metaprint<symb>(cout) << endl;
```
which I call `metaprint`. This name really cooool, right?

Nesting `cons` will now result in problems.
Why? I may never know looool.

## Call members like chain.

Using `Prototype` technique, this new feature is enabled now.

```cpp
cout << Eval<map::is::map> << endl;
cout << Eval<r1::is::map> << endl;
cout << Eval<r1::is::rational> << endl;
cout << Eval<r1::is::_not::rational> << endl;
```

## Clause

```cpp
cout << Eval<It::is::False::that<
                r1::plus<r2>::is::_not::equal_to<r3>
            ::_and<
                map::is::_not::map::_or<map::is::map>>>> << endl;
```

## Do... if

Template `Do<[LambdaExpr]>::If<[Logical]>`. Only available after C++17.

Lambda can have some parameters, and it may not be called instantly.

If `Eval<[Logical]>` is `true`, we can call the Lambda by static member

`Do<[LambdaExpr]>::If<[Logical]>::execute(params...)`.

And if false, the execute would be a void function that receives indefinite

number of parameters and do nothing at all.

```cpp
auto SomePrint = [] () { metaprint<symbol("Wsgjb")>(cout) << endl; };
Do<SomePrint>
    ::If<It::is::False::that<
            r1::plus<r2>::minus<r4>::is::_not::equal_to<r3>
        ::_and<
                map::is::_not::map
            ::_or<
                map::is::map>>>>
    ::execute();
```

### Speak English in `siebenzevan`

```cpp
auto SomePrint = lambda() { metaprint<symbol("Wsgjb")>(cout) << endl; }

let to_do =
  _Do(SomePrint)
      _If(It _is _false _that(
              r1 _plus(r2) _minus(r4) _is __not equal_to(r3)
          __and(
                  map _is __not _map
              __or(
                  map _is _map))));
to_do instantly();

let _res =
  cond(
      _case(r2 _is less_than(r1) __and(r4 _is less_than(r1))
                _then r1),
      _case(r3 _is less_equal_than(r1)
                _then r2),
      _case(r0 _is greater_than(r1)
                _then r4),
      _else(r3));

let c3   = _make_complex(_make_rat(19 _over 7), _make_rat(-3 _over 11));
```
