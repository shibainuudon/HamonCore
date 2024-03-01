/**
 *	@file	unit_test_ranges_slide_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end()
 *	  requires (!(simple-view<V> && slide-caches-nothing<const V>));
 *	constexpr auto end() const requires slide-caches-nothing<const V>;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
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
namespace slide_view_test
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
	// simple_view<V> && slide_caches_nothing<V const>
	{
		// slide_caches_nothing<V>
		{
			using V = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert( hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert( hamon::ranges::detail::slide_caches_nothing<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert( has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			using CS = decltype(hamon::declval<SV const&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<true>>::value, "");
			//static_assert( hamon::is_same<CS, SV::iterator<true>>::value, "");
			static_assert( hamon::is_same<S, CS>::value, "");
			static_assert( hamon::is_same<S, decltype(hamon::declval<SV&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
			{
				SV const sv(v, 3);
				CS sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && slide_caches_last<V>
		// !slide_caches_nothing<V> && !slide_caches_last<V> && common_range<V>
		// !slide_caches_nothing<V> && !slide_caches_last<V> && !common_range<V>
		{
			// simple_view<V> && slide_caches_nothing<V const> ということは
			// !slide_caches_nothing<V> になることはない
		}
	}

	// !simple_view<V> && slide_caches_nothing<V const>
	{
		// slide_caches_nothing<V>
		{
			using V = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int const>,
				random_access_iterator_wrapper<int const>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert( hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert( hamon::ranges::detail::slide_caches_nothing<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert( has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			using CS = decltype(hamon::declval<SV const&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<false>>::value, "");
			//static_assert( hamon::is_same<CS, SV::iterator<true>>::value, "");
			static_assert(!hamon::is_same<S, CS>::value, "");
			static_assert( hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");
			static_assert( hamon::is_same<CS, decltype(hamon::declval<SV const&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
			{
				SV const sv(v, 3);
				CS sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && slide_caches_last<V>
		{
			using V = TestView<int,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert( hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert( hamon::ranges::detail::slide_caches_last<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert( has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			using CS = decltype(hamon::declval<SV const&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<false>>::value, "");
			//static_assert( hamon::is_same<CS, SV::iterator<true>>::value, "");
			static_assert(!hamon::is_same<S, CS>::value, "");
			static_assert( hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");
			static_assert( hamon::is_same<CS, decltype(hamon::declval<SV const&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
			{
				SV const sv(v, 3);
				CS sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && !slide_caches_last<V> && common_range<V>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert( hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_last<V>, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert( has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			using CS = decltype(hamon::declval<SV const&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<false>>::value, "");
			//static_assert( hamon::is_same<CS, SV::iterator<true>>::value, "");
			static_assert(!hamon::is_same<S, CS>::value, "");
			static_assert( hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");
			static_assert( hamon::is_same<CS, decltype(hamon::declval<SV const&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
			{
				SV const sv(v, 3);
				CS sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && !slide_caches_last<V> && !common_range<V>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert( hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_last<V>, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert( has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			using CS = decltype(hamon::declval<SV const&>().end());
			//static_assert( hamon::is_same<S,  SV::sentinel>::value, "");
			//static_assert( hamon::is_same<CS, SV::iterator<true>>::value, "");
			static_assert(!hamon::is_same<S, CS>::value, "");
			static_assert(!hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");
			static_assert( hamon::is_same<CS, decltype(hamon::declval<SV const&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
			{
				SV const sv(v, 3);
				CS sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
	}

	// simple_view<V> && !slide_caches_nothing<V const>
	{
		// slide_caches_nothing<V>
		{
			// simple_view<V> && !slide_caches_nothing<V const> ということは
			// slide_caches_nothing<V> になることはない
		}

		// !slide_caches_nothing<V> && slide_caches_last<V>
		{
			using V = TestView<int,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert( hamon::ranges::detail::slide_caches_last<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<false>>::value, "");
			static_assert( hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && !slide_caches_last<V> && common_range<V>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_last<V>, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<false>>::value, "");
			static_assert( hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && !slide_caches_last<V> && !common_range<V>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>
			>;
			static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_last<V>, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			//static_assert( hamon::is_same<S,  SV::sentinel>::value, "");
			static_assert(!hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
	}

	// !simple_view<V> && !slide_caches_nothing<V const>
	{
		// slide_caches_nothing<V>
		{
			using V = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert( hamon::ranges::detail::slide_caches_nothing<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<false>>::value, "");
			static_assert( hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && slide_caches_last<V>
		{
			using V = TestView<int,
				bidirectional_iterator_wrapper<int>,
				bidirectional_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert( hamon::ranges::detail::slide_caches_last<V>, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<false>>::value, "");
			static_assert( hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && !slide_caches_last<V> && common_range<V>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>,
				forward_iterator_wrapper<int const>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_last<V>, "");
			static_assert( hamon::ranges::common_range_t<V>::value, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			//static_assert( hamon::is_same<S,  SV::iterator<false>>::value, "");
			static_assert( hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}

		// !slide_caches_nothing<V> && !slide_caches_last<V> && !common_range<V>
		{
			using V = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>
			>;
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V const>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_nothing<V>, "");
			//static_assert(!hamon::ranges::detail::slide_caches_last<V>, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");

			using SV = hamon::ranges::slide_view<V>;
			static_assert( has_end<SV&>::value, "");
			static_assert(!has_end<SV const&>::value, "");

			using S  = decltype(hamon::declval<SV&>().end());
			//static_assert( hamon::is_same<S,  SV::sentinel>::value, "");
			static_assert(!hamon::is_same<S,  decltype(hamon::declval<SV&>().begin())>::value, "");

			int a[] = {1,2,3,4,5};
			V v(a);
			{
				SV sv(v, 2);
				S sent = sv.end();
				VERIFY(sent != sv.begin());
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
