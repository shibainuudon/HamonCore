/**
 *	@file	unit_test_optional_ctor_optional_move.cpp
 *
 *	@brief	optional<U>&& を引数に取るコンストラクタのテスト
 *
 *	template<class U>
 *	constexpr explicit(see below) optional(optional<U>&& rhs);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace ctor_optional_move_test
{

struct Explicit
{
	Explicit(int&) = delete;
	explicit HAMON_CXX11_CONSTEXPR Explicit(int&& x) : n(x) {}
	Explicit(int const&) = delete;
	Explicit(int const&&) = delete;
	int n;
};

struct Implicit
{
	Implicit(int&) = delete;
	HAMON_CXX11_CONSTEXPR Implicit(int&& x) : n(x) {}
	Implicit(int const&) = delete;
	Implicit(int const&&) = delete;
	int n;
};

struct NoThrow
{
	NoThrow(int&) = delete;
	HAMON_CXX11_CONSTEXPR NoThrow(int&& x) noexcept : n(x) {}
	NoThrow(int const&) = delete;
	NoThrow(int const&&) = delete;
	int n;
};

static_assert(!hamon::is_constructible<hamon::optional<Explicit>, hamon::optional<int> &>::value, "");
static_assert( hamon::is_constructible<hamon::optional<Explicit>, hamon::optional<int> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<Explicit>, hamon::optional<int> const &>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<Explicit>, hamon::optional<int> const &&>::value, "");

static_assert( hamon::is_constructible<hamon::optional<int>,      hamon::optional<int> &&>::value, "");
static_assert( hamon::is_constructible<hamon::optional<Explicit>, hamon::optional<int> &&>::value, "");
static_assert( hamon::is_constructible<hamon::optional<Implicit>, hamon::optional<int> &&>::value, "");
static_assert( hamon::is_constructible<hamon::optional<NoThrow>,  hamon::optional<int> &&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::optional<int>,      hamon::optional<int> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::optional<Explicit>, hamon::optional<int> &&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::optional<Implicit>, hamon::optional<int> &&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::optional<NoThrow>,  hamon::optional<int> &&>::value, "");

#if !defined(HAMON_USE_STD_OPTIONAL)
static_assert( hamon::is_nothrow_constructible<hamon::optional<int>,      hamon::optional<int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::optional<Explicit>, hamon::optional<int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::optional<Implicit>, hamon::optional<int> &&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::optional<NoThrow>,  hamon::optional<int> &&>::value, "");
#endif

GTEST_TEST(OptionalTest, CtorOptionalMoveTest)
{
	{
		hamon::optional<int> o1 {42};
		hamon::optional<Explicit> o2 {hamon::move(o1)};
		EXPECT_TRUE(o2.has_value());
		EXPECT_TRUE(o2->n == 42);
	}
	{
		hamon::optional<int> o1 {42};
		hamon::optional<Implicit> o2 {hamon::move(o1)};
		EXPECT_TRUE(o2.has_value());
		EXPECT_TRUE(o2->n == 42);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::optional<short> o1{(short)13};
		HAMON_CXX14_CONSTEXPR hamon::optional<int> o2 {hamon::move(o1)};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(o2.has_value());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*o2 == 13);
	}
}

}	// namespace ctor_optional_move_test

}	// namespace hamon_optional_test
