/**
 *	@file	unit_test_ranges_enumerate_view_iterator_add_assign.cpp
 *
 *	@brief	operator+= のテスト
 *
 *	constexpr iterator& operator+=(difference_type x)
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
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_random_access_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;

		int a[] = {10,20,30};
		V v(a);
		EV ev{v};

		auto it = ev.begin();
		VERIFY(hamon::adl_get<0>(*it) == 0);
		VERIFY(hamon::adl_get<1>(*it) == 10);
		auto t1 = (it += 2);
		VERIFY(t1 == it);
		VERIFY(hamon::adl_get<0>(*it) == 2);
		VERIFY(hamon::adl_get<1>(*it) == 30);
		VERIFY((it += 1) == ev.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorAddAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_add_assign_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
