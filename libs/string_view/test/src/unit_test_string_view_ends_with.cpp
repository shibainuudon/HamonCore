/**
 *	@file	unit_test_string_view_ends_with.cpp
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

TYPED_TEST(StringViewTest, EndsWithTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;

	{
		HAMON_CXX11_CONSTEXPR string_view const sv{Helper::abcd()};

		// (1)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv.ends_with(string_view{Helper::aababc(), 1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv.ends_with(string_view{Helper::aababc(), 2})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv.ends_with(string_view{Helper::ab()})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv.ends_with(string_view{Helper::cd()})));

		// (2)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv.ends_with(Helper::aababc()[0])));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv.ends_with(Helper::aababc()[2])));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv.ends_with(Helper::abcd()[2])));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv.ends_with(Helper::abcd()[3])));

		// (3)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv.ends_with(Helper::abcd())));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv.ends_with(Helper::ab())));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv.ends_with(Helper::cd())));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv.ends_with(Helper::aababc())));
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
