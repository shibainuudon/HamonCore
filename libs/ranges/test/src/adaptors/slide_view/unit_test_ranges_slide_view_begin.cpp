/**
 *	@file	unit_test_ranges_slide_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin()
 *	  requires (!(simple-view<V> && slide-caches-nothing<const V>));
 *	constexpr auto begin() const requires slide-caches-nothing<const V>;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
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
namespace slide_view_test
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
	// simple_view<V> && slide_caches_nothing<V const>
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::slide_caches_nothing<V const>, "");
		//static_assert(!hamon::ranges::detail::slide_caches_first<V>, "");

		using SV = hamon::ranges::slide_view<V>;
		static_assert( has_begin<SV&>::value, "");
		static_assert( has_begin<SV const&>::value, "");

		using I  = decltype(hamon::declval<SV&>().begin());
		using CI = decltype(hamon::declval<SV const&>().begin());
		//static_assert(hamon::is_same<I,  SV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CI, SV::iterator<true>>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		{
			SV sv(v, 2);
			I it = sv.begin();
			int const expected[] = {1,2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		{
			SV const sv(v, 3);
			CI it = sv.begin();
			int const expected[] = {1,2,3};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
	}

	// !simple_view<V> && slide_caches_nothing<V const>
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int const>,
			random_access_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::slide_caches_nothing<V const>, "");
		//static_assert(!hamon::ranges::detail::slide_caches_first<V>, "");

		using SV = hamon::ranges::slide_view<V>;
		static_assert( has_begin<SV&>::value, "");
		static_assert( has_begin<SV const&>::value, "");

		using I  = decltype(hamon::declval<SV&>().begin());
		using CI = decltype(hamon::declval<SV const&>().begin());
		//static_assert(hamon::is_same<I,  SV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, SV::iterator<true>>::value, "");

		int a[] = {11,12,13,14,15};
		V v(a);
		{
			SV sv(v, 3);
			I it = sv.begin();
			int const expected[] = {11,12,13};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		{
			SV const sv(v, 4);
			CI it = sv.begin();
			int const expected[] = {11,12,13,14};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
	}

	// simple_view<V> && !slide_caches_nothing<V const>
	{
		// slide_caches_first<V>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert( hamon::ranges::detail::slide_caches_first<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_begin<SV&>::value, "");
			static_assert(!has_begin<SV const&>::value, "");

			using I  = decltype(hamon::declval<SV&>().begin());
			//static_assert(hamon::is_same<I,  SV::iterator<false>>::value, "");

			int a[] = {10,20,30,40,50};
			V v(a);
			{
				SV sv(v, 2);
				I it = sv.begin();
				int const expected[] = {10,20};
				VERIFY(hamon::ranges::equal(*it, expected));
			}
		}
		// !slide_caches_first<V>
		{
			using V = TestView<int,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_first<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_begin<SV&>::value, "");
			static_assert(!has_begin<SV const&>::value, "");

			using I  = decltype(hamon::declval<SV&>().begin());
			//static_assert(hamon::is_same<I,  SV::iterator<false>>::value, "");

			int a[] = {10,20,30,40,50};
			V v(a);
			{
				SV sv(v, 3);
				I it = sv.begin();
				int const expected[] = {10,20,30};
				VERIFY(hamon::ranges::equal(*it, expected));
			}
		}
	}

	// !simple_view<V> && !slide_caches_nothing<V const>
	{
		// slide_caches_first<V>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>,
				forward_iterator_wrapper<int const>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert( hamon::ranges::detail::slide_caches_first<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_begin<SV&>::value, "");
			static_assert(!has_begin<SV const&>::value, "");

			using I  = decltype(hamon::declval<SV&>().begin());
			//static_assert(hamon::is_same<I,  SV::iterator<false>>::value, "");

			int a[] = {3,1,4,1,5};
			V v(a);
			{
				SV sv(v, 2);
				I it = sv.begin();
				int const expected[] = {3,1};
				VERIFY(hamon::ranges::equal(*it, expected));
			}
		}
		// !slide_caches_first<V>
		{
			using V = TestView<int,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int const>,
				bidirectional_iterator_wrapper<int const>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_first<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_begin<SV&>::value, "");
			static_assert(!has_begin<SV const&>::value, "");

			using I  = decltype(hamon::declval<SV&>().begin());
			//static_assert(hamon::is_same<I,  SV::iterator<false>>::value, "");

			int a[] = {3,1,4,1,5};
			V v(a);
			{
				SV sv(v, 3);
				I it = sv.begin();
				int const expected[] = {3,1,4};
				VERIFY(hamon::ranges::equal(*it, expected));
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
