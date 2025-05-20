/**
 *	@file	unit_test_expected_void_ctor_in_place.cpp
 *
 *	@brief	in_place_t を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit expected(in_place_t) noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace ctor_in_place_test
{

struct S1
{
};

struct S2
{
	constexpr S2(int) {}
};

static_assert( hamon::is_constructible<hamon::expected<void, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, int>, hamon::in_place_t, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, S1>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, S1>, hamon::in_place_t, int>::value, "");
static_assert( hamon::is_constructible<hamon::expected<void, S2>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_constructible<hamon::expected<void, S2>, hamon::in_place_t, int>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, int>, hamon::in_place_t, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, S1>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S1>, hamon::in_place_t, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::expected<void, S2>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::expected<void, S2>, hamon::in_place_t, int>::value, "");
#endif

static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, int>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, int>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S1>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S1>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S2>, hamon::in_place_t>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::expected<void, S2>, hamon::in_place_t, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, int> x{hamon::in_place};
		VERIFY(x.has_value());
	}
	{
		hamon::expected<Void, S2> x{hamon::in_place};
		VERIFY(x.has_value());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, CtorInPlaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile>()));
}

}	// namespace ctor_in_place_test

}	// namespace hamon_expected_void_test
