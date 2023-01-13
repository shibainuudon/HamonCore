/**
 *	@file	unit_test_string_view_find_last_not_of.cpp
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

TYPED_TEST(StringViewTest, FindLastNotOfTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;

	HAMON_CXX11_CONSTEXPR auto const npos = string_view::npos;

	HAMON_CXX11_CONSTEXPR string_view const sv1{Helper::aababc(), 6};	// "aababc"
	HAMON_CXX11_CONSTEXPR string_view const sv2{Helper::abcd(), 1};	// "a"
	HAMON_CXX11_CONSTEXPR string_view const sv3{Helper::abcd(), 2};	// "ab"
	HAMON_CXX11_CONSTEXPR string_view const sv4{Helper::abcd(), 3};	// "abc"
	HAMON_CXX11_CONSTEXPR string_view const sv5{Helper::abcd(), 0};	// ""

	// (1)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv2, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv3, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv4, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find_last_not_of(sv5, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(sv2, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv3, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv4, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(sv5, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(sv2, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv3, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv4, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find_last_not_of(sv5, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(sv2, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv3, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv4, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(sv5, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv2, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv3, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv4, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv5, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv2, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv3, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(sv4, 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(sv5, 6));

	// (2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[0]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[1]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(Helper::abcd()[2]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[3]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd()[0], 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find_last_not_of(Helper::abcd()[1], 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find_last_not_of(Helper::abcd()[2], 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find_last_not_of(Helper::abcd()[3], 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(Helper::abcd()[0], 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find_last_not_of(Helper::abcd()[1], 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(Helper::abcd()[2], 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(Helper::abcd()[3], 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(Helper::abcd()[0], 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find_last_not_of(Helper::abcd()[1], 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find_last_not_of(Helper::abcd()[2], 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find_last_not_of(Helper::abcd()[3], 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(Helper::abcd()[0], 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find_last_not_of(Helper::abcd()[1], 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(Helper::abcd()[2], 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(Helper::abcd()[3], 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[0], 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[1], 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(Helper::abcd()[2], 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[3], 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[0], 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[1], 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(Helper::abcd()[2], 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd()[3], 6));

	// (3)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  0u == sv1.find_last_not_of(Helper::abcd(), 0, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 0, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 0, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 0, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find_last_not_of(Helper::abcd(), 1, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 1, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 1, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 1, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(Helper::abcd(), 2, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(Helper::abcd(), 2, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 2, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 2, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find_last_not_of(Helper::abcd(), 3, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find_last_not_of(Helper::abcd(), 3, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 3, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 3, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(Helper::abcd(), 4, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find_last_not_of(Helper::abcd(), 4, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 4, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 4, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd(), 5, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd(), 5, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd(), 5, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 5, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd(), 6, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd(), 6, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::abcd(), 6, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd(), 6, 3));

	// (4)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::abcd()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::ab()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::ab(), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::ab(), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::ab(), 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::ab(), 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find_last_not_of(Helper::ab(), 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::ab(), 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find_last_not_of(Helper::ab(), 6));
}

}	// namespace string_view_test
}	// namespace hamon_test
