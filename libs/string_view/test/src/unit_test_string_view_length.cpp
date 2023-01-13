/**
 *	@file	unit_test_string_view_length.cpp
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

TYPED_TEST(StringViewTest, LengthTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	using Helper = StringViewTestHelper<TypeParam>;

	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::foo_bar()};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 7);
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::foo_bar(), 6};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 6);
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::aababc()};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 6);
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::aababc(), 3};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::abcd()};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 4);
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::abcd(), 0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 0);
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 0);
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
