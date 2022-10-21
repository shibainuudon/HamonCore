/**
 *	@file	unit_test_functional_modulus.cpp
 *
 *	@brief	modulus のテスト
 */

#include <hamon/functional/modulus.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace modulus_test
{

GTEST_TEST(FunctionalTest, ModulusTest)
{
	{
		using type = hamon::modulus<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, type()(  0,  1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, type()( 42,  5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::modulus<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, type()(9, 4));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, type()(9, 3));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace modulus_test

}	// namespace hamon_functional_test
