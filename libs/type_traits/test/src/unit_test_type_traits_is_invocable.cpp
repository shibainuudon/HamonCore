/**
 *	@file	unit_test_type_traits_is_invocable.cpp
 *
 *	@brief	is_invocable のテスト
 */

#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_INVOCABLE_TEST(b, ...)	\
	static_assert(hamon::is_invocable_v<__VA_ARGS__>      == b, "");	\
	static_assert(hamon::is_invocable<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_invocable<__VA_ARGS__>()      == b, "")

#else

#define HAMON_IS_INVOCABLE_TEST(b, ...)	\
	static_assert(hamon::is_invocable<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_invocable<__VA_ARGS__>()      == b, "")

#endif

namespace hamon_type_traits_test
{

namespace is_invocable_test
{

using func_type_v0 = void(*)();

HAMON_IS_INVOCABLE_TEST(true,  func_type_v0);
HAMON_IS_INVOCABLE_TEST(false, func_type_v0, int);

using func_type_i0 = int(*)();

HAMON_IS_INVOCABLE_TEST(true,  func_type_i0);
HAMON_IS_INVOCABLE_TEST(false, func_type_i0, int);

using func_type_l0 = int&(*)();

HAMON_IS_INVOCABLE_TEST(true,  func_type_l0);
HAMON_IS_INVOCABLE_TEST(false, func_type_l0, int);

using func_type_ii = int(*)(int);

HAMON_IS_INVOCABLE_TEST(false, func_type_ii);
HAMON_IS_INVOCABLE_TEST(true,  func_type_ii, int);

using func_type_il = int(*)(int&);

HAMON_IS_INVOCABLE_TEST(false, func_type_il);
HAMON_IS_INVOCABLE_TEST(false, func_type_il, int);
HAMON_IS_INVOCABLE_TEST(true,  func_type_il, int&);

using func_type_ir = int(*)(int&&);

HAMON_IS_INVOCABLE_TEST(false, func_type_ir);
HAMON_IS_INVOCABLE_TEST(true,  func_type_ir, int);
HAMON_IS_INVOCABLE_TEST(false, func_type_ir, int&);

struct X {};
struct Y : X {};

using mem_type_i = int X::*;

HAMON_IS_INVOCABLE_TEST(false, mem_type_i);
HAMON_IS_INVOCABLE_TEST(false, mem_type_i, int);
HAMON_IS_INVOCABLE_TEST(false, mem_type_i, int*);
HAMON_IS_INVOCABLE_TEST(false, mem_type_i, int&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_i, int*&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_i, int&&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_i, int*&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X               );
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const         );
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X               *);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const         *);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile*);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile*);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X               &);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const         &);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X               *&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const         *&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile*&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile*&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X               &&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const         &&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X               *&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const         *&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X       volatile*&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, X const volatile*&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y               );
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         );
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y               *);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         *);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile*);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile*);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y               &);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         &);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y               *&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         *&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile*&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile*&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y               &&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         &&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y               *&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const         *&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y       volatile*&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_i, Y const volatile*&&);

using mem_type_f = float Y::*;

HAMON_IS_INVOCABLE_TEST(false, mem_type_f);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, float);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, float*);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, float&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, float*&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, float&&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, float*&&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X               );
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const         );
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X               *);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const         *);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile*);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile*);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X               &);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const         &);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X               *&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const         *&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile*&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile*&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X               &&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const         &&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile&&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile&&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X               *&&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const         *&&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X       volatile*&&);
HAMON_IS_INVOCABLE_TEST(false, mem_type_f, X const volatile*&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y               );
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         );
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y               *);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         *);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile*);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile*);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y               &);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         &);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y               *&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         *&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile*&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile*&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y               &&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         &&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y               *&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const         *&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y       volatile*&&);
HAMON_IS_INVOCABLE_TEST(true,  mem_type_f, Y const volatile*&&);

using memfun_type_i = int (X::*)();

HAMON_IS_INVOCABLE_TEST(false, memfun_type_i);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, int&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X* const         );
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X*       volatile);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X* const volatile);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X*&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X&&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i,                X*&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X*&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X*&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X*&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,                X,  int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X,  int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X,  int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X,  int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,                X&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,                X*, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const          X*, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i,       volatile X*, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_i, const volatile X*, int);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i, Y);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i, Y*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i, Y&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i, Y*&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i, Y&&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_i, Y*&&);

using memfun_type_f = float (Y::*)();

HAMON_IS_INVOCABLE_TEST(true,  memfun_type_f, Y);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_f, Y*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_f, Y&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_f, Y*&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_f, Y&&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_f, Y*&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_f, X);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_f, X*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_f, X&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_f, X*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_f, X&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_f, X*&&);

using memfun_type_iic = int (X::*)(int&) const;

HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, int&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, int*&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, X               , int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               , int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, X const         , int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         , int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, X               *, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               *, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, X const         *, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         *, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile*, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile*, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, X               &, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, X const         &, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, X               &&, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X               &&, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int*);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, X const         &&, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const         &&, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X       volatile&&, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int*);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int               &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int const         &);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int       volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int const volatile&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int*&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X const volatile&&, int&&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X, float&);
HAMON_IS_INVOCABLE_TEST(false, memfun_type_iic, X, int&, int);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, Y, int&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, Y*, int&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, Y&, int&);
HAMON_IS_INVOCABLE_TEST(true,  memfun_type_iic, Y&&, int&);

struct F
{
	int operator()();
	int operator()(int);
	int operator()(float);
private:
	void operator()(int, int);
};

HAMON_IS_INVOCABLE_TEST(true,  F);
HAMON_IS_INVOCABLE_TEST(true,  F, int);
HAMON_IS_INVOCABLE_TEST(true,  F, float);
HAMON_IS_INVOCABLE_TEST(false, F, int, int);

}	// namespace is_invocable_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_INVOCABLE_TEST
