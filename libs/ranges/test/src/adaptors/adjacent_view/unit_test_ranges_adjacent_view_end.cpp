/**
 *	@file	unit_test_ranges_adjacent_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires (!simple-view<V>);
 *	constexpr auto end() const requires range<const V>;
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
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
namespace adjacent_view_test
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

	HAMON_CXX14_CONSTEXPR Iterator      begin()       noexcept { return Iterator {m_first}; }
	HAMON_CXX11_CONSTEXPR ConstIterator begin() const noexcept { return ConstIterator {m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel {m_last}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel {m_last}; }
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
		// common_range<V> && common_range<V const>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");
			static_assert( hamon::ranges::common_range_t<V const>::value, "");

			using AV = hamon::ranges::adjacent_view<V, 2>;
			static_assert( has_end<AV&>::value, "");
			static_assert( has_end<AV const&>::value, "");

			using S  = decltype(hamon::declval<AV&>().end());
			using CS = decltype(hamon::declval<AV const&>().end());
			//static_assert( hamon::is_same<S,  AV::iterator<true>>::value, "");
			//static_assert( hamon::is_same<CS, AV::iterator<true>>::value, "");
			static_assert( hamon::is_same<S, CS>::value, "");

			using I = decltype(hamon::declval<AV&>().begin());
			static_assert( hamon::is_same<S, I>::value, "");

			int a[] = {1,2,3,4};
			V v(a);
			{
				AV av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
			{
				AV const av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
		}

		// !common_range<V> && !common_range<V const>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::common_range_t<V const>::value, "");

			using AV = hamon::ranges::adjacent_view<V, 2>;
			static_assert( has_end<AV&>::value, "");
			static_assert( has_end<AV const&>::value, "");

			using S  = decltype(hamon::declval<AV&>().end());
			using CS = decltype(hamon::declval<AV const&>().end());
			//static_assert( hamon::is_same<S,  AV::sentinel<true>>::value, "");
			//static_assert( hamon::is_same<CS, AV::sentinel<true>>::value, "");
			static_assert( hamon::is_same<S, CS>::value, "");

			using I = decltype(hamon::declval<AV&>().begin());
			static_assert(!hamon::is_same<S, I>::value, "");

			int a[] = {1,2,3,4};
			V v(a);
			{
				AV av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
			{
				AV const av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
		}
	}

	// !simple_view<V> && range<V const>
	{
		// common_range<V> && common_range<V const>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>,
				forward_iterator_wrapper<int const>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");
			static_assert( hamon::ranges::common_range_t<V const>::value, "");

			using AV = hamon::ranges::adjacent_view<V, 2>;
			static_assert( has_end<AV&>::value, "");
			static_assert( has_end<AV const&>::value, "");

			using S  = decltype(hamon::declval<AV&>().end());
			using CS = decltype(hamon::declval<AV const&>().end());
			//static_assert( hamon::is_same<S,  AV::iterator<false>>::value, "");
			//static_assert( hamon::is_same<CS, AV::iterator<true>>::value, "");
			static_assert(!hamon::is_same<S, CS>::value, "");

			using I = decltype(hamon::declval<AV&>().begin());
			using CI = decltype(hamon::declval<AV const&>().begin());
			static_assert( hamon::is_same<S, I>::value, "");
			static_assert( hamon::is_same<CS, CI>::value, "");

			int a[] = {1,2,3,4};
			V v(a);
			{
				AV av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
			{
				AV const av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
		}

		// !common_range<V> && common_range<V const>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int const>,
				forward_iterator_wrapper<int const>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");
			static_assert( hamon::ranges::common_range_t<V const>::value, "");

			using AV = hamon::ranges::adjacent_view<V, 2>;
			static_assert( has_end<AV&>::value, "");
			static_assert( has_end<AV const&>::value, "");

			using S  = decltype(hamon::declval<AV&>().end());
			using CS = decltype(hamon::declval<AV const&>().end());
			//static_assert( hamon::is_same<S,  AV::sentinel<false>>::value, "");
			//static_assert( hamon::is_same<CS, AV::iterator<true>>::value, "");
			static_assert(!hamon::is_same<S, CS>::value, "");

			using I = decltype(hamon::declval<AV&>().begin());
			using CI = decltype(hamon::declval<AV const&>().begin());
			static_assert(!hamon::is_same<S, I>::value, "");
			static_assert( hamon::is_same<CS, CI>::value, "");

			int a[] = {1,2,3,4};
			V v(a);
			{
				AV av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
			{
				AV const av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
		}

		// common_range<V> && !common_range<V const>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>,
				test_sentinel<forward_iterator_wrapper<int const>>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::common_range_t<V const>::value, "");

			using AV = hamon::ranges::adjacent_view<V, 2>;
			static_assert( has_end<AV&>::value, "");
			static_assert( has_end<AV const&>::value, "");

			using S  = decltype(hamon::declval<AV&>().end());
			using CS = decltype(hamon::declval<AV const&>().end());
			//static_assert( hamon::is_same<S,  AV::iterator<false>>::value, "");
			//static_assert( hamon::is_same<CS, AV::sentinel<true>>::value, "");
			static_assert(!hamon::is_same<S, CS>::value, "");

			using I = decltype(hamon::declval<AV&>().begin());
			using CI = decltype(hamon::declval<AV const&>().begin());
			static_assert( hamon::is_same<S, I>::value, "");
			static_assert(!hamon::is_same<CS, CI>::value, "");

			int a[] = {1,2,3,4};
			V v(a);
			{
				AV av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
			{
				AV const av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
		}

		// !common_range<V> && !common_range<V const>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int const>,
				test_sentinel<forward_iterator_wrapper<int const>>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::common_range_t<V const>::value, "");

			using AV = hamon::ranges::adjacent_view<V, 2>;
			static_assert( has_end<AV&>::value, "");
			static_assert( has_end<AV const&>::value, "");

			using S  = decltype(hamon::declval<AV&>().end());
			using CS = decltype(hamon::declval<AV const&>().end());
			//static_assert( hamon::is_same<S,  AV::sentinel<false>>::value, "");
			//static_assert( hamon::is_same<CS, AV::sentinel<true>>::value, "");
			static_assert(!hamon::is_same<S, CS>::value, "");

			using I = decltype(hamon::declval<AV&>().begin());
			using CI = decltype(hamon::declval<AV const&>().begin());
			static_assert(!hamon::is_same<S, I>::value, "");
			static_assert(!hamon::is_same<CS, CI>::value, "");

			int a[] = {1,2,3,4};
			V v(a);
			{
				AV av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
			{
				AV const av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
		}
	}

	// simple_view<V> && !range<V const>
	{
		// simple_view<V> && !range<V const> ということは、
		// range<V> も false になってしまう
	}

	// !simple_view<V> && !range<V const>
	{
		// common_range<V> && !common_range<V const>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>,
				forward_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::range_t<V const>::value, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::common_range_t<V const>::value, "");

			using AV = hamon::ranges::adjacent_view<V, 2>;
			static_assert( has_end<AV&>::value, "");
			static_assert(!has_end<AV const&>::value, "");

			using S  = decltype(hamon::declval<AV&>().end());
			//static_assert( hamon::is_same<S,  AV::iterator<false>>::value, "");

			using I = decltype(hamon::declval<AV&>().begin());
			static_assert( hamon::is_same<S, I>::value, "");

			int a[] = {1,2,3,4};
			V v(a);
			{
				AV av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
		}

		// !common_range<V> && !common_range<V const>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int const>,
				forward_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::range_t<V const>::value, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::common_range_t<V const>::value, "");

			using AV = hamon::ranges::adjacent_view<V, 2>;
			static_assert( has_end<AV&>::value, "");
			static_assert(!has_end<AV const&>::value, "");

			using S  = decltype(hamon::declval<AV&>().end());
			//static_assert( hamon::is_same<S,  AV::sentinel<false>>::value, "");

			using I = decltype(hamon::declval<AV&>().begin());
			static_assert(!hamon::is_same<S, I>::value, "");

			int a[] = {1,2,3,4};
			V v(a);
			{
				AV av(v);
				auto sent = av.end();
				VERIFY(sent != av.begin());
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
