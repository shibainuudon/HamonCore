/**
 *	@file	unit_test_ranges_cartesian_product_view_iterator_add.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	friend constexpr iterator operator+(const iterator& x, difference_type y)
 *	  requires cartesian-product-is-random-access<Const, First, Vs...>;
 *	friend constexpr iterator operator+(difference_type x, const iterator& y)
 *	  requires cartesian-product-is-random-access<Const, First, Vs...>;
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
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
namespace iterator_add_test
{

template <typename T, typename U, typename = void>
struct has_add
	: public hamon::false_type {};

template <typename T, typename U>
struct has_add<T, U, hamon::void_t<decltype(hamon::declval<T>() + hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<char>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_bidirectional_view<char>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<char>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_random_access_view<int>;
	using CV = hamon::ranges::cartesian_product_view<V>;

	int a[] = {1,2,3,4,5};
	V v(a);
	CV cv(v);
	auto it1 = cv.begin() + 1;
	auto it2 = 2 + cv.begin();
	VERIFY(*it1 == hamon::make_tuple(2));
	VERIFY(*it2 == hamon::make_tuple(3));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<char>;
	using V3 = test_random_access_view<float>;
	using CV = hamon::ranges::cartesian_product_view<V1, V2, V3>;

	int a1[] = {1,2,3};
	char a2[] = {'a', 'b'};
	float a3[] = {0.5f, 1.5f, 2.5f};
	V1 v1(a1);
	V2 v2(a2);
	V3 v3(a3);
	CV cv(v1, v2, v3);

	auto it = cv.begin();
	auto it01 = it +  0;
	auto it02 = it +  1;
	auto it03 = it +  2;
	auto it04 = it +  3;
	auto it05 = it +  4;
	auto it06 = it +  5;
	auto it07 = it +  6;
	auto it08 = it +  7;
	auto it09 = it +  8;
	auto it10 = it +  9;
	auto it11 = it + 10;
	auto it12 = it + 11;
	auto it13 = it + 12;
	auto it14 = it + 13;
	auto it15 = it + 14;
	auto it16 = it + 15;
	auto it17 = it + 16;
	auto it18 = it + 17;
	VERIFY(*it01 == hamon::make_tuple(1, 'a', 0.5f));
	VERIFY(*it02 == hamon::make_tuple(1, 'a', 1.5f));
	VERIFY(*it03 == hamon::make_tuple(1, 'a', 2.5f));
	VERIFY(*it04 == hamon::make_tuple(1, 'b', 0.5f));
	VERIFY(*it05 == hamon::make_tuple(1, 'b', 1.5f));
	VERIFY(*it06 == hamon::make_tuple(1, 'b', 2.5f));
	VERIFY(*it07 == hamon::make_tuple(2, 'a', 0.5f));
	VERIFY(*it08 == hamon::make_tuple(2, 'a', 1.5f));
	VERIFY(*it09 == hamon::make_tuple(2, 'a', 2.5f));
	VERIFY(*it10 == hamon::make_tuple(2, 'b', 0.5f));
	VERIFY(*it11 == hamon::make_tuple(2, 'b', 1.5f));
	VERIFY(*it12 == hamon::make_tuple(2, 'b', 2.5f));
	VERIFY(*it13 == hamon::make_tuple(3, 'a', 0.5f));
	VERIFY(*it14 == hamon::make_tuple(3, 'a', 1.5f));
	VERIFY(*it15 == hamon::make_tuple(3, 'a', 2.5f));
	VERIFY(*it16 == hamon::make_tuple(3, 'b', 0.5f));
	VERIFY(*it17 == hamon::make_tuple(3, 'b', 1.5f));
	VERIFY(*it18 == hamon::make_tuple(3, 'b', 2.5f));

	VERIFY(*(17 + it01) == *it18);
	VERIFY(*(16 + it02) == *it18);
	VERIFY(*(15 + it03) == *it18);
	VERIFY(*(14 + it04) == *it18);
	VERIFY(*(13 + it05) == *it18);
	VERIFY(*(12 + it06) == *it18);
	VERIFY(*(11 + it07) == *it18);
	VERIFY(*(10 + it08) == *it18);
	VERIFY(*( 9 + it09) == *it18);
	VERIFY(*( 8 + it10) == *it18);
	VERIFY(*( 7 + it11) == *it18);
	VERIFY(*( 6 + it12) == *it18);
	VERIFY(*( 5 + it13) == *it18);
	VERIFY(*( 4 + it14) == *it18);
	VERIFY(*( 3 + it15) == *it18);
	VERIFY(*( 2 + it16) == *it18);
	VERIFY(*( 1 + it17) == *it18);
	VERIFY(*( 0 + it18) == *it18);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewIteratorAddTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_add_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
