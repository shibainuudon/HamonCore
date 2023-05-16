/**
 *	@file	unit_test_optional_or_else.cpp
 *
 *	@brief	or_else関数のテスト
 *
 *	template<class F> constexpr optional or_else(F&& f) const &;
 *	template<class F> constexpr optional or_else(F&& f) &&;
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace or_else_test
{

HAMON_CXX11_CONSTEXPR hamon::optional<int> default_value()
{
	return 42;
}

GTEST_TEST(OptionalTest, OrElseTest)
{
	{
		hamon::optional<int> o = 1;
		EXPECT_TRUE(o.or_else(default_value).value() == 1);
		EXPECT_TRUE(hamon::move(o).or_else(default_value).value() == 1);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o1 = 1;
		HAMON_CXX11_CONSTEXPR auto o2 = o1.or_else(default_value);
		HAMON_CXX11_CONSTEXPR auto o3 = hamon::move(o1).or_else(default_value);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o2.value() == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o3.value() == 1);
	}
	{
		hamon::optional<int> o = hamon::nullopt;
		EXPECT_TRUE(o.or_else(default_value).value() == 42);
		EXPECT_TRUE(hamon::move(o).or_else(default_value).value() == 42);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::optional<int> o1 = hamon::nullopt;
		HAMON_CXX14_CONSTEXPR auto o2 = o1.or_else(default_value);
		HAMON_CXX14_CONSTEXPR auto o3 = hamon::move(o1).or_else(default_value);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(o2.value() == 42);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(o3.value() == 42);
	}
}

}	// namespace or_else_test

}	// namespace hamon_optional_test
