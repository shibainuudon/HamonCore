/**
 *	@file	unit_test_ranges_adjacent_view_iterator_sub_assign.cpp
 *
 *	@brief	operator-= のテスト
 *
 *	constexpr iterator& operator-=(difference_type x)
 *	  requires random_access_range<Base>;
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/tuple.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace iterator_sub_assign_test
{

template <typename T, typename = void>
struct has_sub_assign
	: public hamon::false_type {};

template <typename T>
struct has_sub_assign<T, hamon::void_t<decltype(hamon::declval<T>() -= hamon::declval<int>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;

		int a[] = {1,2,3,4,5};
		V v(a);
		AV av{v};

		auto it = av.begin();
		++it;
		++it;
		++it;
		VERIFY(*it == hamon::make_tuple(4,5));
		auto t1 = it -= 2;
		VERIFY(t1 == it);
		VERIFY(*it == hamon::make_tuple(2,3));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewIteratorSubAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_sub_assign_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
