/**
 *	@file	unit_test_ranges_adjacent_transform_view_iterator_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr decltype(auto) operator[](difference_type n) const
 *	  requires random_access_range<Base>;
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
namespace iterator_subscript_test
{

struct F
{
	template <typename T>
	constexpr T& operator()(T& x) const { return x; }

	constexpr int operator()(int x, int y) const { return x + y; }
};

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
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int>::value, "");
	}
	{
		using V = test_contiguous_view<int const>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int>::value, "");
	}


	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int&>::value, "");
	}
	{
		using V = test_contiguous_view<int const>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int const&>::value, "");
	}
	{
		using V = test_random_access_view<char>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), char&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), char&>::value, "");
	}
	{
		using V = test_contiguous_view<float const>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), float const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), float const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v, F{}};

		auto it = av.begin();
		VERIFY(it[0] == 3);
		VERIFY(it[1] == 5);
		VERIFY(it[2] == 7);
	}
	{
		using V = test_random_access_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 1>;

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v, F{}};

		auto it = av.begin();
		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);
		VERIFY(it[3] == 4);

		it[1] = 10;

		VERIFY(a[0] == 1);
		VERIFY(a[1] == 10);
		VERIFY(a[2] == 3);
		VERIFY(a[3] == 4);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewIteratorSubscriptTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_subscript_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
