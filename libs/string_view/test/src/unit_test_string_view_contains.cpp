/**
 *	@file	unit_test_string_view_contains.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

TYPED_TEST(StringViewTest, ContainsTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;

	HAMON_CXX11_CONSTEXPR string_view const sv1{Helper::aababc(), 6};	// "aababc"

	// (1)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( sv1.contains(string_view{Helper::abcd(), 2}));	// "ab"
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( sv1.contains(string_view{Helper::abcd(), 3}));	// "abc"
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv1.contains(string_view{Helper::abcd(), 4}));	// "abcd"
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( sv1.contains(string_view{Helper::aababc()}));	// "aababc"

	// (2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( sv1.contains(Helper::abcd()[0]));	// 'a'
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( sv1.contains(Helper::abcd()[1]));	// 'b'
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( sv1.contains(Helper::abcd()[2]));	// 'c'
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv1.contains(Helper::abcd()[3]));	// 'd'

	// (3)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( sv1.contains(Helper::ab()));		// "ab"
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv1.contains(Helper::cd()));		// "cd"
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv1.contains(Helper::abcd()));		// "abcd"
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( sv1.contains(Helper::aababc()));	// "aababc"
}

}	// namespace string_view_test
}	// namespace hamon_test
