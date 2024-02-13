/**
 *	@file	unit_test_ranges_enumerate_view_iterator_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	friend constexpr iterator operator-(const iterator& x, difference_type y)
 *	  requires random_access_range<Base>;
 *	friend constexpr difference_type operator-(const iterator& x, const iterator& y) noexcept;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace iterator_sub_test
{

template <typename T, typename U, typename = void>
struct has_sub
	: public hamon::false_type {};

template <typename T, typename U>
struct has_sub<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
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

	auto it = ev.begin();
	++it;
	++it;
	++it;
	++it;
	auto it1 = it - 1;
	auto it2 = it - 3;
	VERIFY(hamon::adl_get<0>(*it1) == 3);
	VERIFY(hamon::adl_get<1>(*it1) == 17);
	VERIFY(hamon::adl_get<0>(*it2) == 1);
	VERIFY(hamon::adl_get<1>(*it2) == 13);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;

	int a[] = {11,13,15,17,19};
	V v(a);
	EV ev{v};

	auto it = ev.begin();
	++it;
	auto it1 = it;
	++it;
	auto it2 = it;
	++it;
	++it;
	auto it3 = it;
	VERIFY((it1 - it1) ==  0);
	VERIFY((it1 - it2) == -1);
	VERIFY((it1 - it3) == -3);
	VERIFY((it3 - it1) ==  3);
	VERIFY((it3 - it2) ==  2);
	VERIFY((it3 - it3) ==  0);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_sub_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
