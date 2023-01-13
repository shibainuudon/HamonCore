/**
 *	@file	unit_test_string_view_empty.cpp
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

TYPED_TEST(StringViewTest, EmptyTest)
{
	using CharT = TypeParam;
	using string_view = hamon::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::foo_bar(), 7};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::foo_bar(), 0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::aababc()};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::aababc(), 0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::abcd(), 1};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{nullptr, 0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.empty());
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
