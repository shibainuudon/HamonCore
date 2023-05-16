/**
 *	@file	unit_test_optional_transform.cpp
 *
 *	@brief	transform関数のテスト
 *
 *	template<class F> constexpr auto transform(F&& f) &;
 *	template<class F> constexpr auto transform(F&& f) const &;
 *	template<class F> constexpr auto transform(F&& f) &&;
 *	template<class F> constexpr auto transform(F&& f) const &&;
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace transform_test
{

HAMON_CXX11_CONSTEXPR int twice(int n)
{
	return n * 2;
}

HAMON_CXX11_CONSTEXPR int to_int(float f)
{
	return static_cast<int>(f);
}

struct PerfectForwardTest
{
	HAMON_CXX11_CONSTEXPR int operator()(int&) const
	{
		return 1;
	}

	HAMON_CXX11_CONSTEXPR int operator()(int&&) const
	{
		return 2;
	}

	HAMON_CXX11_CONSTEXPR int operator()(int const&) const
	{
		return 3;
	}

	HAMON_CXX11_CONSTEXPR int operator()(int const&&) const
	{
		return 4;
	}
};

struct S
{
	int value;
	S(int i) : value(i) {}
	~S() {}
};

S to_S(int n)
{
	return S{n};
}

GTEST_TEST(OptionalTest, TransformTest)
{
	{
		hamon::optional<int> o = 2;
		EXPECT_TRUE(o.transform(twice).value() == 4);
		EXPECT_TRUE(hamon::move(o).transform(twice).value() == 4);
	}
	{
		hamon::optional<int> o1 = 3;
		auto o2 = o1.transform(to_S);
		auto o3 = hamon::move(o1).transform(to_S);
		EXPECT_TRUE(o2->value == 3);
		EXPECT_TRUE(o3->value == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o1 = 2;
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o2 = o1.transform(twice);
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o3 = hamon::move(o1).transform(twice);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o2.value() == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o3.value() == 4);
	}

	{
		hamon::optional<int> o = hamon::nullopt;
		EXPECT_TRUE(!o.transform(twice).has_value());
		EXPECT_TRUE(!hamon::move(o).transform(twice).has_value());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = hamon::nullopt;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!o.transform(twice).has_value());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::move(o).transform(twice).has_value());
	}

	{
		hamon::optional<float> o1 = 2.5f;
		hamon::optional<int> o2 = o1.transform(to_int);
		hamon::optional<int> o3 = hamon::move(o1).transform(to_int);
		EXPECT_TRUE(o2.value() == 2);
		EXPECT_TRUE(o3.value() == 2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<float> o1 = 2.5f;
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o2 = o1.transform(to_int);
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o3 = hamon::move(o1).transform(to_int);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o2.value() == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o3.value() == 2);
	}

	{
		hamon::optional<int> o = 42;
		EXPECT_TRUE(o.transform(PerfectForwardTest{}).value() == 1);
		EXPECT_TRUE(hamon::move(o).transform(PerfectForwardTest{}).value() == 2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o1 = 42;
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o2 = o1.transform(PerfectForwardTest{});
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o3 = hamon::move(o1).transform(PerfectForwardTest{});
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o2.value() == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o3.value() == 4);
	}
}

}	// namespace transform_test

}	// namespace hamon_optional_test
