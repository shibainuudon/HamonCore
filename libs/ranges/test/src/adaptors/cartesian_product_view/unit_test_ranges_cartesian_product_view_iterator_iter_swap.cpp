/**
 *	@file	unit_test_ranges_cartesian_product_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	friend constexpr void iter_swap(const iterator& l, const iterator& r) noexcept(see below)
 *	  requires (indirectly_swappable<iterator_t<maybe-const<Const, First>>> && ... &&
 *	    indirectly_swappable<iterator_t<maybe-const<Const, Vs>>>);
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace iterator_iter_swap_test
{

template <typename T, typename = void>
struct has_iter_swap
	: public hamon::false_type {};

template <typename T>
struct has_iter_swap<T, hamon::void_t<decltype(hamon::ranges::iter_swap(hamon::declval<T>(), hamon::declval<T>()))>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int const>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_iter_swap<I>::value, "");
	}
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_iter_swap<I>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		CV cv(v);

		auto it1 = cv.begin();
		auto it2 = cv.begin();
		it2++; it2++;
		hamon::ranges::iter_swap(it1, it2);
		static_assert(!noexcept(hamon::ranges::iter_swap(it1, it2)), "");

		VERIFY(a[0] == 3);
		VERIFY(a[1] == 2);
		VERIFY(a[2] == 1);
		VERIFY(a[3] == 4);
		VERIFY(a[4] == 5);
	}
	{
		int a[] = {1,2,3,4,5};
		auto cv = hamon::views::cartesian_product(a);

		auto it1 = cv.begin();
		auto it2 = cv.begin();
		it1++;
		hamon::ranges::iter_swap(it1, it2);
		static_assert( noexcept(hamon::ranges::iter_swap(it1, it2)), "");

		VERIFY(a[0] == 2);
		VERIFY(a[1] == 1);
		VERIFY(a[2] == 3);
		VERIFY(a[3] == 4);
		VERIFY(a[4] == 5);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V1 = test_random_access_view<int const>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_iter_swap<I>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int const>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_iter_swap<I>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_iter_swap<I>::value, "");

		int a1[] = {1,2,3,4,5};
		int a2[] = {11,12,13};
		V1 v1(a1);
		V2 v2(a2);
		CV cv(v1, v2);
		auto it1 = cv.begin() + 1;
		auto it2 = cv.begin() + 3;
		hamon::ranges::iter_swap(it1, it2);
		static_assert(!noexcept(hamon::ranges::iter_swap(it1, it2)), "");

		VERIFY(a1[0] == 2);
		VERIFY(a1[1] == 1);
		VERIFY(a1[2] == 3);
		VERIFY(a1[3] == 4);
		VERIFY(a1[4] == 5);

		VERIFY(a2[0] == 12);
		VERIFY(a2[1] == 11);
		VERIFY(a2[2] == 13);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a1[] = {1,2,3};
	char a2[] = {'a', 'b'};
	float a3[] = {0.5f, 1.5f, 2.5f};

	auto cv = hamon::views::cartesian_product(a1, a2, a3);

	auto it1 = cv.begin() + 12;
	auto it2 = cv.begin() + 1;
	hamon::ranges::iter_swap(it1, it2);
	static_assert( noexcept(hamon::ranges::iter_swap(it1, it2)), "");

	VERIFY(a1[0] == 3);
	VERIFY(a1[1] == 2);
	VERIFY(a1[2] == 1);

	VERIFY(a2[0] == 'a');
	VERIFY(a2[1] == 'b');

	VERIFY(a3[0] == 1.5f);
	VERIFY(a3[1] == 0.5f);
	VERIFY(a3[2] == 2.5f);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_iter_swap_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
