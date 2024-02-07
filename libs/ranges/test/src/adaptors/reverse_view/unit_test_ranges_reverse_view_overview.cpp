/**
 *	@file	unit_test_ranges_reverse_view_overview.cpp
 *
 *	@brief	reverse_view のテスト
 */

#include <hamon/ranges/adaptors/reverse_view.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

namespace hamon_ranges_test
{
namespace reverse_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, ReverseViewOverviewTest)
{
	{
		// [range.reverse.overview]/3
		// Example 1:
		std::vector<int> is {0, 1, 2, 3, 4};
		std::stringstream out;
		for (int i : is | hamon::views::reverse)
		{
			out << i << ' '; // prints 4 3 2 1 0
		}
		EXPECT_EQ("4 3 2 1 0 ", out.str());
	}

	{
		std::stringstream out;
		for (char c : hamon::string_view("Hello") | hamon::views::reverse)
		{
			out << c;
		}
		EXPECT_EQ("olleH", out.str());
	}
	{
		// reverseを2回適用すると元の型に戻る
		static_assert(hamon::same_as_t<
			hamon::string_view,
			decltype(hamon::string_view{} | hamon::views::reverse | hamon::views::reverse)
		>::value, "");

		std::stringstream out;
		for (char c : hamon::string_view("Hello") | hamon::views::reverse | hamon::views::reverse)
		{
			out << c;
		}
		EXPECT_EQ("Hello", out.str());
	}

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		auto il = {3, 1, 4, 1, 5, 9};

		{
			std::stringstream out;
			hamon::ranges::reverse_view rv {il};
			for (int i : rv)
			{
				out << i << ' ';
			}
			EXPECT_EQ("9 5 1 4 1 3 ", out.str());
		}
		{
			std::stringstream out;
			for (int i : il | hamon::views::reverse)
			{
				out << i << ' ';
			}
			EXPECT_EQ("9 5 1 4 1 3 ", out.str());
		}
		{
			std::stringstream out;
			hamon::ranges::reverse_view rv {il};
			// operator[] is inherited from hamon::view_interface
			for (auto i {0U}; i != rv.size(); ++i)
			{
				using D = hamon::ranges::range_reference_t<decltype(rv)>;
				out << rv[static_cast<D>(i)] << ' ';
			}
			EXPECT_EQ("9 5 1 4 1 3 ", out.str());
		}
	}
#endif
}

}	// namespace overview_test
}	// namespace reverse_view_test
}	// namespace hamon_ranges_test
