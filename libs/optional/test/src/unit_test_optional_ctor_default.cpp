/**
 *	@file	unit_test_optional_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr optional() noexcept;
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace ctor_default_test
{

struct NoConstexprDefaultCtor
{
	NoConstexprDefaultCtor() {}
};

struct NoDefaultCtor
{
	NoDefaultCtor() = delete;
};

static_assert( hamon::is_default_constructible<int>::value, "");
static_assert( hamon::is_default_constructible<NoConstexprDefaultCtor>::value, "");
static_assert(!hamon::is_default_constructible<NoDefaultCtor>::value, "");

static_assert( hamon::is_default_constructible<hamon::optional<int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::optional<NoConstexprDefaultCtor>>::value, "");
static_assert( hamon::is_default_constructible<hamon::optional<NoDefaultCtor>>::value, "");

static_assert( hamon::is_nothrow_default_constructible<int>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<NoConstexprDefaultCtor>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<NoDefaultCtor>::value, "");

static_assert( hamon::is_nothrow_default_constructible<hamon::optional<int>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::optional<NoConstexprDefaultCtor>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::optional<NoDefaultCtor>>::value, "");

GTEST_TEST(OptionalTest, CtorDefaultTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o.has_value());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o{};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o.has_value());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o.has_value());
	}

	// [optional.ctor]/3
	// For every object type T these constructors are constexpr constructors
	{
#if defined(HAMON_CLANG) ||	\
	(defined(HAMON_GCC_VERSION) && HAMON_GCC_VERSION < 100000)
		hamon::optional<NoConstexprDefaultCtor> o;
		EXPECT_FALSE(o.has_value());
#else
		HAMON_CXX20_CONSTEXPR hamon::optional<NoConstexprDefaultCtor> o;
		HAMON_CXX20_CONSTEXPR_EXPECT_FALSE(o.has_value());
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<NoDefaultCtor> o;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o.has_value());
	}
}

}	// namespace ctor_default_test

}	// namespace hamon_optional_test
