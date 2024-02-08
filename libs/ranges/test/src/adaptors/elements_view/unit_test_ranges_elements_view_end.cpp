/**
 *	@file	unit_test_ranges_elements_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires (!simple-view<V> && !common_range<V>);
 *	constexpr auto end() requires (!simple-view<V> && common_range<V>);
 *	constexpr auto end() const requires range<const V>;
 *	constexpr auto end() const requires common_range<const V>;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
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
namespace elements_view_test
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
	//  simple_view<V> &&  range<V const> &&  common_range<V> &&  common_range<V const>
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");
		static_assert( hamon::ranges::common_range_t<V>::value, "");
		static_assert( hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		using S  = decltype(hamon::declval<EV&>().end());
		using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CS, EV::iterator<true>>::value, "");
		static_assert(hamon::is_same<S, CS>::value, "");
		static_assert(hamon::input_or_output_iterator_t<S>::value, "");
		static_assert(hamon::input_or_output_iterator_t<CS>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<S>,  int&>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<CS>, int&>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		V const& cv = v;
		{
			EV ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == v.end());
		}
		{
			EV const ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == cv.end());
		}
	}

	// !simple_view<V> &&  range<V const> &&  common_range<V> &&  common_range<V const>
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple const>,
			input_iterator_wrapper<Tuple const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");
		static_assert( hamon::ranges::common_range_t<V>::value, "");
		static_assert( hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		using S  = decltype(hamon::declval<EV&>().end());
		using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CS, EV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<S, CS>::value, "");
		static_assert(hamon::input_or_output_iterator_t<S>::value, "");
		static_assert(hamon::input_or_output_iterator_t<CS>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<S>,  int&>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<CS>, int const&>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		V const& cv = v;
		{
			EV ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == v.end());
		}
		{
			EV const ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == cv.end());
		}
	}

	//  simple_view<V> && !range<V const> &&  common_range<V> &&  common_range<V const>
	{
		// simple_view<V> && !range<V const> ということは、
		// range<V> も false になってしまう
	}

	// !simple_view<V> && !range<V const> &&  common_range<V> &&  common_range<V const>
	{
		// !range<V const> ということは、
		// common_range<V const> も false になってしまう
	}

	//  simple_view<V> &&  range<V const> && !common_range<V> &&  common_range<V const>
	{
		// !common_range<V> &&  common_range<V const> ということは、
		// simple_view<V> も false になってしまう
	}

	// !simple_view<V> &&  range<V const> && !common_range<V> &&  common_range<V const>
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			test_sentinel<input_iterator_wrapper<Tuple>>,
			input_iterator_wrapper<Tuple const>,
			input_iterator_wrapper<Tuple const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert( hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		using S  = decltype(hamon::declval<EV&>().end());
		using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::sentinel<false>>::value, "");
		//static_assert(hamon::is_same<CS, EV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<S, CS>::value, "");
		static_assert(!hamon::input_or_output_iterator_t<S>::value, "");
		static_assert(hamon::input_or_output_iterator_t<CS>::value, "");
		//static_assert(hamon::is_same<hamon::iter_reference_t<S>,  int&>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<CS>, int const&>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		V const& cv = v;
		{
			EV ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == v.end());
		}
		{
			EV const ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == cv.end());
		}
	}

	//  simple_view<V> && !range<V const> && !common_range<V> &&  common_range<V const>
	{
		// simple_view<V> && !range<V const> ということは、
		// range<V> も false になってしまう
	}

	// !simple_view<V> && !range<V const> && !common_range<V> &&  common_range<V const>
	{
		// !range<V const> ということは、
		// common_range<V const> も false になってしまう
	}

	//  simple_view<V> &&  range<V const> &&  common_range<V> && !common_range<V const>
	{
		// common_range<V> && !common_range<V const> ということは、
		// simple_view<V> も false になってしまう
	}

	// !simple_view<V> &&  range<V const> &&  common_range<V> && !common_range<V const>
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple const>,
			test_sentinel<input_iterator_wrapper<Tuple const>>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");
		static_assert( hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		using S  = decltype(hamon::declval<EV&>().end());
		using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CS, EV::sentinel<true>>::value, "");
		static_assert(!hamon::is_same<S, CS>::value, "");
		static_assert(hamon::input_or_output_iterator_t<S>::value, "");
		static_assert(!hamon::input_or_output_iterator_t<CS>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<S>,  int&>::value, "");
		//static_assert(hamon::is_same<hamon::iter_reference_t<CS>, int const&>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		V const& cv = v;
		{
			EV ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == v.end());
		}
		{
			EV const ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == cv.end());
		}
	}

	//  simple_view<V> && !range<V const> &&  common_range<V> && !common_range<V const>
	{
		// simple_view<V> && !range<V const> ということは、
		// range<V> も false になってしまう
	}

	// !simple_view<V> && !range<V const> &&  common_range<V> && !common_range<V const>
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple>,
			input_iterator_wrapper<Tuple const>,
			input_iterator_wrapper<Tuple>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(!hamon::ranges::range_t<V const>::value, "");
		static_assert( hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_end<EV&>::value, "");
		static_assert(!has_end<EV const&>::value, "");

		using S  = decltype(hamon::declval<EV&>().end());
		//static_assert(hamon::is_same<S, EV::iterator<false>>::value, "");
		static_assert(hamon::input_or_output_iterator_t<S>::value, "");
		static_assert(hamon::is_same<hamon::iter_reference_t<S>, int&>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		{
			EV ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == v.end());
		}
	}

	//  simple_view<V> &&  range<V const> && !common_range<V> && !common_range<V const>
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			test_sentinel<input_iterator_wrapper<Tuple>>,
			input_iterator_wrapper<Tuple>,
			test_sentinel<input_iterator_wrapper<Tuple>>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		using S  = decltype(hamon::declval<EV&>().end());
		using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::sentinel<true>>::value, "");
		//static_assert(hamon::is_same<CS, EV::sentinel<true>>::value, "");
		static_assert(hamon::is_same<S, CS>::value, "");
		static_assert(!hamon::input_or_output_iterator_t<S>::value, "");
		static_assert(!hamon::input_or_output_iterator_t<CS>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		V const& cv = v;
		{
			EV ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == v.end());
		}
		{
			EV const ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == cv.end());
		}
	}

	// !simple_view<V> &&  range<V const> && !common_range<V> && !common_range<V const>
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			test_sentinel<input_iterator_wrapper<Tuple>>,
			input_iterator_wrapper<Tuple const>,
			test_sentinel<input_iterator_wrapper<Tuple const>>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		using S  = decltype(hamon::declval<EV&>().end());
		using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::sentinel<false>>::value, "");
		//static_assert(hamon::is_same<CS, EV::sentinel<true>>::value, "");
		static_assert(!hamon::is_same<S, CS>::value, "");
		static_assert(!hamon::input_or_output_iterator_t<S>::value, "");
		static_assert(!hamon::input_or_output_iterator_t<CS>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		V const& cv = v;
		{
			EV ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == v.end());
		}
		{
			EV const ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == cv.end());
		}
	}

	//  simple_view<V> && !range<V const> && !common_range<V> && !common_range<V const>
	{
		// simple_view<V> && !range<V const> ということは、
		// range<V> も false になってしまう
	}

	// !simple_view<V> && !range<V const> && !common_range<V> && !common_range<V const>
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			input_iterator_wrapper<Tuple>,
			test_sentinel<input_iterator_wrapper<Tuple>>,
			input_iterator_wrapper<Tuple const>,
			input_iterator_wrapper<Tuple>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(!hamon::ranges::range_t<V const>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		static_assert( has_end<EV&>::value, "");
		static_assert(!has_end<EV const&>::value, "");

		using S = decltype(hamon::declval<EV&>().end());
		//static_assert(hamon::is_same<S, EV::sentinel<false>>::value, "");
		static_assert(!hamon::input_or_output_iterator_t<S>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		{
			EV ev(v);
			auto sent = ev.end();
			VERIFY(sent.base() == v.end());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
