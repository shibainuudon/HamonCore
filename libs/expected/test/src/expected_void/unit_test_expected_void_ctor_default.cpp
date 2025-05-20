/**
 *	@file	unit_test_expected_void_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr expected() noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace ctor_default_test
{

struct DefaultConstructible
{
	int value;
	constexpr DefaultConstructible() : value(42) {}
};
static_assert(hamon::is_default_constructible<DefaultConstructible>::value, "");

struct NonDefaultConstructible
{
	int value;
	constexpr NonDefaultConstructible(int v) : value(v) {}
};
static_assert(!hamon::is_default_constructible<NonDefaultConstructible>::value, "");

struct NothrowDefaultConstructible
{
	NothrowDefaultConstructible() noexcept;
};
static_assert(hamon::is_nothrow_default_constructible<NothrowDefaultConstructible>::value, "");

struct TriviallyDefaultConstructible
{
};
static_assert(hamon::is_trivially_default_constructible<TriviallyDefaultConstructible>::value, "");

struct ExplicitlyDefaultConstructible
{
	explicit ExplicitlyDefaultConstructible();
};
static_assert( hamon::is_default_constructible<ExplicitlyDefaultConstructible>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<ExplicitlyDefaultConstructible>::value, "");

static_assert( hamon::is_default_constructible<hamon::expected<void, int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::expected<void, DefaultConstructible>>::value, "");
static_assert( hamon::is_default_constructible<hamon::expected<void, NonDefaultConstructible>>::value, "");
static_assert( hamon::is_default_constructible<hamon::expected<void, NothrowDefaultConstructible>>::value, "");
static_assert( hamon::is_default_constructible<hamon::expected<void, TriviallyDefaultConstructible>>::value, "");
static_assert( hamon::is_default_constructible<hamon::expected<void, ExplicitlyDefaultConstructible>>::value, "");

static_assert( hamon::is_nothrow_default_constructible<hamon::expected<void, int>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::expected<void, DefaultConstructible>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::expected<void, NonDefaultConstructible>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::expected<void, NothrowDefaultConstructible>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::expected<void, TriviallyDefaultConstructible>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::expected<void, ExplicitlyDefaultConstructible>>::value, "");

static_assert(!hamon::is_trivially_default_constructible<hamon::expected<void, int>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<void, DefaultConstructible>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<void, NonDefaultConstructible>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<void, NothrowDefaultConstructible>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<void, TriviallyDefaultConstructible>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::expected<void, ExplicitlyDefaultConstructible>>::value, "");

static_assert( hamon::is_implicitly_default_constructible<hamon::expected<void, int>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<void, DefaultConstructible>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<void, NonDefaultConstructible>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<void, NothrowDefaultConstructible>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<void, TriviallyDefaultConstructible>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::expected<void, ExplicitlyDefaultConstructible>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, int> e;
		VERIFY(e.has_value());
	}
	{
		hamon::expected<Void, NonDefaultConstructible> e;
		VERIFY(e.has_value());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile>()));
}

}	// namespace ctor_default_test

}	// namespace hamon_expected_void_test
