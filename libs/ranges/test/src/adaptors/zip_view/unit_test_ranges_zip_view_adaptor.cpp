/**
 *	@file	unit_test_ranges_zip_view_adaptor.cpp
 *
 *	@brief	views::zip のテスト
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	auto zv = hamon::views::zip();
	static_assert(hamon::is_same<decltype(zv), hamon::ranges::empty_view<hamon::tuple<>>>::value, "");
	VERIFY(zv.empty());
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a1[] = {1,2,3,4,5,6,7,8,9,};
	char a2[] = {'A','B','C','D','E','F',};
	hamon::string_view a3[] =
	{
		hamon::string_view("Alice"),
		hamon::string_view("Bob"),
		hamon::string_view("Charlie"),
		hamon::string_view("Dave"),
	};

	{
		auto zv = hamon::views::zip(a1, a2, a3);
		static_assert(hamon::is_same<decltype(zv),
			hamon::ranges::zip_view<
				hamon::views::all_t<int(&)[9]>,
				hamon::views::all_t<char(&)[6]>,
				hamon::views::all_t<hamon::string_view(&)[4]>
			>
		>::value, "");
		
		hamon::tuple<int, char, hamon::string_view> expected[] =
		{
			{1, 'A', hamon::string_view("Alice")},
			{2, 'B', hamon::string_view("Bob")},
			{3, 'C', hamon::string_view("Charlie")},
			{4, 'D', hamon::string_view("Dave")},
		};
		VERIFY(hamon::ranges::equal(zv, expected));
	}
	{
		auto zv = hamon::views::zip(a1, a2);
		static_assert(hamon::is_same<decltype(zv),
			hamon::ranges::zip_view<
				hamon::views::all_t<int(&)[9]>,
				hamon::views::all_t<char(&)[6]>
			>
		>::value, "");

		hamon::tuple<int, char> expected[] =
		{
			{1, 'A'},
			{2, 'B'},
			{3, 'C'},
			{4, 'D'},
			{5, 'E'},
			{6, 'F'},
		};
		VERIFY(hamon::ranges::equal(zv, expected));
	}
	{
		auto zv = hamon::views::zip(a1, a3);
		static_assert(hamon::is_same<decltype(zv),
			hamon::ranges::zip_view<
				hamon::views::all_t<int(&)[9]>,
				hamon::views::all_t<hamon::string_view(&)[4]>
			>
		>::value, "");

		hamon::tuple<int, hamon::string_view> expected[] =
		{
			{1, hamon::string_view("Alice")},
			{2, hamon::string_view("Bob")},
			{3, hamon::string_view("Charlie")},
			{4, hamon::string_view("Dave")},
		};
		VERIFY(hamon::ranges::equal(zv, expected));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace adaptor_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
