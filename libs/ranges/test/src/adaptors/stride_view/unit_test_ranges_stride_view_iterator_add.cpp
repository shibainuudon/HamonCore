/**
 *	@file	unit_test_ranges_stride_view_iterator_add.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	friend constexpr iterator operator+(const iterator& x, difference_type n)
 *	  requires random_access_range<Base>;
 *	friend constexpr iterator operator+(difference_type n, const iterator& x)
 *	  requires random_access_range<Base>;
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
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
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
	auto it1 = sv.begin() + 1;
	auto it2 = 2 + sv.begin();
	VERIFY(*it1 == 3);
	VERIFY(*it2 == 5);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorAddTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_add_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
