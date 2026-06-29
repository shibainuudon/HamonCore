/**
 *	@file	unit_test_ranges_concat_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires (!(simple-view<Views> && ...));
 *	constexpr auto end() const
 *		requires (range<const Views> && ...) && concatable<const Views...>;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
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

struct A
{
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	//  (simple-view<Views> && ...) &&
	//  (range<const Views> && ...) &&
	//  concatable<const Views...> &&
	//  all-forward<is-const, Views...> &&
	//  common_range<maybe-const<is-const, Views...[N - 1]>>
	{
		using V1 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
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
		static_assert( hamon::ranges::forward_range<V1>, "");
		static_assert( hamon::ranges::forward_range<V2>, "");
		static_assert( hamon::ranges::forward_range<V1 const>, "");
		static_assert( hamon::ranges::forward_range<V2 const>, "");
		static_assert( hamon::ranges::common_range<V2>, "");
		static_assert( hamon::ranges::common_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");
		static_assert( has_cend<CV&>::value, "");
		static_assert( has_cend<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		//static_assert(hamon::is_same<S,  CV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CS, CV::iterator<true>>::value, "");
		static_assert(hamon::is_same<S, CS>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
		{
			CV const cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// !(simple-view<Views> && ...) &&
	//  (range<const Views> && ...) &&
	//  concatable<const Views...> &&
	//  all-forward<is-const, Views...> &&
	//  common_range<maybe-const<is-const, Views...[N - 1]>>
	{
		using V1 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
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
		static_assert( hamon::ranges::forward_range<V1>, "");
		static_assert( hamon::ranges::forward_range<V2>, "");
		static_assert( hamon::ranges::forward_range<V1 const>, "");
		static_assert( hamon::ranges::forward_range<V2 const>, "");
		static_assert( hamon::ranges::common_range<V2>, "");
		static_assert( hamon::ranges::common_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");
		static_assert( has_cend<CV&>::value, "");
		static_assert( has_cend<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		//static_assert(hamon::is_same<S,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CS, CV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<S, CS>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
		{
			CV const cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// !(simple-view<Views> && ...) &&
	//  (range<const Views> && ...) &&
	//  concatable<const Views...> &&
	// !all-forward<is-const, Views...> &&
	//  common_range<maybe-const<is-const, Views...[N - 1]>>
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
		static_assert(!hamon::ranges::forward_range<V1>, "");
		static_assert( hamon::ranges::forward_range<V2>, "");
		static_assert(!hamon::ranges::forward_range<V1 const>, "");
		static_assert( hamon::ranges::forward_range<V2 const>, "");
		static_assert( hamon::ranges::common_range<V2>, "");
		static_assert( hamon::ranges::common_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");
		static_assert( has_cend<CV&>::value, "");
		static_assert( has_cend<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		static_assert(hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<CS, hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<S, CS>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
		{
			CV const cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// !(simple-view<Views> && ...) &&
	//  (range<const Views> && ...) &&
	// !concatable<const Views...>
	{
		using V1 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
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
		static_assert( has_end<CV&>::value, "");
		static_assert(!has_end<CV const&>::value, "");
		static_assert( has_cend<CV&>::value, "");
		static_assert(!has_cend<CV const&>::value, "");

		//using S = decltype(hamon::declval<CV&>().end());
		//static_assert(hamon::is_same<S, CV::iterator<false>>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	// !(simple-view<Views> && ...) &&
	// !(range<const Views> && ...)
	{
		using V1 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
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
		static_assert( has_end<CV&>::value, "");
		static_assert(!has_end<CV const&>::value, "");
		static_assert( has_cend<CV&>::value, "");
		static_assert(!has_cend<CV const&>::value, "");

		//using S = decltype(hamon::declval<CV&>().end());
		//static_assert(hamon::is_same<S, CV::iterator<false>>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	int p[]{ 37, 42, 69 };
	auto q = { 19937, 1729 };
	auto cat = hamon::ranges::views::concat(p, q);
	static_assert(!hamon::is_same<hamon::default_sentinel_t, decltype(cat.end())>::value, "");
	VERIFY(cat.end()[-1] == 1729);
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace end_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
