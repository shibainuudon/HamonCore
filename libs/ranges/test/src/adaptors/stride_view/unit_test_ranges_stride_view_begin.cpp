/**
 *	@file	unit_test_ranges_stride_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin() requires (!simple-view<V>);
 *	constexpr auto begin() const requires range<const V>;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
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

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_begin<SV&>::value, "");
		static_assert( has_begin<SV const&>::value, "");

		using I  = decltype(hamon::declval<SV&>().begin());
		using CI = decltype(hamon::declval<SV const&>().begin());
		//static_assert(hamon::is_same<I,  SV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CI, SV::iterator<true>>::value, "");
		static_assert(hamon::is_same<I, CI>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		{
			SV sv(v, 1);
			auto it = sv.begin();
			VERIFY(*it == 1);
		}
		{
			SV const sv(v, 2);
			auto it = sv.begin();
			VERIFY(*it == 1);
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

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_begin<SV&>::value, "");
		static_assert( has_begin<SV const&>::value, "");

		using I  = decltype(hamon::declval<SV&>().begin());
		using CI = decltype(hamon::declval<SV const&>().begin());
		//static_assert(hamon::is_same<I,  SV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, SV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<I, CI>::value, "");

		int a[] = {11,12,13,14,15};
		V v(a);
		{
			SV sv(v, 3);
			auto it = sv.begin();
			VERIFY(*it == 11);
		}
		{
			SV const sv(v, 4);
			auto it = sv.begin();
			VERIFY(*it == 11);
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

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_begin<SV&>::value, "");
		static_assert(!has_begin<SV const&>::value, "");

		//using I  = decltype(hamon::declval<SV&>().begin());
		//static_assert(hamon::is_same<I,  SV::iterator<false>>::value, "");

		int a[] = {21,22,23,24,25};
		V v(a);
		{
			SV sv(v, 5);
			auto it = sv.begin();
			VERIFY(*it == 21);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
