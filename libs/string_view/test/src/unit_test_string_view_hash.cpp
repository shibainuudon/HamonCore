/**
 *	@file	unit_test_string_view_hash.cpp
 *
 *	@brief
 */

#include <hamon/string_view.hpp>
#include <hamon/functional/hash.hpp>
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

	HAMON_CXX11_CONSTEXPR string_view const sv1{Helper::abcd()};
	HAMON_CXX11_CONSTEXPR string_view const sv2{Helper::abcd(), 4};
	HAMON_CXX11_CONSTEXPR string_view const sv3{Helper::abcd(), 3};
	HAMON_CXX11_CONSTEXPR string_view const sv4{Helper::abcd(), 2};
	HAMON_CXX11_CONSTEXPR string_view const sv5{Helper::ab()};

	HAMON_CXX11_CONSTEXPR hamon::hash<string_view> h{};

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv1) == h(sv1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv1) == h(sv2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv1) != h(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv1) != h(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv1) != h(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv2) == h(sv2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv2) != h(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv2) != h(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv2) != h(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv3) == h(sv3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv3) != h(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv3) != h(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv4) == h(sv4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv4) == h(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(h(sv5) == h(sv5));

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
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv4) == hamon::ranges::hash(sv5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(sv5) == hamon::ranges::hash(sv5));
}

}	// namespace string_view_test
}	// namespace hamon_test
