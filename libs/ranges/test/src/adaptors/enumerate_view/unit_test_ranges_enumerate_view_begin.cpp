/**
 *	@file	unit_test_ranges_enumerate_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin() requires (!simple-view<V>);
 *	constexpr auto begin() const requires range-with-movable-references<const V>;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
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
namespace begin_test
{

template <typename T, typename Iterator, typename Sentinel, typename ConstIterator, typename ConstSentinel>
struct TestView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	HAMON_CXX11_CONSTEXPR TestView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR TestView(T (&arr)[N]) : TestView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR TestView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR Iterator      begin()       noexcept { return Iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR ConstIterator begin() const noexcept { return ConstIterator{m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{m_last}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{m_last}; }
};

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// simple_view<V> && range_with_movable_references<V const>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::range_with_movable_references<V const>, "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_begin<EV&>::value, "");
		static_assert( has_begin<EV const&>::value, "");

		//using I  = decltype(hamon::declval<EV&>().begin());
		//using CI = decltype(hamon::declval<EV const&>().begin());
		//static_assert(hamon::is_same<I,  EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CI, EV::iterator<true>>::value, "");

		int a[] = { 10, 11, 12 };
		V v(a);
		{
			EV ev(v);
			auto it = ev.begin();
			VERIFY(hamon::adl_get<0>(*it) == 0);
			VERIFY(hamon::adl_get<1>(*it) == 10);
		}
		{
			EV const ev(v);
			auto it = ev.begin();
			VERIFY(hamon::adl_get<0>(*it) == 0);
			VERIFY(hamon::adl_get<1>(*it) == 10);
		}
	}

	// !simple_view<V> && range_with_movable_references<V const>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::range_with_movable_references<V const>, "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_begin<EV&>::value, "");
		static_assert( has_begin<EV const&>::value, "");

		//using I  = decltype(hamon::declval<EV&>().begin());
		//using CI = decltype(hamon::declval<EV const&>().begin());
		//static_assert(hamon::is_same<I,  EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, EV::iterator<true>>::value, "");

		int a[] = { 10, 11, 12 };
		V v(a);
		{
			EV ev(v);
			auto it = ev.begin();
			VERIFY(hamon::adl_get<0>(*it) == 0);
			VERIFY(hamon::adl_get<1>(*it) == 10);
		}
		{
			EV const ev(v);
			auto it = ev.begin();
			VERIFY(hamon::adl_get<0>(*it) == 0);
			VERIFY(hamon::adl_get<1>(*it) == 10);
		}
	}

	// simple_view<V> && !range_with_movable_references<V const>
	{
		// simple_view<V> && !range_with_movable_references<V const> ということは、
		// range_with_movable_references<V> も false になってしまうので
		// インスタンス化できない
	}

	// !simple_view<V> && !range_with_movable_references<V const>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert(!hamon::ranges::detail::range_with_movable_references<V const>, "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_begin<EV&>::value, "");
		static_assert(!has_begin<EV const&>::value, "");

		//using I  = decltype(hamon::declval<EV&>().begin());
		//static_assert(hamon::is_same<I,  EV::iterator<false>>::value, "");

		int a[] = { 10, 11, 12 };
		V v(a);
		{
			EV ev(v);
			auto it = ev.begin();
			VERIFY(hamon::adl_get<0>(*it) == 0);
			VERIFY(hamon::adl_get<1>(*it) == 10);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
