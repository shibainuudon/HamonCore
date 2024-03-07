/**
 *	@file	unit_test_ranges_cartesian_product_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr iterator<false> end()
 *	  requires ((!simple-view<First> || ... || !simple-view<Vs>) &&
 *	    cartesian-product-is-common<First, Vs...>);
 *
 *	constexpr iterator<true> end() const
 *	  requires cartesian-product-is-common<const First, const Vs...>;
 *
 *	constexpr default_sentinel_t end() const noexcept;
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
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
	// (simple-view<Views> && ...) && cartesian_product_is_common<Views...> && cartesian_product_is_common<Views const...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V1>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V1>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V1 const>, "");

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		//static_assert(hamon::is_same<S,  CV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CS, CV::iterator<true>>::value, "");
		static_assert(hamon::is_same<S, CS>::value, "");
		static_assert(!hamon::is_same<S, hamon::default_sentinel_t>::value, "");

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

	// (simple-view<Views> && ...) && cartesian_product_is_common<Views...> && !cartesian_product_is_common<Views const...>
	{
		// この条件を満たすことはできない
	}

	// (simple-view<Views> && ...) && !cartesian_product_is_common<Views...> && cartesian_product_is_common<Views const...>
	{
		// この条件を満たすことはできない
	}

	// (simple-view<Views> && ...) && !cartesian_product_is_common<Views...> && !cartesian_product_is_common<Views const...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			test_sentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int>,
			test_sentinel<input_iterator_wrapper<int>>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V1>::value, "");
		//static_assert(!hamon::ranges::cartesian_product_is_common<V1>, "");
		//static_assert(!hamon::ranges::cartesian_product_is_common<V1 const>, "");

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		static_assert(hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<CS, hamon::default_sentinel_t>::value, "");

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

	// (!simple-view<Views> && ...) && cartesian_product_is_common<Views...> && cartesian_product_is_common<Views const...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V1>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V1 const>, "");

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		//static_assert(hamon::is_same<S,  CV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CS, CV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<S, CS>::value, "");
		static_assert(!hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
		static_assert(!hamon::is_same<CS, hamon::default_sentinel_t>::value, "");

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

	// (!simple-view<Views> && ...) && cartesian_product_is_common<Views...> && !cartesian_product_is_common<Views const...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			test_sentinel<input_iterator_wrapper<int const>>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V1>, "");
		//static_assert(!hamon::ranges::cartesian_product_is_common<V1 const>, "");

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		//static_assert(hamon::is_same<S,  CV::iterator<false>>::value, "");
		static_assert(hamon::is_same<CS, hamon::default_sentinel_t>::value, "");
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

	// (!simple-view<Views> && ...) && !cartesian_product_is_common<Views...> && cartesian_product_is_common<Views const...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			test_sentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
		//static_assert(!hamon::ranges::cartesian_product_is_common<V1>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V1 const>, "");

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		//static_assert(hamon::is_same<S,  CV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CS, CV::iterator<true>>::value, "");
		static_assert(hamon::is_same<S, CS>::value, "");
		static_assert(!hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
		static_assert(!hamon::is_same<CS, hamon::default_sentinel_t>::value, "");

		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv(v1, v2);
			CV const& ccv = cv;
			auto sent = cv.end();
			VERIFY(sent != ccv.begin());
		}
		{
			CV const cv(v1, v2);
			auto sent = cv.end();
			VERIFY(sent != cv.begin());
		}
	}

	// (!simple-view<Views> && ...) && !cartesian_product_is_common<Views...> && !cartesian_product_is_common<Views const...>
	{
		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			test_sentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int const>,
			test_sentinel<input_iterator_wrapper<int const>>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
		//static_assert(!hamon::ranges::cartesian_product_is_common<V1>, "");
		//static_assert(!hamon::ranges::cartesian_product_is_common<V1 const>, "");

		using V2 = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2>, "");
		//static_assert( hamon::ranges::cartesian_product_is_common<V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_end<CV&>::value, "");
		static_assert( has_end<CV const&>::value, "");

		using S  = decltype(hamon::declval<CV&>().end());
		using CS = decltype(hamon::declval<CV const&>().end());
		static_assert(hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
		static_assert(hamon::is_same<CS, hamon::default_sentinel_t>::value, "");

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

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
