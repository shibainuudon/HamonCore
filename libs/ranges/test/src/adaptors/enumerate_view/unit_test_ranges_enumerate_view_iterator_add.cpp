/**
 *	@file	unit_test_ranges_enumerate_view_iterator_add.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	friend constexpr iterator operator+(const iterator& x, difference_type y)
 *	  requires random_access_range<Base>;
 *	friend constexpr iterator operator+(difference_type x, const iterator& y)
 *	  requires random_access_range<Base>;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
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
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
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
	using EV = hamon::ranges::enumerate_view<V>;

	int a[] = {11,13,15,17,19};
	V v(a);
	EV ev{v};

	auto it1 = ev.begin() + 1;
	auto it2 = 2 + ev.begin();
	VERIFY(hamon::adl_get<0>(*it1) == 1);
	VERIFY(hamon::adl_get<1>(*it1) == 13);
	VERIFY(hamon::adl_get<0>(*it2) == 2);
	VERIFY(hamon::adl_get<1>(*it2) == 15);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorAddTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_add_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
