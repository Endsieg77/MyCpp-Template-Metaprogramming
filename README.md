# MyCpp-Template-Metaprogramming

My Library for simple CTMP

Before we start, make sure your `C++` standard is over ISO-C++17.

## Start

```cpp
#include "tmp.h"
```

to get started.

## Use typedef as variable definitions

Like this:

```cpp
using r0 = TMP::Rational<0>;
using r1 = TMP::Rational<4, 6>; // it would be reduced at compile time
using r2 = TMP::Rational<11, 4>;
using r3 = TMP::Rational<15, 2>;
using r4 = TMP::Rational<1>;
```

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
using _if = TMP::If<Greater<r1, r2>, r1, r2>;
cout << _if::value << endl;
using _res =
Cond<
    Case<And<Less<r2, r1>, Less<r4, r1>>, r1>,
    Case<Or<Less<r3, r2>, Not<LessEqual<r4, r0>>>, r2>,
    Case<Greater<r0, r4>, r4>,
    Else<r3>>;
cout << _res::value << endl;
```

