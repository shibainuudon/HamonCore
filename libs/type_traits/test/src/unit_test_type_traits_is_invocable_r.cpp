/**
 *	@file	unit_test_type_traits_is_invocable_r.cpp
 *
 *	@brief	is_invocable_r のテスト
 */

#include <hamon/type_traits/is_invocable_r.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_INVOCABLE_R_TEST(b, ...)	\
	static_assert(hamon::is_invocable_r_v<__VA_ARGS__>      == b, "");	\
	static_assert(hamon::is_invocable_r<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_invocable_r<__VA_ARGS__>()      == b, "")

#else

#define HAMON_IS_INVOCABLE_R_TEST(b, ...)	\
	static_assert(hamon::is_invocable_r<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_invocable_r<__VA_ARGS__>()      == b, "")

#endif

namespace hamon_type_traits_test
{

namespace is_invocable_r_test
{

using func_type_v0 = void(*)();

HAMON_IS_INVOCABLE_R_TEST(true,  void,  func_type_v0);
HAMON_IS_INVOCABLE_R_TEST(false, void*, func_type_v0);
HAMON_IS_INVOCABLE_R_TEST(false, int,   func_type_v0);
HAMON_IS_INVOCABLE_R_TEST(false, void,  func_type_v0, int);
HAMON_IS_INVOCABLE_R_TEST(false, void*, func_type_v0, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,   func_type_v0, int);

using func_type_i0 = int(*)();

HAMON_IS_INVOCABLE_R_TEST(true,  void, func_type_i0);
HAMON_IS_INVOCABLE_R_TEST(true,  int,  func_type_i0);
HAMON_IS_INVOCABLE_R_TEST(false, int&, func_type_i0);
HAMON_IS_INVOCABLE_R_TEST(true,  long, func_type_i0);
HAMON_IS_INVOCABLE_R_TEST(false, void, func_type_i0, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,  func_type_i0, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&, func_type_i0, int);
HAMON_IS_INVOCABLE_R_TEST(false, long, func_type_i0, int);

using func_type_l0 = int&(*)();

HAMON_IS_INVOCABLE_R_TEST(true,  void,  func_type_l0);
HAMON_IS_INVOCABLE_R_TEST(true,  int,   func_type_l0);
HAMON_IS_INVOCABLE_R_TEST(true,  int&,  func_type_l0);
HAMON_IS_INVOCABLE_R_TEST(false, int&&, func_type_l0);
HAMON_IS_INVOCABLE_R_TEST(true,  long,  func_type_l0);
HAMON_IS_INVOCABLE_R_TEST(false, long&, func_type_l0);
HAMON_IS_INVOCABLE_R_TEST(false, void,  func_type_l0, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,   func_type_l0, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,  func_type_l0, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,  func_type_l0, int);

using func_type_ii = int(*)(int);

HAMON_IS_INVOCABLE_R_TEST(false, int,  func_type_ii);
HAMON_IS_INVOCABLE_R_TEST(false, int&, func_type_ii);
HAMON_IS_INVOCABLE_R_TEST(false, long, func_type_ii);
HAMON_IS_INVOCABLE_R_TEST(true,  int,  func_type_ii, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&, func_type_ii, int);
HAMON_IS_INVOCABLE_R_TEST(true,  long, func_type_ii, int);

using func_type_il = int(*)(int&);

HAMON_IS_INVOCABLE_R_TEST(false, int,  func_type_il, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&, func_type_il, int);
HAMON_IS_INVOCABLE_R_TEST(false, long, func_type_il, int);
HAMON_IS_INVOCABLE_R_TEST(true,  int,  func_type_il, int&);
HAMON_IS_INVOCABLE_R_TEST(false, int&, func_type_il, int&);
HAMON_IS_INVOCABLE_R_TEST(true,  long, func_type_il, int&);

using func_type_ir = int(*)(int&&);

HAMON_IS_INVOCABLE_R_TEST(true,  int,  func_type_ir, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&, func_type_ir, int);
HAMON_IS_INVOCABLE_R_TEST(true,  long, func_type_ir, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,  func_type_ir, int&);
HAMON_IS_INVOCABLE_R_TEST(false, int&, func_type_ir, int&);
HAMON_IS_INVOCABLE_R_TEST(false, long, func_type_ir, int&);

struct X {};

using mem_type_i = int X::*;

HAMON_IS_INVOCABLE_R_TEST(false, int,  mem_type_i, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&, mem_type_i, int);
HAMON_IS_INVOCABLE_R_TEST(false, long, mem_type_i, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,  mem_type_i, int&);
HAMON_IS_INVOCABLE_R_TEST(false, int&, mem_type_i, int&);
HAMON_IS_INVOCABLE_R_TEST(false, long, mem_type_i, int&);
HAMON_IS_INVOCABLE_R_TEST(true,  int,  mem_type_i, X&);
HAMON_IS_INVOCABLE_R_TEST(true,  int&, mem_type_i, X&);
HAMON_IS_INVOCABLE_R_TEST(true,  long, mem_type_i, X&);

using memfun_type_i = int (X::*)();

HAMON_IS_INVOCABLE_R_TEST(true,  int,  memfun_type_i, X&);
HAMON_IS_INVOCABLE_R_TEST(false, int&, memfun_type_i, X&);
HAMON_IS_INVOCABLE_R_TEST(true,  long, memfun_type_i, X&);
HAMON_IS_INVOCABLE_R_TEST(false, int,  memfun_type_i, const X&);

using memfun_type_iic = int& (X::*)(int&) const;

HAMON_IS_INVOCABLE_R_TEST(true,  int,   memfun_type_iic, const X&, int&);
HAMON_IS_INVOCABLE_R_TEST(true,  int&,  memfun_type_iic, const X&, int&);
HAMON_IS_INVOCABLE_R_TEST(true,  long,  memfun_type_iic, const X&, int&);
HAMON_IS_INVOCABLE_R_TEST(false, long&, memfun_type_iic, const X&, int&);

struct F
{
	int& operator()();
	long& operator()() const;
	short& operator()(int);
	char& operator()(int) const;
};

HAMON_IS_INVOCABLE_R_TEST(true,  int&,   F               );
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const         );
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const volatile);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F               );
HAMON_IS_INVOCABLE_R_TEST(true,  long&,  F const         );
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const volatile);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F               );
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const         );
HAMON_IS_INVOCABLE_R_TEST(false, short&, F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const volatile);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F               );
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const         );
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const volatile);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F               );
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F const         );
HAMON_IS_INVOCABLE_R_TEST(false, void,   F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F const volatile);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F               );
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F const         );
HAMON_IS_INVOCABLE_R_TEST(false, int,    F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F const volatile);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F               );
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F const         );
HAMON_IS_INVOCABLE_R_TEST(false, long,   F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F const volatile);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F               );
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F const         );
HAMON_IS_INVOCABLE_R_TEST(false, short,  F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F const volatile);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F               );
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F const         );
HAMON_IS_INVOCABLE_R_TEST(false, char,   F       volatile);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F const volatile);

