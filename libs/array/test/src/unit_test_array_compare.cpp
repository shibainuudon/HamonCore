/**
 *	@file	unit_test_array_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	constexpr bool operator==(array<T, N> const&, array<T, N> const&);
 *	constexpr bool operator!=(array<T, N> const&, array<T, N> const&);
 *	constexpr bool operator< (array<T, N> const&, array<T, N> const&);
 *	constexpr bool operator<=(array<T, N> const&, array<T, N> const&);
 *	constexpr bool operator> (array<T, N> const&, array<T, N> const&);
 *	constexpr bool operator>=(array<T, N> const&, array<T, N> const&);
 *	constexpr .... operator<=>(array<T, N> const&, array<T, N> const&);
 */

#include <hamon/array/array.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace compare_test
{

template <typename T>
void CompareTest()
{
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a1 = { { 1, 2, 3 } };
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a2 = { { 1, 2, 3 } };
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a3 = { { 1, 2, 4 } };
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a4 = { { 1, 2, 0 } };
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a5 = { { 2, 2, 3 } };
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a6 = { { 0, 2, 3 } };

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 == a1) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 == a2) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 == a3) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 == a4) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 == a5) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 == a6) == false);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 != a1) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 != a2) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 != a3) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 != a4) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 != a5) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 != a6) == true);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <  a1) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <  a2) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <  a3) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <  a4) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <  a5) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <  a6) == false);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >  a1) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >  a2) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >  a3) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >  a4) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >  a5) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >  a6) == true);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <= a1) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <= a2) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <= a3) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <= a4) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <= a5) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <= a6) == false);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >= a1) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >= a2) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >= a3) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >= a4) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >= a5) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >= a6) == true);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(a1 <=> a1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(a1 <=> a2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(a1 <=> a3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(a1 <=> a4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(a1 <=> a5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(a1 <=> a6));
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a1 = {};
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a2 = {};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 == a1) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 == a2) == true);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 != a1) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 != a2) == false);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <  a1) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <  a2) == false);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >  a1) == false);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >  a2) == false);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <= a1) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 <= a2) == true);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >= a1) == true);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((a1 >= a2) == true);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(a1 <=> a1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(a1 <=> a2));
#endif
	}
}

GTEST_TEST(ArrayTest, CompareTest)
{
	CompareTest<char>();
	CompareTest<int>();
	CompareTest<float>();
	CompareTest<double>();
}

}	// namespace compare_test

}	// namespace hamon_array_test
