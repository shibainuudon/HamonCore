/**
 *	@file	unit_test_ranges_zip_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	friend constexpr void iter_swap(const iterator& l, const iterator& r) noexcept(see below)
 *	  requires (indirectly_swappable<iterator_t<maybe-const<Const, Views>>> && ...);
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace iterator_iter_swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<char>;
	using ZV = hamon::ranges::zip_view<V1, V2>;

	int a1[] = {42, 43, 44};
	char a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(v1, v2);

	auto it1 = zv.begin() + 1;
	auto it2 = zv.begin() + 2;
	hamon::ranges::iter_swap(it1, it2);
#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
	static_assert(!noexcept(hamon::ranges::iter_swap(it1, it2)), "");
#endif

	VERIFY(a1[0] == 42);
	VERIFY(a1[1] == 44);
	VERIFY(a1[2] == 43);

	VERIFY(a2[0] == 1);
	VERIFY(a2[1] == 3);
	VERIFY(a2[2] == 2);
	VERIFY(a2[3] == 4);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a1[] = {10,20,30,40,50};
	char a2[] = {1,2,3,4,5};
	auto zv = hamon::views::zip(a1, a2);

	auto it1 = zv.begin() + 3;
	auto it2 = zv.begin() + 2;
	hamon::ranges::iter_swap(it1, it2);
#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
	static_assert(noexcept(hamon::ranges::iter_swap(it1, it2)), "");
#endif

	VERIFY(a1[0] == 10);
	VERIFY(a1[1] == 20);
	VERIFY(a1[2] == 40);
	VERIFY(a1[3] == 30);
	VERIFY(a1[4] == 50);

	VERIFY(a2[0] == 1);
	VERIFY(a2[1] == 2);
	VERIFY(a2[2] == 4);
	VERIFY(a2[3] == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_iter_swap_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
