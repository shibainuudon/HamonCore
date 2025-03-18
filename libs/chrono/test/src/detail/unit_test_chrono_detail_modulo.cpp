/**
 *	@file	unit_test_chrono_detail_modulo.cpp
 *
 *	@brief	modulo のテスト
 */

#include <hamon/chrono/detail/modulo.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(DurationTest, ModuloTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo(-9, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo(-8, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo(-7, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo(-6, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo(-5, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo(-4, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo(-3, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo(-2, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo(-1, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo( 0, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo( 1, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo( 2, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo( 3, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo( 4, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo( 5, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo( 6, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo( 7, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo( 8, 3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo(-14, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo(-13, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo(-12, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::chrono::detail::modulo(-11, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::chrono::detail::modulo(-10, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::chrono::detail::modulo( -9, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::chrono::detail::modulo( -8, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo( -7, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo( -6, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo( -5, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::chrono::detail::modulo( -4, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::chrono::detail::modulo( -3, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::chrono::detail::modulo( -2, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::chrono::detail::modulo( -1, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo(  0, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo(  1, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo(  2, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::chrono::detail::modulo(  3, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::chrono::detail::modulo(  4, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::chrono::detail::modulo(  5, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::chrono::detail::modulo(  6, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo(  7, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo(  8, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo(  9, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::chrono::detail::modulo( 10, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::chrono::detail::modulo( 11, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::chrono::detail::modulo( 12, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::chrono::detail::modulo( 13, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::chrono::detail::modulo( 14, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::chrono::detail::modulo( 15, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::chrono::detail::modulo( 16, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::chrono::detail::modulo( 17, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::chrono::detail::modulo( 18, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::chrono::detail::modulo( 19, 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::chrono::detail::modulo( 20, 7));
}
