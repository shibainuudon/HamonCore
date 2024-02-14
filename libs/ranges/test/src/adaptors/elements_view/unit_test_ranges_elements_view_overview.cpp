/**
 *	@file	unit_test_ranges_elements_view_overview.cpp
 *
 *	@brief	elements_view のテスト
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/algorithm/ranges/count_if.hpp>
#include <hamon/pair.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <map>
#include <sstream>

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, ElementsViewOverviewTest)
{
#if !(defined(HAMON_CLANG_VERSION) && defined(HAMON_STDLIB_DINKUMWARE))	// win-clangだと以下のコードがエラーになる
	{
		// [range.elements.overview]/2
		// Example 1:
		auto historical_figures = std::map<hamon::string_view, int>
		{
			{ hamon::string_view{"Lovelace"}, 1815 },
			{ hamon::string_view{"Turing"},   1912 },
			{ hamon::string_view{"Babbage"},  1791 },
			{ hamon::string_view{"Hamilton"}, 1936 },
		};

		{
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
			auto names = historical_figures | hamon::views::elements<0>;
#else
			auto names = historical_figures | hamon::views::elements_t<0>{};
#endif
			std::stringstream out;
			for (auto&& name : names)
			{
				out << name << ' ';          // prints Babbage Hamilton Lovelace Turing 
			}
			EXPECT_EQ("Babbage Hamilton Lovelace Turing ", out.str());
		}
		{
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
			auto birth_years = historical_figures | hamon::views::elements<1>;
#else
			auto birth_years = historical_figures | hamon::views::elements_t<1>{};
#endif
			std::stringstream out;
			for (auto&& born : birth_years)
			{
				out << born << ' ';          // prints 1791 1936 1815 1912 
			}
			EXPECT_EQ("1791 1936 1815 1912 ", out.str());
		}

		// Example 2:
		{
			auto names = historical_figures | hamon::views::keys;
			std::stringstream out;
			for (auto&& name : names)
			{
				out << name << ' ';          // prints Babbage Hamilton Lovelace Turing 
			}
			EXPECT_EQ("Babbage Hamilton Lovelace Turing ", out.str());
		}

		// Example 3:
		{
			auto is_even = [](int x) { return x % 2 == 0; };
			EXPECT_EQ(2, hamon::ranges::count_if(historical_figures | hamon::views::values, is_even));
		}
	}
#endif
}

}	// namespace overview_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
