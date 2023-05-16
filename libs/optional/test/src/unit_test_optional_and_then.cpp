/**
 *	@file	unit_test_optional_and_then.cpp
 *
 *	@brief	and_then関数のテスト
 *
 *	template<class F> constexpr auto and_then(F&& f) &;
 *	template<class F> constexpr auto and_then(F&& f) const &;
 *	template<class F> constexpr auto and_then(F&& f) &&;
 *	template<class F> constexpr auto and_then(F&& f) const &&;
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace and_then_test
{

HAMON_CXX11_CONSTEXPR hamon::optional<int> twice_if_positive(int n)
{
	return (n >= 0) ? hamon::optional<int>(n * 2) : hamon::nullopt;
}

struct PerfectForwardTest
{
	HAMON_CXX11_CONSTEXPR hamon::optional<int> operator()(int&) const
	{
		return 1;
	}

	HAMON_CXX11_CONSTEXPR hamon::optional<int> operator()(int&&) const
	{
		return 2;
	}

	HAMON_CXX11_CONSTEXPR hamon::optional<int> operator()(int const&) const
	{
		return 3;
	}

	HAMON_CXX11_CONSTEXPR hamon::optional<int> operator()(int const&&) const
	{
		return 4;
	}
};

GTEST_TEST(OptionalTest, AndThenTest)
{
	{
		hamon::optional<int> o = 1;
		EXPECT_TRUE(o.and_then(twice_if_positive).value() == 2);
		EXPECT_TRUE(hamon::move(o).and_then(twice_if_positive).value() == 2);
	}
	{
		hamon::optional<int> o = -1;
		EXPECT_TRUE(!o.and_then(twice_if_positive).has_value());
		EXPECT_TRUE(!hamon::move(o).and_then(twice_if_positive).has_value());
	}
	{
		hamon::optional<int> o;
		EXPECT_TRUE(!o.and_then(twice_if_positive).has_value());
		EXPECT_TRUE(!hamon::move(o).and_then(twice_if_positive).has_value());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o1 = 2;
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o2 = o1.and_then(twice_if_positive);
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o3 = hamon::move(o1).and_then(twice_if_positive);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o2.value() == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o3.value() == 4);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = -2;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!o.and_then(twice_if_positive).has_value());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::move(o).and_then(twice_if_positive).has_value());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!o.and_then(twice_if_positive).has_value());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::move(o).and_then(twice_if_positive).has_value());
	}

	{
		hamon::optional<int> o = 42;
		EXPECT_TRUE(o.and_then(PerfectForwardTest{}).value() == 1);
		EXPECT_TRUE(hamon::move(o).and_then(PerfectForwardTest{}).value() == 2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o1 = 42;
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o2 = o1.and_then(PerfectForwardTest{});
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o3 = hamon::move(o1).and_then(PerfectForwardTest{});
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o2.value() == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o3.value() == 4);
	}
}

}	// namespace and_then_test

}	// namespace hamon_optional_test
