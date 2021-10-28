#ifndef __TMP_DEFS_H__
#define __TMP_DEFS_H__

#define display std::cout << std::boolalpha <<
#define newline << std::endl;

#define _is ::is
#define _shall ::shall
#define _that(Logical) ::that<Logical>

#define __not ::_not
#define __and(Logical) ::_and<Logical>
#define __or(Logical) ::_or<Logical>

#define _true ::True
#define _false ::False

#define equal_to(_Num) ::equal_to<_Num>
#define greater_than(_Num) ::greater_than<_Num>
#define less_than(_Num) ::less_than<_Num>
#define greater_equal_than(_Num) ::greater_equal_than<_Num>
#define less_equal_than(_Num) ::less_equal_than<_Num>

#define _plus(_Num) ::plus<_Num>
#define _minus(_Num) ::minus<_Num>
#define _divide(_Num) ::divide<_Num>
#define _multiply(_Num) ::multiply<_Num>

#define evaluate(__) Eval<__>

/* Traits: */
#define _null ::null
#define _rational ::rational
#define _integer ::integer
#define _complex ::complex
#define _boolean ::boolean
#define _pair ::pair
#define _condition ::condition
#define _container ::container
#define _loop ::loop
#define _map ::map
#define _symbol ::symbol
#define _prodedure ::procedure

/* Factories: */
#define make_int(_num) Integer<(_num)>
#define make_rat(_rat) Rational<_rat>
#define make_complex(_rat1, _rat2) Complex<_rat1, _rat2>
#define _over ,
#define _sqrt(_rat) Sqrt<_rat>
#define lambda(...) [=] (__VA_ARGS__)

/* Conditions: */
#define cond(...) Cond<__VA_ARGS__>
#define _case(Pred_Conseq) Case<Pred_Conseq>
#define _else(Conseq) Else<Conseq>
#define _then ,

/* Do... if */
#define _Do(Procedure) Do<Procedure>
#define _If(Logical) ::If<Logical>
#define instantly(...) ::execute(__VA_ARGS__)

#endif