HAMON_IS_INVOCABLE_R_TEST(true,  int&,   F               &);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F               &);
HAMON_IS_INVOCABLE_R_TEST(true,  long&,  F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F               &);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F               &);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const volatile&);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F               &);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F const volatile&);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F               &);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F const volatile&);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F               &);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F const volatile&);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F               &);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F const volatile&);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F               &);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F const         &);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F       volatile&);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F const volatile&);

HAMON_IS_INVOCABLE_R_TEST(true,  int&,   F               &&);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F               &&);
HAMON_IS_INVOCABLE_R_TEST(true,  long&,  F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F               &&);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F               &&);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const volatile&&);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F               &&);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F const volatile&&);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F               &&);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F const volatile&&);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F               &&);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F const volatile&&);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F               &&);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F const volatile&&);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F               &&);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F const         &&);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F       volatile&&);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F const volatile&&);

HAMON_IS_INVOCABLE_R_TEST(false, int&,   F               , int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F               , int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const volatile, int);
HAMON_IS_INVOCABLE_R_TEST(true,  short&, F               , int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F               , int);
HAMON_IS_INVOCABLE_R_TEST(true,  char&,  F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const volatile, int);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F               , int);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F const volatile, int);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F               , int);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F const volatile, int);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F               , int);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F const volatile, int);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F               , int);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F const volatile, int);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F               , int);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F const         , int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F       volatile, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F const volatile, int);

HAMON_IS_INVOCABLE_R_TEST(false, int&,   F               &, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F               &, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  short&, F               &, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F               &, int);
HAMON_IS_INVOCABLE_R_TEST(true,  char&,  F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F               &, int);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F const volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F               &, int);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F const volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F               &, int);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F const volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F               &, int);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F const volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F               &, int);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F const         &, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F       volatile&, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F const volatile&, int);

HAMON_IS_INVOCABLE_R_TEST(false, int&,   F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  short&, F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  char&,  F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  void,   F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F const volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  int,    F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F const volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  long,   F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F const volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  short,  F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F const volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F               &&, int);
HAMON_IS_INVOCABLE_R_TEST(true,  char,   F const         &&, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F       volatile&&, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F const volatile&&, int);

HAMON_IS_INVOCABLE_R_TEST(false, int&,   F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, int&,   F const volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, long&,  F const volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, short&, F const volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, char&,  F const volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, void,   F const volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, int,    F const volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, long,   F const volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, short,  F const volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F               , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F const         , int, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F       volatile, int, int);
HAMON_IS_INVOCABLE_R_TEST(false, char,   F const volatile, int, int);

}	// namespace is_invocable_r_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_INVOCABLE_R_TEST
