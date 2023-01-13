/**
 *	@file	unit_test_string_view_back.cpp
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

TYPED_TEST(StringViewTest, BackTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;
	using const_reference = typename string_view::const_reference;

	{
		HAMON_CXX11_CONSTEXPR auto str = Helper::foo_bar();
		HAMON_CXX11_CONSTEXPR string_view sv{str};
		HAMON_CXX11_CONSTEXPR const_reference r = sv.back();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(r == str[6]);
	}
	{
		HAMON_CXX11_CONSTEXPR auto str = Helper::abcd();
		HAMON_CXX11_CONSTEXPR string_view sv{str};
		HAMON_CXX11_CONSTEXPR const_reference r = sv.back();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(r == str[3]);
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
