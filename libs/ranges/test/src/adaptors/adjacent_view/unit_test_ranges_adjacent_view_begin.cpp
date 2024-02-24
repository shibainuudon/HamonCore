/**
 *	@file	unit_test_ranges_adjacent_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin() requires (!simple-view<V>);
 *	constexpr auto begin() const requires range<const V>;
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
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
	// simple_view<V> && range<V const>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");

		using AV = hamon::ranges::adjacent_view<V, 2>;
		static_assert( has_begin<AV&>::value, "");
		static_assert( has_begin<AV const&>::value, "");

		using I  = decltype(hamon::declval<AV&>().begin());
		using CI = decltype(hamon::declval<AV const&>().begin());
		//static_assert(hamon::is_same<I,  AV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CI, AV::iterator<true>>::value, "");
		static_assert(hamon::is_same<I, CI>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<I>,  hamon::tuple<int&, int&>>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<CI>, hamon::tuple<int&, int&>>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		{
			AV av(v);
			auto it = av.begin();
			VERIFY(hamon::adl_get<0>(*it) == 1);
			VERIFY(hamon::adl_get<1>(*it) == 2);
		}
		{
			AV const av(v);
			auto it = av.begin();
			VERIFY(hamon::adl_get<0>(*it) == 1);
			VERIFY(hamon::adl_get<1>(*it) == 2);
		}
	}

	// !simple_view<V> && range<V const>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");

		using AV = hamon::ranges::adjacent_view<V, 3>;
		static_assert( has_begin<AV&>::value, "");
		static_assert( has_begin<AV const&>::value, "");

		using I  = decltype(hamon::declval<AV&>().begin());
		using CI = decltype(hamon::declval<AV const&>().begin());
		//static_assert(hamon::is_same<I,  AV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, AV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<I, CI>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<I>,  hamon::tuple<int&, int&, int&>>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<CI>, hamon::tuple<int const&, int const&, int const&>>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		{
			AV av(v);
			auto it = av.begin();
			VERIFY(hamon::adl_get<0>(*it) == 1);
			VERIFY(hamon::adl_get<1>(*it) == 2);
			VERIFY(hamon::adl_get<2>(*it) == 3);
		}
		{
			AV const av(v);
			auto it = av.begin();
			VERIFY(hamon::adl_get<0>(*it) == 1);
			VERIFY(hamon::adl_get<1>(*it) == 2);
			VERIFY(hamon::adl_get<2>(*it) == 3);
		}
	}

	// simple_view<V> && !range<V const>
	{
		// simple_view<V> && !range<V const> ということは、
		// range<V> も false になってしまう
	}

	// !simple_view<V> && !range<V const>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(!hamon::ranges::range_t<V const>::value, "");

		using AV = hamon::ranges::adjacent_view<V, 1>;
		static_assert( has_begin<AV&>::value, "");
		static_assert(!has_begin<AV const&>::value, "");

		using I = decltype(hamon::declval<AV&>().begin());
		//static_assert(hamon::is_same<I,  AV::iterator<false>>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<I>,  hamon::tuple<int&>>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		{
			AV av(v);
			auto it = av.begin();
			VERIFY(hamon::adl_get<0>(*it) == 1);
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
