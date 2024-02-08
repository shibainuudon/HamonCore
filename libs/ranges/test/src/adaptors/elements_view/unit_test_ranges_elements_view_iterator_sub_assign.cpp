/**
 *	@file	unit_test_ranges_elements_view_iterator_sub_assign.cpp
 *
 *	@brief	operator-= のテスト
 *
 *	constexpr iterator& operator-=(difference_type x)
 *	  requires random_access_range<Base>;
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
namespace iterator_sub_assign_test
{

template <typename T, typename = void>
struct has_sub_assign
	: public hamon::false_type {};

template <typename T>
struct has_sub_assign<T, hamon::void_t<decltype(hamon::declval<T>() -= hamon::declval<int>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_forward_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_bidirectional_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_random_access_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_contiguous_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert( has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
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

		auto it = ev.begin();
		++it;
		++it;
		VERIFY(*it == 5);
		auto t1 = (it -= 2);
		VERIFY(*it == 1);
		VERIFY(*t1 == 1);
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

		auto it = ev.begin();
		++it;
		++it;
		VERIFY(*it == 6);
		auto t1 = (it -= 2);
		VERIFY(*it == 2);
		VERIFY(*t1 == 2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewIteratorSubAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_sub_assign_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
