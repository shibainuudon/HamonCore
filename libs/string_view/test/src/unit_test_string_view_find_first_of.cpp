/**
 *	@file	unit_test_string_view_find_first_of.cpp
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

TYPED_TEST(StringViewTest, FindFirstOfTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;

	HAMON_CXX11_CONSTEXPR auto const npos = string_view::npos;

	HAMON_CXX11_CONSTEXPR string_view const sv1{Helper::with_nulls(), 28};	// "This contains \0 a zero byte."
	HAMON_CXX11_CONSTEXPR string_view const sv2{Helper::abcd(), 1};	// "a"
	HAMON_CXX11_CONSTEXPR string_view const sv3{Helper::abcd(), 2};	// "ab"
	HAMON_CXX11_CONSTEXPR string_view const sv4{Helper::abcd(), 3};	// "abc"
	HAMON_CXX11_CONSTEXPR string_view const sv5{Helper::abcd(), 0};	// ""

	// (1)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_first_of(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(sv5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv2, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv3, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_first_of(sv4, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(sv5, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv2, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv3, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_first_of(sv4, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(sv5, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv2, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv3, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(sv4, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(sv5, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(sv2, 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(sv3, 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(sv4, 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(sv5, 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(sv2, 17));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 23u == sv1.find_first_of(sv3, 17));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 23u == sv1.find_first_of(sv4, 17));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(sv5, 17));

	// (2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd()[0]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 23u == sv1.find_first_of(Helper::abcd()[1]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_first_of(Helper::abcd()[2]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd()[3]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd()[0], 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 23u == sv1.find_first_of(Helper::abcd()[1], 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_first_of(Helper::abcd()[2], 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd()[3], 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd()[0], 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 23u == sv1.find_first_of(Helper::abcd()[1], 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd()[2], 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd()[3], 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(Helper::abcd()[0], 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 23u == sv1.find_first_of(Helper::abcd()[1], 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd()[2], 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd()[3], 10));

	// (3)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd(),  0, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  0, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  0, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_first_of(Helper::abcd(),  0, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd(),  5, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  5, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  5, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_first_of(Helper::abcd(),  5, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd(),  6, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  6, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  6, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  6, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd(),  9, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  9, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  9, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::abcd(),  9, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::abcd(), 10, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(Helper::abcd(), 10, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(Helper::abcd(), 10, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(Helper::abcd(), 10, 3));

	// (4)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_first_of(Helper::abcd()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::ab()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::ab(),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  9u == sv1.find_first_of(Helper::ab(),  9));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(Helper::ab(), 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 16u == sv1.find_first_of(Helper::ab(), 16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 23u == sv1.find_first_of(Helper::ab(), 17));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( 23u == sv1.find_first_of(Helper::ab(), 23));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_first_of(Helper::ab(), 24));
}

}	// namespace string_view_test
}	// namespace hamon_test
