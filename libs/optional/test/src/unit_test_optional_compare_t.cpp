/**
 *	@file	unit_test_optional_compare_t.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T, class U> constexpr bool operator==(const optional<T>& x, const U& v);
 *	template<class T, class U> constexpr bool operator==(const T& v, const optional<U>& x);
 *	template<class T, class U> constexpr bool operator!=(const optional<T>& x, const U& v);
 *	template<class T, class U> constexpr bool operator!=(const T& v, const optional<U>& x);
 *	template<class T, class U> constexpr bool operator<(const optional<T>& x, const U& v);
 *	template<class T, class U> constexpr bool operator<(const T& v, const optional<U>& x);
 *	template<class T, class U> constexpr bool operator>(const optional<T>& x, const U& v);
 *	template<class T, class U> constexpr bool operator>(const T& v, const optional<U>& x);
 *	template<class T, class U> constexpr bool operator<=(const optional<T>& x, const U& v);
 *	template<class T, class U> constexpr bool operator<=(const T& v, const optional<U>& x);
 *	template<class T, class U> constexpr bool operator>=(const optional<T>& x, const U& v);
 *	template<class T, class U> constexpr bool operator>=(const T& v, const optional<U>& x);
 *	template<class T, class U>
 *	requires (!is-derived-from-optional<U>) && three_way_comparable_with<T, U>
 *	constexpr compare_three_way_result_t<T, U>
 *	operator<=>(const optional<T>& x, const U& v);
 */

#include <hamon/optional.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace compare_t_test
{

GTEST_TEST(OptionalTest, CompareTTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o;
		HAMON_CXX11_CONSTEXPR long x = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o == x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o != x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o <  x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o >  x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o <= x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o >= x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x == o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x != o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x <  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x >  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x <= o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x >= o);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = 42;
		HAMON_CXX11_CONSTEXPR long x = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o == x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o != x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o <  x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o >  x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o <= x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o >= x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x == o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x != o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x <  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x >  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x <= o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x >= o);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = 41;
		HAMON_CXX11_CONSTEXPR long x = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o == x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o != x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o <  x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o >  x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o <= x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o >= x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x == o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x != o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x <  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x >  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x <= o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x >= o);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = 41;
		HAMON_CXX11_CONSTEXPR long x = 40;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o == x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o != x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o <  x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o >  x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o <= x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o >= x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x == o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x != o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x <  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x >  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (x <= o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x >= o);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o;
		HAMON_CXX11_CONSTEXPR long x = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_neq(o <=> x));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_neq(x <=> o));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = 42;
		HAMON_CXX11_CONSTEXPR long x = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(o <=> x));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(x <=> o));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = 41;
		HAMON_CXX11_CONSTEXPR long x = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(o <=> x));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(x <=> o));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = 41;
		HAMON_CXX11_CONSTEXPR long x = 40;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(o <=> x));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(x <=> o));
	}
#endif
}

}	// namespace compare_t_test

}	// namespace hamon_optional_test
