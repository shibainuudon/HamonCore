/**
 *	@file	unit_test_ranges_chunk_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	input_range:
 *	constexpr outer-iterator begin();
 *
 *	forward_range:
 *	constexpr auto begin() requires (!simple-view<V>);
 *	constexpr auto begin() const requires forward_range<const V>;
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_view_test
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
	// input_range

	int a[] = {0,1,2,3,4,5,6,7,8,9};

	using V = test_input_view<int>;
	V v(a);

	using CV = hamon::ranges::chunk_view<V>;
	static_assert( has_begin<CV&>::value, "");
	static_assert(!has_begin<CV const&>::value, "");

	CV cv(v, 3);
	auto it = cv.begin();

	int const expected[] = {0,1,2};
	VERIFY(hamon::ranges::equal(*it, expected));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// forward_range

	// simple_view<V> && forward_range<const V>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::forward_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_begin<CV&>::value, "");
		static_assert( has_begin<CV const&>::value, "");

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");
		static_assert(hamon::is_same<I, CI>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		{
			CV cv(v, 2);
			auto it = cv.begin();

			int const expected[] = {1,2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		{
			CV const cv(v, 3);
			auto it = cv.begin();

			int const expected[] = {1,2,3};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
	}

	// !simple_view<V> && forward_range<const V>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::forward_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_begin<CV&>::value, "");
		static_assert( has_begin<CV const&>::value, "");

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<I, CI>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		{
			CV cv(v, 2);
			auto it = cv.begin();

			int const expected[] = {1,2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		{
			CV const cv(v, 3);
			auto it = cv.begin();

			int const expected[] = {1,2,3};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
	}

	// simple_view<V> && !forward_range<const V>
	{
		// simple_view<V> && !forward_range<V const> ということは、
		// forward_range<V> も false になってしまう
	}

	// !simple_view<V> && !forward_range<const V>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(!hamon::ranges::forward_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_begin<CV&>::value, "");
		static_assert(!has_begin<CV const&>::value, "");

		//using I  = decltype(hamon::declval<CV&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		{
			CV cv(v, 2);
			auto it = cv.begin();

			int const expected[] = {1,2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace begin_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
