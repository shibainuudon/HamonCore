/**
 *	@file	unit_test_string_view_at.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

TYPED_TEST(StringViewTest, AtTest)
{
	using CharT = TypeParam;
	using string_view = hamon::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;

	{
		HAMON_CXX11_CONSTEXPR auto str = StringViewTestHelper<CharT>::foo_bar();
		HAMON_CXX11_CONSTEXPR string_view sv{str};
		HAMON_CXX11_CONSTEXPR const_reference r0 = sv.at(0);
		HAMON_CXX11_CONSTEXPR const_reference r1 = sv.at(1);
		HAMON_CXX11_CONSTEXPR const_reference r2 = sv.at(2);
		HAMON_CXX11_CONSTEXPR const_reference r3 = sv.at(3);
		HAMON_CXX11_CONSTEXPR const_reference r4 = sv.at(4);
		HAMON_CXX11_CONSTEXPR const_reference r5 = sv.at(5);
		HAMON_CXX11_CONSTEXPR const_reference r6 = sv.at(6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(str[0] == r0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(str[1] == r1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(str[2] == r2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(str[3] == r3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(str[4] == r4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(str[5] == r5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(str[6] == r6);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};
		EXPECT_THROW((void)sv.at(7), hamon::out_of_range);
	}
	{
		string_view sv{StringViewTestHelper<CharT>::with_nulls()};
		EXPECT_NO_THROW((void)sv.at(0));
		EXPECT_NO_THROW((void)sv.at(13));
		EXPECT_THROW   ((void)sv.at(14),  hamon::out_of_range);
		EXPECT_THROW   ((void)sv.at(100), hamon::out_of_range);
	}
	{
		string_view sv;
		EXPECT_THROW((void)sv.at(0), hamon::out_of_range);
		EXPECT_THROW((void)sv.at(1), hamon::out_of_range);
	}
#endif
}

}	// namespace string_view_test
}	// namespace hamon_test
