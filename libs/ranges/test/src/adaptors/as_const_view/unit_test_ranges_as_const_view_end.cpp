/**
 *	@file	unit_test_ranges_as_const_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires (!simple-view<V>);
 *	constexpr auto end() const requires range<const V>;
 */

#include <hamon/ranges/adaptors/as_const_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/iterator/const_sentinel.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_const_view_test
{
namespace end_test
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
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// simple_view<V> && range<V const>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");

		using CV = hamon::ranges::as_const_view<V>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");

		using ConstSentinel = hamon::const_sentinel<input_iterator_wrapper<int>>;
		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().end()), ConstSentinel>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().end()), ConstSentinel>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		{
			CV cv(v);
			auto sent = cv.end();
			VERIFY(cv.begin() != sent);
		}
		{
			CV const cv(v);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
	}
	
	// !simple_view<V> && range<V const>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");

		using CV = hamon::ranges::as_const_view<V>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");

		using ConstSentinel = hamon::const_sentinel<input_iterator_wrapper<int const>>;
		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().end()), ConstSentinel>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().end()), ConstSentinel>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		{
			CV cv(v);
			auto sent = cv.end();
			VERIFY(cv.begin() != sent);
		}
		{
			CV const cv(v);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
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
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(!hamon::ranges::range_t<V const>::value, "");

		using CV = hamon::ranges::as_const_view<V>;
		static_assert( has_end<CV&>::value, "");
		static_assert(!has_end<CV const&>::value, "");

		using ConstSentinel = hamon::const_sentinel<input_iterator_wrapper<int>>;
		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().end()), ConstSentinel>::value, "");

		int a[] = { 1,2,3 };
		V v(a);
		{
			CV cv(v);
			auto sent = cv.end();
			VERIFY(cv.begin() != sent);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsConstViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace as_const_view_test
}	// namespace hamon_ranges_test
