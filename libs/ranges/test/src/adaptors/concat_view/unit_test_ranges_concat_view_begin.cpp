/**
 *	@file	unit_test_ranges_concat_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr iterator<false> begin() requires (!(simple-view<Views> && ...));
 *	constexpr iterator<true> begin() const
 *		requires (range<const Views> && ...) && concatable<const Views...>;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
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

struct A
{
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	//  (simple-view<Views> && ...) &&
	//  (range<const Views> && ...) &&
	//  concatable<const Views...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;

		static_assert( hamon::ranges::detail::simple_view<V1>, "");
		static_assert( hamon::ranges::detail::simple_view<V2>, "");
		static_assert( hamon::ranges::range<V1 const>, "");
		static_assert( hamon::ranges::range<V2 const>, "");
		static_assert( hamon::ranges::detail::concatable<V1 const, V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_begin<CV&>::value, "");
		static_assert( has_begin<CV const&>::value, "");
		static_assert( has_cbegin<CV&>::value, "");
		static_assert( has_cbegin<CV const&>::value, "");

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");
		static_assert(hamon::is_same<I, CI>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto it = cv.begin();
			VERIFY(*it == 1);
		}
		{
			CV const cv(v1, v2);
			auto it = cv.begin();
			VERIFY(*it == 1);
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// !(simple-view<Views> && ...) &&
	//  (range<const Views> && ...) &&
	//  concatable<const Views...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int const>
		>;

		static_assert( hamon::ranges::detail::simple_view<V1>, "");
		static_assert(!hamon::ranges::detail::simple_view<V2>, "");
		static_assert( hamon::ranges::range<V1 const>, "");
		static_assert( hamon::ranges::range<V2 const>, "");
		static_assert( hamon::ranges::detail::concatable<V1 const, V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_begin<CV&>::value, "");
		static_assert( has_begin<CV const&>::value, "");
		static_assert( has_cbegin<CV&>::value, "");
		static_assert( has_cbegin<CV const&>::value, "");

		using I  = decltype(hamon::declval<CV&>().begin());
		using CI = decltype(hamon::declval<CV const&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, CV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<I, CI>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto it = cv.begin();
			VERIFY(*it == 1);
		}
		{
			CV const cv(v1, v2);
			auto it = cv.begin();
			VERIFY(*it == 1);
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// !(simple-view<Views> && ...) &&
	//  (range<const Views> && ...) &&
	// !concatable<const Views...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<A>,
			forward_iterator_wrapper<A>
		>;

		static_assert( hamon::ranges::detail::simple_view<V1>, "");
		static_assert(!hamon::ranges::detail::simple_view<V2>, "");
		static_assert( hamon::ranges::range<V1 const>, "");
		static_assert( hamon::ranges::range<V2 const>, "");
		static_assert(!hamon::ranges::detail::concatable<V1 const, V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_begin<CV&>::value, "");
		static_assert(!has_begin<CV const&>::value, "");
		static_assert( has_cbegin<CV&>::value, "");
		static_assert(!has_cbegin<CV const&>::value, "");

		//using I = decltype(hamon::declval<CV&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto it = cv.begin();
			VERIFY(*it == 1);
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// !(simple-view<Views> && ...) &&
	// !(range<const Views> && ...)
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int>
		>;

		static_assert( hamon::ranges::detail::simple_view<V1>, "");
		static_assert(!hamon::ranges::detail::simple_view<V2>, "");
		static_assert( hamon::ranges::range<V1 const>, "");
		static_assert(!hamon::ranges::range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_begin<CV&>::value, "");
		static_assert(!has_begin<CV const&>::value, "");
		static_assert( has_cbegin<CV&>::value, "");
		static_assert(!has_cbegin<CV const&>::value, "");

		//using I = decltype(hamon::declval<CV&>().begin());
		//static_assert(hamon::is_same<I,  CV::iterator<false>>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto it = cv.begin();
			VERIFY(*it == 1);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace begin_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
