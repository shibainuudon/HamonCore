/**
 *	@file	unit_test_expected_void_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	constexpr void emplace() noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace emplace_test
{

template <typename Void, typename T, typename... Args>
struct CanEmplaceImpl
	: hamon::false_type {};

template <typename T, typename... Args>
struct CanEmplaceImpl<
	hamon::void_t<decltype(hamon::declval<T&>().emplace(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using CanEmplace = CanEmplaceImpl<void, T, Args...>;

static_assert( CanEmplace<hamon::expected<void, int>>::value, "");
static_assert(!CanEmplace<hamon::expected<void, int>, int>::value, "");
static_assert(!CanEmplace<hamon::expected<void, int>, int, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	static_assert(noexcept(hamon::declval<hamon::expected<Void, E>&>().emplace()), "");

	{
		hamon::expected<Void, E> e(hamon::in_place);
		static_assert(hamon::is_same<decltype(e.emplace()), void>::value, "");
		VERIFY(e.has_value());
		e.emplace();
		VERIFY(e.has_value());
	}
	{
		hamon::expected<Void, E> e(hamon::unexpect);
		static_assert(hamon::is_same<decltype(e.emplace()), void>::value, "");
		VERIFY(!e.has_value());
		e.emplace();
		VERIFY(e.has_value());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, EmplaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, float>()));
}

}	// namespace hamon_expected_void_test

}	// namespace hamon_expected_test
