/**
 *	@file	unit_test_cmath_ranges_abs.cpp
 *
 *	@brief	ranges::abs のテスト
 */

#include <hamon/cmath/ranges/abs.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_abs_test
{

template <typename T>
struct Real
{
	T value;

	HAMON_CXX11_CONSTEXPR bool operator==(Real const& rhs) const
	{
		return value == rhs.value;
	}
};

template <typename T>
HAMON_CXX11_CONSTEXPR Real<T> abs(Real<T> const& r)
{
	return Real<T>{hamon::abs(r.value)};
}

template <typename T>
void RangesAbsTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{2.0}, hamon::ranges::abs(T{-2.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.5}, hamon::ranges::abs(T{-1.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.0}, hamon::ranges::abs(T{-1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.5}, hamon::ranges::abs(T{-0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.0}, hamon::ranges::abs(T{-0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.0}, hamon::ranges::abs(T{ 0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.5}, hamon::ranges::abs(T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.0}, hamon::ranges::abs(T{ 1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.5}, hamon::ranges::abs(T{ 1.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{2.0}, hamon::ranges::abs(T{ 2.0}));
}

GTEST_TEST(CMathTest, RangesAbsTest)
{
	RangesAbsTest<float>();
	RangesAbsTest<double>();
	RangesAbsTest<long double>();

	RangesAbsTest<Real<float>>();
	RangesAbsTest<Real<double>>();
	RangesAbsTest<Real<long double>>();
}

}	// namespace ranges_abs_test

}	// namespace hamon_cmath_test
