/**
 *	@file	unit_test_ranges_enumerate_view_sentinel_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	template<bool OtherConst>
 *	  requires sized_sentinel_for<sentinel_t<Base>, iterator_t<maybe-const<OtherConst, V>>>
 *	friend constexpr range_difference_t<maybe-const<OtherConst, V>>
 *	operator-(const iterator<OtherConst>& x, const sentinel& y);
 *
 *	template<bool OtherConst>
 *	  requires sized_sentinel_for<sentinel_t<Base>, iterator_t<maybe-const<OtherConst, V>>>
 *	friend constexpr range_difference_t<maybe-const<OtherConst, V>>
 *	operator-(const sentinel& x, const iterator<OtherConst>& y);
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace sentinel_sub_test
{

template <typename Iterator>
struct ConvertibleSentinel
{
	Iterator m_it;

	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel() : m_it() {}

	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel(Iterator const& it) : m_it(it) {}
};

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(ConvertibleSentinel<T> const& x, U const& y) noexcept
{
	return base(x.m_it) == base(y);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(ConvertibleSentinel<T> const& x, U const& y) noexcept
{
	return !(x == y);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(T const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return y == x;
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(T const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return !(x == y);
}

template <typename T, typename U>
HAMON_CONSTEXPR auto
operator-(ConvertibleSentinel<T> const& s, U const& i) noexcept
->decltype(base(s.m_it) - base(i))
{
	return base(s.m_it) - base(i);
}

template <typename T, typename U>
HAMON_CONSTEXPR auto
operator-(T const& i, ConvertibleSentinel<U> const& s) noexcept
->decltype(base(i) - base(s.m_it))
{
	return base(i) - base(s.m_it);
}

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
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{Iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{ConstIterator{m_last}}; }
};

template <typename T, typename U, typename = void>
struct has_sub
	: public hamon::false_type {};

template <typename T, typename U>
struct has_sub<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// iterator<true>, sentinel<true>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<true>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<true>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a[] = {1,2};
		V v(a);
		EV ev{v};
		I i = ev.begin();
		S s = ev.end();
		VERIFY(i - s == -2);
		VERIFY(s - i ==  2);
	}

	// iterator<false>, sentinel<true>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			test_sentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int const>,
			test_sentinel<input_iterator_wrapper<int const>>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV const&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<true>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			ConvertibleSentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int const>,
			ConvertibleSentinel<input_iterator_wrapper<int const>>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV const&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<true>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a[] = {1,2,3};
		V v(a);
		EV ev{v};
		I i = ev.begin();
		S s = ev.cend();
		VERIFY(i - s == -3);
		VERIFY(s - i ==  3);
	}

	// iterator<true>,  sentinel<false>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			test_sentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int const>,
			test_sentinel<input_iterator_wrapper<int const>>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV const&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<false>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			ConvertibleSentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int const>,
			ConvertibleSentinel<input_iterator_wrapper<int const>>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV const&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<false>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");
		
		int a[] = {1,2,3,4};
		V v(a);
		EV ev{v};
		I i = ev.cbegin();
		S s = ev.end();
		VERIFY(i - s == -4);
		VERIFY(s - i ==  4);
	}

	// iterator<false>, sentinel<false>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			test_sentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int const>,
			test_sentinel<input_iterator_wrapper<int const>>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<false>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			ConvertibleSentinel<input_iterator_wrapper<int>>,
			input_iterator_wrapper<int const>,
			ConvertibleSentinel<input_iterator_wrapper<int const>>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<false>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");
		
		int a[] = {1,2,3,4,5};
		V v(a);
		EV ev{v};
		I i = ev.begin();
		S s = ev.end();
		VERIFY(i - s == -5);
		VERIFY(s - i ==  5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewSentinelSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_sub_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
