/**
 *	@file	unit_test_type_traits_is_nothrow_invocable_r.cpp
 *
 *	@brief	is_nothrow_invocable_r のテスト
 */

#include <hamon/type_traits/is_nothrow_invocable_r.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_NOTHROW_INVOCABLE_R_TEST(b, ...)	\
	static_assert(hamon::is_nothrow_invocable_r_v<__VA_ARGS__>      == b, "");	\
	static_assert(hamon::is_nothrow_invocable_r<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_nothrow_invocable_r<__VA_ARGS__>()      == b, "")

#else

#define HAMON_IS_NOTHROW_INVOCABLE_R_TEST(b, ...)	\
	static_assert(hamon::is_nothrow_invocable_r<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_nothrow_invocable_r<__VA_ARGS__>()      == b, "")

#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wundefined-internal")

namespace hamon_type_traits_test
{

namespace is_nothrow_invocable_r_test
{

using func_type_v0 = void(*)();

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void,  func_type_v0);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void,  func_type_v0);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void*, func_type_v0);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int,   func_type_v0);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void,  func_type_v0, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void*, func_type_v0, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int,   func_type_v0, int);

#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using func_type_v0_nt = void(*)() noexcept;

HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void,  func_type_v0_nt);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void*, func_type_v0_nt);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int,   func_type_v0_nt);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void,  func_type_v0_nt, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void*, func_type_v0_nt, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int,   func_type_v0_nt, int);

#endif

struct X {};
using mem_type = int X::*;

HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int,  mem_type, X&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, mem_type, X&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, mem_type, X&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, mem_type, X*);

using memfun_type = int (X::*)();

HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, int&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X*);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, memfun_type, X&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, memfun_type, X*);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X*, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X&, int, char);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type, X*, int, char);

#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using memfun_type_nt = int (X::*)() noexcept;

HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, int&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, memfun_type_nt, X&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, memfun_type_nt, X*);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, X&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, X*, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, X&, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, memfun_type_nt, X*, int, int);

#endif

struct F
{
	int&   operator()();
	long&  operator()() const HAMON_NOEXCEPT;
	short& operator()(int);
	char&  operator()(int) volatile HAMON_NOEXCEPT;
};

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               );
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, F               );
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long&, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               );
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               );
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               );
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               );
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               );
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               );
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               );
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               );
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               );
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               );
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F const         );
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile);

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               &);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, F               &);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long&, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               &);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               &);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               &);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               &);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               &);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               &);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               &);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               &);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               &);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               &);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F const         &);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile&);

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               &&);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int&, F               &&);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long&, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile&&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               &&);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               &&);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile&&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               &&);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               &&);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile&&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               &&);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               &&);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile&&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               &&);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               &&);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile&&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               &&);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               &&);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile&&);

HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               &, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short&, F               &, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char&, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               &, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               &, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               &, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               &, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               &, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               &, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               &, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               &, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               &, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               &, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile&, int);

HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F               &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F               &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile&&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F               &&, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short&, F               &&, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F               &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char&, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile&&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F               &&, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F               &&, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  void, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile&&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F               &&, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F               &&, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  int, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile&&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F               &&, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F               &&, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  long, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile&&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F               &&, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F               &&, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  short, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile&&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F               &&, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F               &&, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const         &&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(true,  char, F       volatile&&, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile&&, int);

HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int&, F const volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long&, F const volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short&, F const volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char&, F const volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, void, F const volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, int, F const volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, long, F const volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, short, F const volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_R_TEST(false, char, F const volatile, int, int);

}	// namespace is_nothrow_invocable_r_test

}	// namespace hamon_type_traits_test

HAMON_WARNING_POP()

#undef HAMON_IS_NOTHROW_INVOCABLE_R_TEST
