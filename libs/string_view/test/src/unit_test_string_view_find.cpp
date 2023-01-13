/**
 *	@file	unit_test_string_view_find.cpp
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

TYPED_TEST(StringViewTest, FindTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;

	HAMON_CXX11_CONSTEXPR auto const npos = string_view::npos;

	HAMON_CXX11_CONSTEXPR string_view const sv1{Helper::aababc(), 6};	// "aababc"
	HAMON_CXX11_CONSTEXPR string_view const sv2{Helper::abcd(), 1};	// "a"
	HAMON_CXX11_CONSTEXPR string_view const sv3{Helper::abcd(), 2};	// "ab"
	HAMON_CXX11_CONSTEXPR string_view const sv4{Helper::abcd(), 3};	// "abc"
	HAMON_CXX11_CONSTEXPR string_view const sv5{Helper::abcd(), 4};	// "abcd"

	// (1)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  0u == sv1.find(sv2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(sv5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find(sv2, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find(sv3, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(sv4, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(sv5, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(sv2, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(sv3, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(sv4, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(sv5, 2));

	// (2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  0u == sv1.find(Helper::abcd()[0]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find(Helper::abcd()[1]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  5u == sv1.find(Helper::abcd()[2]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(Helper::abcd()[3]));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find(Helper::abcd()[1], 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find(Helper::abcd()[1], 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  4u == sv1.find(Helper::abcd()[1], 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(Helper::abcd()[1], 5));

	// (3)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  0u == sv1.find(Helper::abcd(), 0, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  0u == sv1.find(Helper::abcd(), 0, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find(Helper::abcd(), 0, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(Helper::abcd(), 0, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(Helper::abcd(), 0, 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  2u == sv1.find(Helper::abcd(), 2, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(Helper::abcd(), 2, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(Helper::abcd(), 2, 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(Helper::abcd(), 2, 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(Helper::abcd(), 2, 4));

	// (4)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(Helper::abcd()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find(Helper::ab()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  1u == sv1.find(Helper::ab(), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(Helper::ab(), 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(  3u == sv1.find(Helper::ab(), 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(Helper::ab(), 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(npos == sv1.find(Helper::ab(), 5));
}

}	// namespace string_view_test
}	// namespace hamon_test
