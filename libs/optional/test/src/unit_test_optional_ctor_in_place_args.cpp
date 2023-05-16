/**
 *	@file	unit_test_optional_ctor_in_place_args.cpp
 *
 *	@brief	in_place_tとArgs...を引数に取るコンストラクタのテスト
 *
 *	template<class... Args> constexpr explicit optional(in_place_t, Args&&... args);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace ctor_in_place_args_test
{

struct S
{
};

struct Noexcept
{
	Noexcept(int) noexcept(true);
};

struct NotNoexcept
{
	NotNoexcept(int) noexcept(false);
};

static_assert( hamon::is_constructible<hamon::optional<int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<int>, hamon::in_place_t, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<S>,   hamon::in_place_t, int>::value, "");
static_assert( hamon::is_constructible<hamon::optional<Noexcept>, hamon::in_place_t, int>::value, "");
static_assert( hamon::is_constructible<hamon::optional<NotNoexcept>, hamon::in_place_t, int>::value, "");

#if !defined(HAMON_USE_STD_OPTIONAL)
static_assert( hamon::is_nothrow_constructible<hamon::optional<int>, hamon::in_place_t, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::optional<Noexcept>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::optional<NotNoexcept>, hamon::in_place_t, int>::value, "");
#endif

GTEST_TEST(OptionalTest, CtorInPlaceArgsTest)
{
	{
		hamon::optional<int> t { hamon::in_place, 42 };
		EXPECT_EQ(42, t.value());
		EXPECT_EQ(42, *t);
	}
	{
		hamon::optional<std::string> t { hamon::in_place, 3u, 'A' };
		EXPECT_EQ("AAA", t.value());
		EXPECT_EQ("AAA", *t);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> t { hamon::in_place, 42 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, t.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, *t);
	}
}

}	// namespace ctor_in_place_args_test

}	// namespace hamon_optional_test
