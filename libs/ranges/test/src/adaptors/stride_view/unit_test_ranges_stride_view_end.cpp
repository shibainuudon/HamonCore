/**
 *	@file	unit_test_ranges_stride_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires (!simple-view<V>);
 *	constexpr auto end() const requires range<const V>;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
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
		// common_range<V const> && sized_range<V const> && forward_range<V const>
		{
			using V = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert( hamon::ranges::common_range_t<V const>::value, "");
			static_assert( hamon::ranges::sized_range_t<V const>::value, "");
			static_assert( hamon::ranges::forward_range_t<V const>::value, "");

			using SV = hamon::ranges::stride_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert( has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			using CS = decltype(hamon::declval<SV const&>().end());
			//static_assert(hamon::is_same<S,  SV::iterator<true>>::value, "");
			//static_assert(hamon::is_same<CS, SV::iterator<true>>::value, "");
			static_assert(hamon::is_same<S, CS>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 1);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
			{
				SV const sv(v, 2);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
		// else common_range<V const> && !bidirectional_range<V const>
		{
			using V = TestView<int,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert( hamon::ranges::common_range_t<V const>::value, "");
			static_assert(!hamon::ranges::sized_range_t<V const>::value, "");
			static_assert(!hamon::ranges::forward_range_t<V const>::value, "");
			static_assert(!hamon::ranges::bidirectional_range_t<V const>::value, "");

			using SV = hamon::ranges::stride_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert( has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			using CS = decltype(hamon::declval<SV const&>().end());
			//static_assert(hamon::is_same<S,  SV::iterator<true>>::value, "");
			//static_assert(hamon::is_same<CS, SV::iterator<true>>::value, "");
			static_assert(hamon::is_same<S, CS>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 1);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
			{
				SV const sv(v, 2);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
		// else
		{
			using V = TestView<int,
				input_iterator_wrapper<int>,
				test_sentinel<input_iterator_wrapper<int>>,
				input_iterator_wrapper<int>,
				test_sentinel<input_iterator_wrapper<int>>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert( hamon::ranges::range_t<V const>::value, "");
			static_assert(!hamon::ranges::common_range_t<V const>::value, "");

			using SV = hamon::ranges::stride_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert( has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			using CS = decltype(hamon::declval<SV const&>().end());
			static_assert(hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
			static_assert(hamon::is_same<CS, hamon::default_sentinel_t>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 1);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
			{
				SV const sv(v, 2);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
	}

	// !simple_view<V> && range<V const>
	{
		// common_range<V> && sized_range<V> && forward_range<V>
		{
			// common_range<V const> && sized_range<V const> && forward_range<V const>
			{
				using V = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int const>,
					random_access_iterator_wrapper<int const>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert( hamon::ranges::common_range_t<V>::value, "");
				static_assert( hamon::ranges::sized_range_t<V>::value, "");
				static_assert( hamon::ranges::forward_range_t<V>::value, "");
				static_assert( hamon::ranges::common_range_t<V const>::value, "");
				static_assert( hamon::ranges::sized_range_t<V const>::value, "");
				static_assert( hamon::ranges::forward_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				//static_assert(hamon::is_same<S,  SV::iterator<false>>::value, "");
				//static_assert(hamon::is_same<CS, SV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
			}
			// else common_range<V const> && !bidirectional_range<V const>
			{
				using V = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					input_iterator_wrapper<int>,
					input_iterator_wrapper<int>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert( hamon::ranges::common_range_t<V>::value, "");
				static_assert( hamon::ranges::sized_range_t<V>::value, "");
				static_assert( hamon::ranges::forward_range_t<V>::value, "");
				static_assert( hamon::ranges::common_range_t<V const>::value, "");
				static_assert(!hamon::ranges::sized_range_t<V const>::value, "");
				static_assert(!hamon::ranges::forward_range_t<V const>::value, "");
				static_assert(!hamon::ranges::bidirectional_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				//static_assert(hamon::is_same<S,  SV::iterator<false>>::value, "");
				//static_assert(hamon::is_same<CS, SV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
			}
			// else
			{
				using V = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					input_iterator_wrapper<int>,
					test_sentinel<input_iterator_wrapper<int>>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert( hamon::ranges::common_range_t<V>::value, "");
				static_assert( hamon::ranges::sized_range_t<V>::value, "");
				static_assert( hamon::ranges::forward_range_t<V>::value, "");
				static_assert(!hamon::ranges::common_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				//static_assert(hamon::is_same<S,  SV::iterator<false>>::value, "");
				static_assert(hamon::is_same<CS, hamon::default_sentinel_t>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
			}
		}
		// else common_range<V> && !bidirectional_range<V>
		{
			// common_range<V const> && sized_range<V const> && forward_range<V const>
			{
				using V = TestView<int,
					input_iterator_wrapper<int>,
					input_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert( hamon::ranges::common_range_t<V>::value, "");
				static_assert(!hamon::ranges::sized_range_t<V>::value, "");
				static_assert(!hamon::ranges::forward_range_t<V>::value, "");
				static_assert(!hamon::ranges::bidirectional_range_t<V>::value, "");
				static_assert( hamon::ranges::common_range_t<V const>::value, "");
				static_assert( hamon::ranges::sized_range_t<V const>::value, "");
				static_assert( hamon::ranges::forward_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				//static_assert(hamon::is_same<S,  SV::iterator<false>>::value, "");
				//static_assert(hamon::is_same<CS, SV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
			}
			// else common_range<V const> && !bidirectional_range<V const>
			{
				using V = TestView<int,
					input_iterator_wrapper<int>,
					input_iterator_wrapper<int>,
					input_iterator_wrapper<int const>,
					input_iterator_wrapper<int const>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert( hamon::ranges::common_range_t<V>::value, "");
				static_assert(!hamon::ranges::sized_range_t<V>::value, "");
				static_assert(!hamon::ranges::forward_range_t<V>::value, "");
				static_assert(!hamon::ranges::bidirectional_range_t<V>::value, "");
				static_assert( hamon::ranges::common_range_t<V const>::value, "");
				static_assert(!hamon::ranges::sized_range_t<V const>::value, "");
				static_assert(!hamon::ranges::forward_range_t<V const>::value, "");
				static_assert(!hamon::ranges::bidirectional_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				//static_assert(hamon::is_same<S,  SV::iterator<false>>::value, "");
				//static_assert(hamon::is_same<CS, SV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
			}
			// else
			{
				using V = TestView<int,
					input_iterator_wrapper<int>,
					input_iterator_wrapper<int>,
					input_iterator_wrapper<int>,
					test_sentinel<input_iterator_wrapper<int>>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert( hamon::ranges::common_range_t<V>::value, "");
				static_assert(!hamon::ranges::sized_range_t<V>::value, "");
				static_assert(!hamon::ranges::forward_range_t<V>::value, "");
				static_assert(!hamon::ranges::bidirectional_range_t<V>::value, "");
				static_assert(!hamon::ranges::common_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				//static_assert(hamon::is_same<S,  SV::iterator<false>>::value, "");
				static_assert(hamon::is_same<CS, hamon::default_sentinel_t>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
			}
		}
		// else
		{
			// common_range<V const> && sized_range<V const> && forward_range<V const>
			{
				using V = TestView<int,
					random_access_iterator_wrapper<int>,
					test_sentinel<random_access_iterator_wrapper<int>>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert(!hamon::ranges::common_range_t<V>::value, "");
				static_assert( hamon::ranges::common_range_t<V const>::value, "");
				static_assert( hamon::ranges::sized_range_t<V const>::value, "");
				static_assert( hamon::ranges::forward_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				static_assert(hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
				//static_assert(hamon::is_same<CS, SV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
			}
			// else common_range<V const> && !bidirectional_range<V const>
			{
				using V = TestView<int,
					random_access_iterator_wrapper<int>,
					test_sentinel<random_access_iterator_wrapper<int>>,
					input_iterator_wrapper<int>,
					input_iterator_wrapper<int>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert(!hamon::ranges::common_range_t<V>::value, "");
				static_assert( hamon::ranges::common_range_t<V const>::value, "");
				static_assert(!hamon::ranges::sized_range_t<V const>::value, "");
				static_assert(!hamon::ranges::forward_range_t<V const>::value, "");
				static_assert(!hamon::ranges::bidirectional_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				static_assert(hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
				//static_assert(hamon::is_same<CS, SV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
			}
			// else
			{
				using V = TestView<int,
					random_access_iterator_wrapper<int>,
					test_sentinel<random_access_iterator_wrapper<int>>,
					input_iterator_wrapper<int>,
					test_sentinel<input_iterator_wrapper<int>>
				>;
				static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
				static_assert( hamon::ranges::range_t<V const>::value, "");
				static_assert(!hamon::ranges::common_range_t<V>::value, "");
				static_assert(!hamon::ranges::common_range_t<V const>::value, "");

				using SV = hamon::ranges::stride_view<V>;
				static_assert( has_end<SV&>::value, "");
				static_assert( has_end<SV const&>::value, "");

				using S  = decltype(hamon::declval<SV&>().end());
				using CS = decltype(hamon::declval<SV const&>().end());
				static_assert(hamon::is_same<S,  hamon::default_sentinel_t>::value, "");
				static_assert(hamon::is_same<CS, hamon::default_sentinel_t>::value, "");

				int a[] = {1,2,3,4,5};
				V v(a);
				{
					SV sv(v, 1);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
				{
					SV const sv(v, 2);
					auto sent = sv.end();
					VERIFY(sent != sv.begin());
				}
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
		// common_range<V> && sized_range<V> && forward_range<V>
		{
			using V = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int const>,
				random_access_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::range_t<V const>::value, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");
			static_assert( hamon::ranges::sized_range_t<V>::value, "");
			static_assert( hamon::ranges::forward_range_t<V>::value, "");

			using SV = hamon::ranges::stride_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			//using S  = decltype(hamon::declval<SV&>().end());
			//static_assert(hamon::is_same<S,  SV::iterator<false>>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 1);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
		// else common_range<V> && !bidirectional_range<V>
		{
			using V = TestView<int,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int const>,
				input_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::range_t<V const>::value, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::sized_range_t<V>::value, "");
			static_assert(!hamon::ranges::forward_range_t<V>::value, "");
			static_assert(!hamon::ranges::bidirectional_range_t<V>::value, "");

			using SV = hamon::ranges::stride_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			//using S  = decltype(hamon::declval<SV&>().end());
			//static_assert(hamon::is_same<S,  SV::iterator<false>>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 1);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
		// else
		{
			using V = TestView<int,
				input_iterator_wrapper<int>,
				test_sentinel<input_iterator_wrapper<int>>,
				input_iterator_wrapper<int const>,
				input_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::range_t<V const>::value, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");

			using SV = hamon::ranges::stride_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			static_assert(hamon::is_same<S,  hamon::default_sentinel_t>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 1);
				auto sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
