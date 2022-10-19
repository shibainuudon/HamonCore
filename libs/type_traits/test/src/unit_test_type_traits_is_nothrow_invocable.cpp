/**
 *	@file	unit_test_type_traits_is_nothrow_invocable.cpp
 *
 *	@brief	is_nothrow_invocable のテスト
 */

#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_NOTHROW_INVOCABLE_TEST(b, ...)	\
	static_assert(hamon::is_nothrow_invocable_v<__VA_ARGS__>      == b, "");	\
	static_assert(hamon::is_nothrow_invocable<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_nothrow_invocable<__VA_ARGS__>()      == b, "")

#else

#define HAMON_IS_NOTHROW_INVOCABLE_TEST(b, ...)	\
	static_assert(hamon::is_nothrow_invocable<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_nothrow_invocable<__VA_ARGS__>()      == b, "")

#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wundefined-internal")

namespace hamon_type_traits_test
{

namespace is_nothrow_invocable_test
{

using func_type_v0 = void(*)();

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_v0);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_v0);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_v0, int);

using func_type_i0 = int(*)();

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_i0);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_i0);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_i0, int);

using func_type_l0 = int&(*)();

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_l0);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_l0);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_l0, int);

using func_type_ii = int(*)(int);

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ii);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ii, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_ii, int);
#endif

using func_type_il = int(*)(int&);

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il, int&);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_il, int&);
#endif

using func_type_ir = int(*)(int&&);

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_ir, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir, int&);

#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using func_type_v0_nt = void(*)() noexcept;

HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_v0_nt);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_v0_nt, int);

using func_type_i0_nt = int(*)() noexcept;

HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_i0_nt);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_i0_nt, int);

using func_type_l0_nt = int&(*)() noexcept;

HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_l0_nt);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_l0_nt, int);

using func_type_ii_nt = int(*)(int) noexcept;

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ii_nt);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_ii_nt, int);

using func_type_il_nt = int(*)(int&) noexcept;

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il_nt);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_il_nt, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_il_nt, int&);

using func_type_ir_nt = int(*)(int&&) noexcept;

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir_nt);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  func_type_ir_nt, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, func_type_ir_nt, int&);

#endif

struct X {};
using mem_type = int X::*;

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, mem_type);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, mem_type, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, mem_type, int&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  mem_type, X&);

using memfun_type = int (X::*)();

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, int&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, X&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, X*);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  memfun_type, X&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  memfun_type, X*);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, X&, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type, X*, int);

#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

using memfun_type_nt = int (X::*)() noexcept;

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt, int&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  memfun_type_nt, X&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  memfun_type_nt, X*);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt, X&, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, memfun_type_nt, X*, int);

#endif

struct F
{
	int&    operator()();
	long&   operator()() const HAMON_NOEXCEPT;
	short&  operator()(int);
	char&   operator()(int) volatile HAMON_NOEXCEPT;
	float&  operator()(int, int) HAMON_NOEXCEPT;
	double& operator()(int, int) const volatile;
};

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F               );
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F               );
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F const         );
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F               &);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F               &);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F const         &);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile&);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F               &&);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F               &&);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F const         &&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile&&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F               *);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const         *);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile*);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile*);

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F       volatile, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F               &, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F               &, int);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const         &, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F       volatile&, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile&, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F, int&);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F, int&);
#endif
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const, int&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F       volatile, int&);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile, int&);

HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F, int, int);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile, int, int);
#else
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F const, int, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F       volatile, int, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(true,  F const volatile, int, int);
#endif

HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F, int, int, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const, int, int, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F       volatile, int, int, int);
HAMON_IS_NOTHROW_INVOCABLE_TEST(false, F const volatile, int, int, int);

}	// namespace is_nothrow_invocable_test

}	// namespace hamon_type_traits_test

HAMON_WARNING_POP()

#undef HAMON_IS_NOTHROW_INVOCABLE_TEST
