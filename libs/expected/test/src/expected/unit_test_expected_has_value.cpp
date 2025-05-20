/**
 *	@file	unit_test_expected_has_value.cpp
 *
 *	@brief	has_value() のテスト
 *
 *	constexpr bool has_value() const noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace has_value_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> const e{T{5}};
		static_assert(hamon::is_same<decltype(e.has_value()), bool>::value, "");
		static_assert(noexcept(e.has_value()), "");
		VERIFY(e.has_value());
	}
	{
		hamon::expected<T, E> const e{hamon::unexpect};
		static_assert(hamon::is_same<decltype(e.has_value()), bool>::value, "");
		static_assert(noexcept(e.has_value()), "");
		VERIFY(!e.has_value());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, HasValueTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace has_value_test

}	// namespace hamon_expected_test
