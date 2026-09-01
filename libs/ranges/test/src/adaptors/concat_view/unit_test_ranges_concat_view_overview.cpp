/**
 *	@file	unit_test_ranges_concat_view_overview.cpp
 *
 *	@brief	concat_view のテスト
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/size.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace overview_test
{

GTEST_TEST(RangesTest, ConcatViewOverviewTest)
{
	{
		// 25.7.18.1 Overview[range.concat.overview]
		// Example 1:
		hamon::vector<int> v1{ 1, 2, 3 }, v2{ 4, 5 }, v3{};
		hamon::array<int, 3> a{ 6, 7, 8 };
		auto s = hamon::views::single(9);
		hamon::stringstream out;
		for (auto&& i : hamon::views::concat(v1, v2, v3, a, s))
		{
			out << i << ' ';      // prints 1 2 3 4 5 6 7 8 9
		}
		EXPECT_EQ("1 2 3 4 5 6 7 8 9 ", out.str());
	}
	{
		// https://en.cppreference.com/cpp/ranges/concat_view
		hamon::vector<int> v0{ 1, 2, 3 }, v1{ 4, 5 };
		int a[]{ 6, 7 };
		int i{ 8 };
		auto ie{ hamon::views::single(i) };

		auto con = hamon::views::concat(v0, v1, a, ie);
		EXPECT_TRUE(con.size() == v0.size() + v1.size() + hamon::size(a) + ie.size());
		{
			hamon::stringstream out;
			for (auto&& t : con)
			{
				out << t << ' ';
			}
			EXPECT_EQ("1 2 3 4 5 6 7 8 ", out.str());
		}
		con[6] = 42; // con is random_access_range, operator[] returns a reference
		EXPECT_TRUE(a[1] == 42); // a[1] was modified via con[6]
		{
			hamon::stringstream out;
			for (auto&& t : con)
			{
				out << t << ' ';
			}
			EXPECT_EQ("1 2 3 4 5 6 42 8 ", out.str());
		}

		hamon::list<int> l{ 7, 8 }; // list is bidirectional range
		auto cat = hamon::views::concat(v0, l);
		{
			hamon::stringstream out;
			for (auto&& t : cat)
			{
				out << t << ' ';
			}
			EXPECT_EQ("1 2 3 7 8 ", out.str());
		}
		// cat[0] = 13; // compile-time error: cat is bidirectional => no operator[]
	}
	{
		// https://en.cppreference.com/cpp/ranges/concat_view/iterator
		const int p[]{ 1, 2, 3 };
		const auto e = { 4, 5 };
		auto t = hamon::views::iota(6, 9);
		auto cat = hamon::views::concat(p, e, t);
		auto dog = hamon::views::concat(cat, cat);
		hamon::stringstream out;
		for (auto i{ dog.begin() }; i != hamon::default_sentinel; ++i)
		{
			out << *i << ' ';
		}
		EXPECT_EQ("1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 ", out.str());
	}
}

}	// namespace overview_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
