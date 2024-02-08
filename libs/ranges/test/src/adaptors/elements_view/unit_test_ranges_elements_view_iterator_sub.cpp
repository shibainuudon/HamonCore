/**
 *	@file	unit_test_ranges_elements_view_iterator_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	friend constexpr iterator operator-(const iterator& x, difference_type y)
 *	  requires random_access_range<Base>;
 *	friend constexpr difference_type operator-(const iterator& x, const iterator& y)
 *	  requires sized_sentinel_for<iterator_t<Base>, iterator_t<Base>>;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
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
namespace elements_view_test
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
		using Tuple = hamon::tuple<int, long const>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_forward_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_bidirectional_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert(!has_sub<I const&, I const&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_random_access_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_sub<I const&, int>::value, "");
		static_assert(!has_sub<int, I const&>::value, "");
		static_assert( has_sub<I const&, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_contiguous_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
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
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_random_access_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev{v};

		auto it1 = ev.begin() + 2;
		auto it2 = it1 - 1;
		auto it3 = it1 - 2;
		VERIFY(*it1 == 5);
		VERIFY(*it2 == 3);
		VERIFY(*it3 == 1);
		VERIFY((it1 - it1) ==  0);
		VERIFY((it1 - it2) ==  1);
		VERIFY((it1 - it3) ==  2);
		VERIFY((it3 - it1) == -2);
		VERIFY((it3 - it2) == -1);
		VERIFY((it3 - it3) ==  0);
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_random_access_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 1>;

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev{v};

		auto it1 = ev.begin() + 2;
		auto it2 = it1 - 1;
		auto it3 = it1 - 2;
		VERIFY(*it1 == 6);
		VERIFY(*it2 == 4);
		VERIFY(*it3 == 2);
		VERIFY((it1 - it1) ==  0);
		VERIFY((it1 - it2) ==  1);
		VERIFY((it1 - it3) ==  2);
		VERIFY((it3 - it1) == -2);
		VERIFY((it3 - it2) == -1);
		VERIFY((it3 - it3) ==  0);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewIteratorSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_sub_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
