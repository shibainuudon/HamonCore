/**
 *	@file	unit_test_ranges_elements_view_iterator_pre_increment.cpp
 *
 *	@brief	前置インクリメントのテスト
 *
 *	constexpr iterator& operator++();
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
namespace iterator_pre_increment_test
{

template <typename T, typename = void>
struct has_pre_increment
	: public hamon::false_type {};

template <typename T>
struct has_pre_increment<T, hamon::void_t<decltype(++hamon::declval<T>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_pre_increment<I&>::value, "");
		static_assert(!has_pre_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_forward_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_pre_increment<I&>::value, "");
		static_assert(!has_pre_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_bidirectional_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_pre_increment<I&>::value, "");
		static_assert(!has_pre_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_random_access_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_pre_increment<I&>::value, "");
		static_assert(!has_pre_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_contiguous_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_pre_increment<I&>::value, "");
		static_assert(!has_pre_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev{v};

		auto it = ev.begin();
		VERIFY(*it == 1);
		auto t1 = ++it;
		VERIFY(*it == 3);
		VERIFY(*t1 == 3);
		auto t2 = ++it;
		VERIFY(*it == 5);
		VERIFY(*t2 == 5);
		VERIFY(it != ev.end());
		VERIFY(++it == ev.end());
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 1>;

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev{v};

		auto it = ev.begin();
		VERIFY(*it == 2);
		auto t1 = ++it;
		VERIFY(*it == 4);
		VERIFY(*t1 == 4);
		auto t2 = ++it;
		VERIFY(*it == 6);
		VERIFY(*t2 == 6);
		VERIFY(it != ev.end());
		VERIFY(++it == ev.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewIteratorPreIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_pre_increment_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
