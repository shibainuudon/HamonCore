/**
 *	@file	unit_test_string_view_front.cpp
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

TYPED_TEST(StringViewTest, FrontTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;
	using const_reference = typename string_view::const_reference;

	{
		HAMON_CXX11_CONSTEXPR auto str = Helper::foo_bar();
		HAMON_CXX11_CONSTEXPR string_view sv{str};
		HAMON_CXX11_CONSTEXPR const_reference r = sv.front();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(r == str[0]);
	}
	{
		HAMON_CXX11_CONSTEXPR auto str = Helper::abcd();
		HAMON_CXX11_CONSTEXPR string_view sv{str};
		HAMON_CXX11_CONSTEXPR const_reference r = sv.front();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(r == str[0]);
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
