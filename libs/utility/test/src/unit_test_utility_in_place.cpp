/**
 *	@file	unit_test_utility_in_place.cpp
 *
 *	@brief	in_place のテスト
 */

#include <hamon/utility/in_place.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace in_place_test
{

struct Foo
{
	HAMON_CXX11_CONSTEXPR Foo(int) : m_in_place_initialized(false) {}

	HAMON_CXX11_CONSTEXPR Foo(hamon::in_place_t, int) : m_in_place_initialized(true) {}

	bool m_in_place_initialized;
};

GTEST_TEST(UtilityTest, InPlaceTest)
{
	HAMON_CXX11_CONSTEXPR Foo f1(1);
	HAMON_CXX11_CONSTEXPR Foo f2(hamon::in_place, 1);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(f1.m_in_place_initialized);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (f2.m_in_place_initialized);
}

}	// namespace in_place_test

}	// namespace hamon_utility_test
