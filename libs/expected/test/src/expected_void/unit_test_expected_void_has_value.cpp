/**
 *	@file	unit_test_expected_void_has_value.cpp
 *
 *	@brief	has_value() のテスト
 *
 *	constexpr bool has_value() const noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace has_value_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, E> const e;
		static_assert(hamon::is_same<decltype(e.has_value()), bool>::value, "");
		static_assert(noexcept(e.has_value()), "");
		VERIFY(e.has_value());
	}
	{
		hamon::expected<Void, E> const e{hamon::unexpect};
		static_assert(hamon::is_same<decltype(e.has_value()), bool>::value, "");
		static_assert(noexcept(e.has_value()), "");
		VERIFY(!e.has_value());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, HasValueTest)
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

}	// namespace has_value_test

}	// namespace hamon_expected_void_test
