/**
 *	@file	unit_test_ranges_stride_view_iterator_post_increment.cpp
 *
 *	@brief	後置インクリメントのテスト
 *
 *	constexpr void operator++(int);
 *	constexpr iterator operator++(int) requires forward_range<Base>;
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
namespace iterator_post_increment_test
{

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
		using V = test_input_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_post_increment<I&>::value, "");
		static_assert(!has_post_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_input_view<int>;
		using SV = hamon::ranges::stride_view<V>;

		int a[] = {1,2,3,4,5,6};
		V v(a);
		SV sv(v, 2);
		auto it = sv.begin();
		VERIFY(*it == 1);
		it++;
		VERIFY(*it == 3);
		it++;
		VERIFY(*it == 5);
		it++;
		VERIFY(it == sv.end());
	}
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::stride_view<V>;

		int a[] = {1,2,3,4,5,6};
		V v(a);
		SV sv(v, 2);
		auto it = sv.begin();
		VERIFY(*it == 1);
		auto t1 = it++;
		VERIFY(*t1 == 1);
		VERIFY(*it == 3);
		auto t2 = it++;
		VERIFY(*t2 == 3);
		VERIFY(*it == 5);
		VERIFY(it++ != sv.end());
		VERIFY(it == sv.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_post_increment_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
