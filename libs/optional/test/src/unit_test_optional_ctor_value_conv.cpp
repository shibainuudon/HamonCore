/**
 *	@file	unit_test_optional_ctor_value_conv.cpp
 *
 *	@brief	U&& を引数に取るコンストラクタのテスト
 *
 *	template<class U = T> constexpr explicit(see below) optional(U&& v);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace ctor_value_conv_test
{

struct Explicit
{
	explicit HAMON_CXX11_CONSTEXPR Explicit(int x) : n(x) {}
	int n;
};

struct Implicit
{
	HAMON_CXX11_CONSTEXPR Implicit(int x) : n(x) {}
	int n;
};

struct NoThrow
{
	HAMON_CXX11_CONSTEXPR NoThrow(int x) noexcept : n(x) {}
	int n;
};

struct NoCtor
{
	HAMON_CXX11_CONSTEXPR NoCtor(int x) = delete;
	int n;
};

static_assert( hamon::is_constructible<hamon::optional<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::optional<int>, int&>::value, "");
static_assert( hamon::is_constructible<hamon::optional<int>, int&&>::value, "");
static_assert( hamon::is_constructible<hamon::optional<int>, int const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<int>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::optional<Explicit>, int>::value, "");
static_assert( hamon::is_constructible<hamon::optional<Implicit>, int>::value, "");
static_assert( hamon::is_constructible<hamon::optional<NoThrow>,  int>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<NoCtor>,   int>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::optional<int>, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::optional<Implicit>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::optional<Explicit>, int>::value, "");

#if !defined(HAMON_USE_STD_OPTIONAL)
static_assert( hamon::is_nothrow_constructible<hamon::optional<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::optional<NoThrow>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::optional<Implicit>, int>::value, "");
#endif

GTEST_TEST(OptionalTest, CtorValueConvTest)
{
	{
		hamon::optional<Explicit> o {42};
		EXPECT_TRUE(o.has_value());
		EXPECT_TRUE(o->n == 42);
	}
	{
		hamon::optional<Implicit> o {42};
		EXPECT_TRUE(o.has_value());
		EXPECT_TRUE(o->n == 42);
	}
	{
		HAMON_CXX11_CONSTEXPR short s = 13;
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o {s};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o.has_value());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*o == 13);
	}
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::optional o = 3;
		static_assert(hamon::is_same<decltype(o), hamon::optional<int>>::value, "");
		EXPECT_TRUE(*o == 3);
	}
#endif
}

}	// namespace ctor_value_conv_test

}	// namespace hamon_optional_test
