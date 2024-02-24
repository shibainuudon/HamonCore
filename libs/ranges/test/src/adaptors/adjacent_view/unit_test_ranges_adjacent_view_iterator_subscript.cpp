/**
 *	@file	unit_test_ranges_adjacent_view_iterator_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr auto operator[](difference_type n) const
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
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		using Tuple = hamon::tuple<int&, int&>;
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), Tuple>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), Tuple>::value, "");
	}
	{
		using V = test_contiguous_view<int const>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		using Tuple = hamon::tuple<int const&, int const&>;
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), Tuple>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), Tuple>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 3>;
		using I = decltype(hamon::declval<AV&>().begin());
		using Tuple = hamon::tuple<int&, int&, int&>;
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), Tuple>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), Tuple>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 4>;
		using I = decltype(hamon::declval<AV&>().begin());
		using Tuple = hamon::tuple<int&, int&, int&, int&>;
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), Tuple>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), Tuple>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v};

		auto it = av.begin();
		VERIFY(it[0] == hamon::make_tuple(1,2));
		VERIFY(it[1] == hamon::make_tuple(2,3));
		VERIFY(it[2] == hamon::make_tuple(3,4));

		it[1] = hamon::make_tuple(10, 11);
		VERIFY(a[0] == 1);
		VERIFY(a[1] == 10);
		VERIFY(a[2] == 11);
		VERIFY(a[3] == 4);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewIteratorSubscriptTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_subscript_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
