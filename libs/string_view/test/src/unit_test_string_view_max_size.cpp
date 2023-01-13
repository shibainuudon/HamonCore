/**
 *	@file	unit_test_string_view_max_size.cpp
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

TYPED_TEST(StringViewTest, MaxSizeTest)
{
	using CharT = TypeParam;
	using string_view = hamon::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::foo_bar()};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::aababc()};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{Helper::abcd()};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
