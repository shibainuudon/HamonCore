/**
 *	@file	unit_test_ranges_cartesian_product_view_iterator_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr reference operator[](difference_type n) const
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
namespace iterator_subscript_test
{

template <typename T, typename = void>
struct has_subscript
	: public hamon::false_type {};

template <typename T>
struct has_subscript<T, hamon::void_t<decltype(hamon::declval<T>()[hamon::declval<int>()])>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()[hamon::declval<int>()]), hamon::tuple<int&>>::value, "");
	}
	{
		using V = test_contiguous_view<int const>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()[hamon::declval<int>()]), hamon::tuple<int const&>>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<char>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()[hamon::declval<int>()]), hamon::tuple<int&, char&>>::value, "");
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
	auto it = cv.begin();
	VERIFY(it[0] == hamon::make_tuple(1));
	VERIFY(it[1] == hamon::make_tuple(2));
	VERIFY(it[2] == hamon::make_tuple(3));
	VERIFY(it[3] == hamon::make_tuple(4));
	VERIFY(it[4] == hamon::make_tuple(5));

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

	VERIFY(it[ 0] == hamon::make_tuple(1, 'a', 0.5f));
	VERIFY(it[ 1] == hamon::make_tuple(1, 'a', 1.5f));
	VERIFY(it[ 2] == hamon::make_tuple(1, 'a', 2.5f));
	VERIFY(it[ 3] == hamon::make_tuple(1, 'b', 0.5f));
	VERIFY(it[ 4] == hamon::make_tuple(1, 'b', 1.5f));
	VERIFY(it[ 5] == hamon::make_tuple(1, 'b', 2.5f));
	VERIFY(it[ 6] == hamon::make_tuple(2, 'a', 0.5f));
	VERIFY(it[ 7] == hamon::make_tuple(2, 'a', 1.5f));
	VERIFY(it[ 8] == hamon::make_tuple(2, 'a', 2.5f));
	VERIFY(it[ 9] == hamon::make_tuple(2, 'b', 0.5f));
	VERIFY(it[10] == hamon::make_tuple(2, 'b', 1.5f));
	VERIFY(it[11] == hamon::make_tuple(2, 'b', 2.5f));
	VERIFY(it[12] == hamon::make_tuple(3, 'a', 0.5f));
	VERIFY(it[13] == hamon::make_tuple(3, 'a', 1.5f));
	VERIFY(it[14] == hamon::make_tuple(3, 'a', 2.5f));
	VERIFY(it[15] == hamon::make_tuple(3, 'b', 0.5f));
	VERIFY(it[16] == hamon::make_tuple(3, 'b', 1.5f));
	VERIFY(it[17] == hamon::make_tuple(3, 'b', 2.5f));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewIteratorSubscriptTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_subscript_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
