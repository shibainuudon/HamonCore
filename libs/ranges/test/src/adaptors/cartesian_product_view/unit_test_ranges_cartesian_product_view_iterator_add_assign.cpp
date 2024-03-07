/**
 *	@file	unit_test_ranges_cartesian_product_view_iterator_add_assign.cpp
 *
 *	@brief	operator+= のテスト
 *
 *	constexpr iterator& operator+=(difference_type x)
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
namespace iterator_add_assign_test
{

template <typename T, typename = void>
struct has_add_assign
	: public hamon::false_type {};

template <typename T>
struct has_add_assign<T, hamon::void_t<decltype(hamon::declval<T>() += hamon::declval<int>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		using I = decltype(hamon::declval<CV&>().begin());
		static_assert( has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
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
	VERIFY(*it == hamon::make_tuple(1));
	auto& t1 = (it += 2);
	VERIFY(&t1 == &it);
	VERIFY(*it == hamon::make_tuple(3));
	auto& t2 = (it += -1);
	VERIFY(&t2 == &it);
	VERIFY(*it == hamon::make_tuple(2));
	it += 3;
	VERIFY(*it == hamon::make_tuple(5));
	it += 0;
	VERIFY(*it == hamon::make_tuple(5));

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
	VERIFY(*it == hamon::make_tuple(1, 'a', 0.5f));
	it += 2;
	VERIFY(*it == hamon::make_tuple(1, 'a', 2.5f));
	it += 4;
	VERIFY(*it == hamon::make_tuple(2, 'a', 0.5f));
	it += 10;
	VERIFY(*it == hamon::make_tuple(3, 'b', 1.5f));
	it += 0;
	VERIFY(*it == hamon::make_tuple(3, 'b', 1.5f));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewIteratorAddAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_add_assign_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
