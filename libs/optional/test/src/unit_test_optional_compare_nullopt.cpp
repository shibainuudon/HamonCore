/**
 *	@file	unit_test_optional_compare_nullopt.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T> constexpr bool operator==(const optional<T>& x, nullopt_t) noexcept;
 *
 *	template<class T> constexpr strong_ordering operator<=>(const optional<T>& x, nullopt_t) noexcept;
 */

#include <hamon/optional.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace compare_nullopt_test
{

GTEST_TEST(OptionalTest, CompareNulloptTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o == hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o != hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o <  hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o >  hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o <= hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o >= hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::nullopt == o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::nullopt != o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::nullopt <  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::nullopt >  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::nullopt <= o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::nullopt >= o);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o == hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o != hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o <  hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o >  hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o <= hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o >= hamon::nullopt);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::nullopt == o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::nullopt != o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::nullopt <  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::nullopt >  o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::nullopt <= o);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::nullopt >= o);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(o <=> hamon::nullopt));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(hamon::nullopt <=> o));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = 1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(o <=> hamon::nullopt));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(hamon::nullopt <=> o));
	}
#endif
}

}	// namespace compare_nullopt_test

}	// namespace hamon_optional_test
