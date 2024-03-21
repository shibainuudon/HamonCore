/**
 *	@file	unit_test_ranges_adaptors.cpp
 *
 *	@brief	Range adaptors のテスト
 */

#include <hamon/ranges.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/array.hpp>
#include <hamon/functional.hpp>
#include <hamon/list.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <cctype>
#include <map>

namespace hamon_ranges_test
{
namespace adaptors_test
{

struct even
{
	bool operator()(int i) const
	{
		return 0 == i % 2;
	}
};

struct square
{
	int operator()(int i) const
	{
		return i * i;
	}
};

struct to_upper
{
	char operator()(char c) const
	{
		return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
	}
};

struct is_space
{
	bool operator()(char c) const
	{
		return std::isspace(static_cast<unsigned char>(c));
	}
};

struct is_not_space
{
	bool operator()(char x, char y) const
	{
		return
			!std::isspace(static_cast<unsigned char>(x)) &&
			!std::isspace(static_cast<unsigned char>(y));
	}
};

GTEST_TEST(RangesTest, AdaptorsTest)
{
	namespace ranges = hamon::ranges;
	namespace views = hamon::views;
	{
		auto v = views::iota(1) | views::take(9);
		hamon::vector<int> expected = {1,2,3,4,5,6,7,8,9};
		EXPECT_TRUE(ranges::equal(expected, v));
		auto c = v | ranges::to<hamon::vector<int>>();
		EXPECT_TRUE(expected == c);
	}
	{
		auto s = views::repeat(hamon::string_view("hello ")) |
			views::take(3) |
			views::join |
			ranges::to<hamon::string>();
		EXPECT_TRUE(s == "hello hello hello ");
	}
	{
		auto v = views::iota(0, 6) |
			views::filter(even{}) |
			views::transform(square{}) |
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{0,4,16}));
	}
	{
		auto s = hamon::string("hello world") |
			views::transform(to_upper{}) |
			ranges::to<hamon::string>();
		EXPECT_TRUE(s == "HELLO WORLD");
	}
	{
		auto v = hamon::vector<int>{2,2,4,8,6,5,1,2,0,4} |
			views::take_while(even{}) |
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{2,2,4,8,6}));
	}
	{
		auto v = hamon::vector<int>{2,2,4,8,6,5,1,2,0,4} |
			views::reverse |
			views::take_while(even{}) |
			views::reverse |
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{2,0,4}));
	}
	{
		auto v = views::iota(1, 10) |
			views::drop(2) |
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{3,4,5,6,7,8,9}));
	}
	{
		auto v = views::iota(42) |
			views::take(6) |
			views::drop(2) |
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{44,45,46,47}));
	}
	{
		auto v = views::iota(10) |
			views::take(6) |
			views::reverse |
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{15,14,13,12,11,10}));
	}
	{
		auto s = hamon::string(" \n\t Hello, World! \r\n ") |
			views::drop_while(is_space{}) | views::reverse |
			views::drop_while(is_space{}) | views::reverse |
			ranges::to<hamon::string>();
		EXPECT_TRUE(s == "Hello, World!");
	}
	{
		auto s = hamon::vector<hamon::string>{ "the", "quick", "brown", "fox"} |
			views::join |
			ranges::to<hamon::string>();
		EXPECT_TRUE(s == "thequickbrownfox");
	}
	{
		auto s = hamon::vector<hamon::string>{ "the", "quick", "brown", "fox"} |
			views::join_with(' ') |
			ranges::to<hamon::string>();
		EXPECT_TRUE(s == "the quick brown fox");
	}
	{
		auto v = hamon::string_view("the quick brown fox") |
			views::split(' ') |
			ranges::to<hamon::vector<hamon::string>>();
		EXPECT_TRUE((v == hamon::vector<hamon::string>{"the", "quick", "brown", "fox"}));
	}
	{
		hamon::vector<int> vec = {1, 2, 4, 4, 1, 1, 1, 10, 23, 67, 9, 1, 1, 1, 1111, 1, 1, 1, 1, 1, 1, 9, 0};
		hamon::list<int> delimiter = {1, 1, 1};
		hamon::vector<int> expected[] = { {1, 2, 4, 4}, {10, 23, 67, 9}, {1111}, {}, {9, 0} };
		int i = 0;
		for (auto r : vec | views::lazy_split(delimiter))
		{
			EXPECT_TRUE(ranges::equal(r, expected[i]));
			++i;
		}
	}
	{
		auto r = hamon::vector<int>{3,1,4,1,5,9} | views::reverse;
		EXPECT_TRUE(ranges::equal(r, hamon::vector<int>{9,5,1,4,1,3}));
	}
	{
		auto r = hamon::vector<int>{3,1,4,1,5,9} | views::take(3) | views::reverse;
		EXPECT_TRUE(ranges::equal(r, hamon::vector<int>{4,1,3}));
	}
	{
		auto r = hamon::vector<int>{3,1,4,1,5,9} | views::reverse | views::take(3);
		EXPECT_TRUE(ranges::equal(r, hamon::vector<int>{9,5,1}));
	}
	{
		std::map<int, hamon::string> m =
		{
			{  1, "Alice" },
			{  3, "Bob" },
			{ 10, "Charlie" },
		};
		auto k = m | views::keys | views::transform(square{});
		auto v = m | views::values | views::take(10);
		EXPECT_TRUE(ranges::equal(k, hamon::vector<int>{1,9,100}));
		EXPECT_TRUE(ranges::equal(v, hamon::vector<hamon::string>{"Alice", "Bob", "Charlie"}));
	}
	{
		auto v = hamon::vector<hamon::string>{"the", "quick", "brown", "fox"} |
			views::enumerate | views::reverse;
		auto it = v.begin();
		EXPECT_TRUE(it[0] == hamon::make_tuple(3, "fox"));
		EXPECT_TRUE(it[1] == hamon::make_tuple(2, "brown"));
		EXPECT_TRUE(it[2] == hamon::make_tuple(1, "quick"));
		EXPECT_TRUE(it[3] == hamon::make_tuple(0, "the"));
	}
