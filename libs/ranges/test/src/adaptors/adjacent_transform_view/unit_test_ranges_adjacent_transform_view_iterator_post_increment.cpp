/**
 *	@file	unit_test_ranges_adjacent_transform_view_iterator_post_increment.cpp
 *
 *	@brief	後置インクリメントのテスト
 *
 *	constexpr iterator operator++(int);
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace iterator_post_increment_test
{

struct F
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

template <typename T, typename = void>
struct has_post_increment
	: public hamon::false_type {};

template <typename T>
struct has_post_increment<T, hamon::void_t<decltype(hamon::declval<T>()++)>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		int a[] = {3,1,4,9};
		V v(a);
		AV av{v, F{}};

		auto it = av.begin();
		VERIFY(*it == 4);
		auto t1 = it++;
		VERIFY(t1 != it);
		VERIFY(*t1 == 4);
		VERIFY(*it == 5);
		auto t2 = it++;
		VERIFY(t2 != it);
		VERIFY(*t2 == 5);
		VERIFY(*it == 13);
		VERIFY(it++ != av.end());
		VERIFY(it   == av.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_post_increment_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
