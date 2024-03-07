/**
 *	@file	unit_test_ranges_cartesian_product_view_adaptor.cpp
 *
 *	@brief	views::cartesian_product のテスト
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	auto cv = hamon::views::cartesian_product();
	static_assert(hamon::is_same<decltype(cv), hamon::ranges::single_view<hamon::tuple<>>>::value, "");
	VERIFY(!cv.empty());
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_input_view<int>;

		int a[] = {1,2,3};
		V v(a);
		
		{
			auto cv = hamon::views::cartesian_product(v);
			static_assert(hamon::is_same<decltype(cv), hamon::ranges::cartesian_product_view<V>>::value, "");

			hamon::tuple<int> expected[] =
			{
				{1},
				{2},
				{3},
			};
			VERIFY(hamon::ranges::equal(cv, expected));
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		using V1 = test_input_view<int>;
		using V2 = test_forward_view<int>;

		int a1[] = {0,1,2};
		int a2[] = {10,20};
		V1 v1(a1);
		V2 v2(a2);
		
		{
			auto cv = hamon::views::cartesian_product(v1, v2);
			static_assert(hamon::is_same<decltype(cv), hamon::ranges::cartesian_product_view<V1, V2>>::value, "");

			hamon::tuple<int, int> expected[] =
			{
				{0, 10},
				{0, 20},
				{1, 10},
				{1, 20},
				{2, 10},
				{2, 20},
			};
			VERIFY(hamon::ranges::equal(cv, expected));
		}
	}
	{
		using V = test_forward_view<int>;

		int a[] = {1,2,3};
		V v(a);
		
		{
			auto cv = hamon::views::cartesian_product(v, v);
			static_assert(hamon::is_same<decltype(cv), hamon::ranges::cartesian_product_view<V, V>>::value, "");

			hamon::tuple<int, int> expected[] =
			{
				{1, 1},
				{1, 2},
				{1, 3},
				{2, 1},
				{2, 2},
				{2, 3},
				{3, 1},
				{3, 2},
				{3, 3},
			};
			VERIFY(hamon::ranges::equal(cv, expected));
		}
	}
	return true;
}

inline bool test03()
{
#if !(defined(HAMON_CLANG_VERSION) && defined(HAMON_STDLIB_DINKUMWARE))	// win-clangだと以下のコードがエラーになる
    const auto x = hamon::array<char, 2>{'A', 'B'};
    const auto y = hamon::vector<int>{1, 2, 3};
    const auto z = hamon::list<hamon::string>{"The", "quick", "brown", "fox"};
	auto cv = hamon::views::cartesian_product(x, y, z);
	
	hamon::tuple<char, int, hamon::string> expected[] =
	{
		{ 'A', 1, "The"}, { 'A', 1, "quick"}, { 'A', 1, "brown"}, { 'A', 1, "fox"},
		{ 'A', 2, "The"}, { 'A', 2, "quick"}, { 'A', 2, "brown"}, { 'A', 2, "fox"},
		{ 'A', 3, "The"}, { 'A', 3, "quick"}, { 'A', 3, "brown"}, { 'A', 3, "fox"},
		{ 'B', 1, "The"}, { 'B', 1, "quick"}, { 'B', 1, "brown"}, { 'B', 1, "fox"},
		{ 'B', 2, "The"}, { 'B', 2, "quick"}, { 'B', 2, "brown"}, { 'B', 2, "fox"},
		{ 'B', 3, "The"}, { 'B', 3, "quick"}, { 'B', 3, "brown"}, { 'B', 3, "fox"},
	};

	VERIFY(hamon::ranges::equal(cv, expected));
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace adaptor_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
