/**
 *	@file	unit_test_string_view_hash.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/functional/ranges/hash.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

TYPED_TEST(StringViewTest, HashTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;

	HAMON_CXX11_CONSTEXPR string_view const sv1{Helper::aababc()};
	HAMON_CXX11_CONSTEXPR string_view const sv2{Helper::aababc(), 6};
	HAMON_CXX11_CONSTEXPR string_view const sv3{Helper::aababc(), 5};
	HAMON_CXX11_CONSTEXPR string_view const sv4{Helper::aababc(), 4};
	HAMON_CXX11_CONSTEXPR string_view const sv5{Helper::abcd()};

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv1) == hamon::ranges::hash(sv1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv1) == hamon::ranges::hash(sv2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv1) != hamon::ranges::hash(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv1) != hamon::ranges::hash(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv1) != hamon::ranges::hash(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv2) == hamon::ranges::hash(sv2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv2) != hamon::ranges::hash(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv2) != hamon::ranges::hash(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv2) != hamon::ranges::hash(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv3) == hamon::ranges::hash(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv3) != hamon::ranges::hash(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv3) != hamon::ranges::hash(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv4) == hamon::ranges::hash(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv4) != hamon::ranges::hash(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv5) == hamon::ranges::hash(sv5));
}

}	// namespace string_view_test
}	// namespace hamon_test
