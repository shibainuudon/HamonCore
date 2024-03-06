/**
 *	@file	unit_test_ranges_stride_view_iterator_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr decltype(auto) operator[](difference_type n) const
 *	  requires random_access_range<Base>
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
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
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int&>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), int&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), int&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_random_access_view<int>;
	using SV = hamon::ranges::stride_view<V>;

	int a[] = {1,2,3,4,5,6};
	V v(a);
	SV sv(v, 2);
	auto it = sv.begin();
	VERIFY(it[0] == 1);
	VERIFY(it[1] == 3);
	VERIFY(it[2] == 5);

	VERIFY(a[2] == 3);
	it[1] = 42;
	VERIFY(a[2] == 42);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorSubscriptTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_subscript_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