#if !(defined(HAMON_CLANG_VERSION) && defined(HAMON_STDLIB_DINKUMWARE))	// win-clangだと以下のコードがエラーになる
	{
		auto x = hamon::vector<int> {1, 2, 3, 4};
		auto y = hamon::list<hamon::string> {"the", "quick", "brown", "fox", "jumps"};
		auto z = hamon::array<char, 6> {'A', 'B', 'C', 'D', 'E', 'F'};
		auto v = views::zip(x, y, z);
		auto it = v.begin();
		EXPECT_TRUE(*it++ == hamon::make_tuple(1, "the", 'A'));
		EXPECT_TRUE(*it++ == hamon::make_tuple(2, "quick", 'B'));
		EXPECT_TRUE(*it++ == hamon::make_tuple(3, "brown", 'C'));
		EXPECT_TRUE(*it++ == hamon::make_tuple(4, "fox", 'D'));
		EXPECT_TRUE(it == v.end());
	}
#endif

	// MSVC-STLだと、バージョンによってはエラーになる
#if !defined(HAMON_USE_STD_RANGES_ZIP_TRANSFORM_VIEW) && defined(HAMON_STDLIB_DINKUMWARE)
	{
		auto x = hamon::vector<char>{1,2,3};
		auto y = hamon::list<short>{10,20,30,40};
		auto v = views::zip_transform(ranges::plus{}, x, y) |
			views::reverse |
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{33,22,11}));
	}
#endif
	{
		auto v = hamon::vector<int>{1,2,3,4,5} |
			views::pairwise | views::take(3);
		auto it = v.begin();
		EXPECT_TRUE(*it++ == hamon::make_tuple(1, 2));
		EXPECT_TRUE(*it++ == hamon::make_tuple(2, 3));
		EXPECT_TRUE(*it++ == hamon::make_tuple(3, 4));
		EXPECT_TRUE(it == v.end());
	}
	{
		auto v = hamon::vector<int>{1,2,3,4,5} |
			views::pairwise_transform(ranges::plus{}) |
			views::reverse |
			views::drop(1) |
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{7,5,3}));
	}
	{
		auto v = hamon::vector<int>{1,2,3,4,5} |
			views::slide(3) |	// [1,2,3][2,3,4][3,4,5]
			views::join |		// [1,2,3,2,3,4,3,4,5]
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{1,2,3,2,3,4,3,4,5}));
	}
	{
		auto v = hamon::vector<int>{1,2,3,4,5} |
			views::chunk(3) |	// [1,2,3][4,5]
			views::reverse |	// [4,5][1,2,3]
			views::join |		// [4,5,1,2,3]
			ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{4,5,1,2,3}));
	}
	{
		auto s = hamon::string("the brown fox jumps") |
			views::chunk_by(is_not_space{}) |	// "the", " ", "brown", " ", "fox", " ", "jumps"
			views::reverse |					// "jumps", " ", "fox", " ", "brown", " ", "the",
			views::join |						// "jumps fox brown the",
			ranges::to<hamon::string>();
		EXPECT_EQ(s, "jumps fox brown the");
	}
	{
		auto v = views::iota(1) | views::stride(3) | views::take(5) | ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{1,4,7,10,13}));
	}
	{
		auto v = views::iota(1, 13) | views::stride(3) | views::reverse | ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{10,7,4,1}));
	}
	{
		auto v = views::iota(1, 13) | views::reverse | views::stride(3) | ranges::to<hamon::vector<int>>();
		EXPECT_TRUE((v == hamon::vector<int>{12,9,6,3}));
	}
}

}	// namespace adaptors_test
}	// namespace hamon_ranges_test
