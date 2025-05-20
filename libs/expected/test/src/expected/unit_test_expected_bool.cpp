/**
 *	@file	unit_test_expected_bool.cpp
 *
 *	@brief	operator bool() のテスト
 *
 *	constexpr explicit operator bool() const noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace bool_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(!hamon::is_convertible<hamon::expected<T, E>, bool>::value, "");
	{
		hamon::expected<T, E> const e{T{5}};
		static_assert(noexcept(static_cast<bool>(e)), "");
		VERIFY(static_cast<bool>(e));
	}
	{
		hamon::expected<T, E> const e{hamon::unexpect};
		static_assert(noexcept(static_cast<bool>(e)), "");
		VERIFY(!static_cast<bool>(e));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, BoolTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace bool_test

}	// namespace hamon_expected_test
