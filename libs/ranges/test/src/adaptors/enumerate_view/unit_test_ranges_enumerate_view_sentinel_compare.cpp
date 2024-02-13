/**
 *	@file	unit_test_ranges_enumerate_view_sentinel_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<bool OtherConst>
 *	  requires sentinel_for<sentinel_t<Base>, iterator_t<maybe-const<OtherConst, V>>>
 *	friend constexpr bool operator==(const iterator<OtherConst>& x, const sentinel& y);
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
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
namespace enumerate_view_test
{
namespace sentinel_compare_test
{

template <typename T>
struct TestInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void                      operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                        operator*() const { return *m_ptr; }
	template <typename U>
	HAMON_CXX11_CONSTEXPR bool operator==(const TestInputIterator<U>& rhs) const { return m_ptr == rhs.m_ptr; }
	template <typename U>
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestInputIterator<U>& rhs) const { return !(*this == rhs); }
};

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

template <typename T, typename U, typename = void>
struct has_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_not_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_not_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
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

		static_assert(has_equal<I, S>::value, "");
		static_assert(has_equal<S, I>::value, "");
		static_assert(has_not_equal<I, S>::value, "");
		static_assert(has_not_equal<S, I>::value, "");

		int a[] = {11,12,13};
		V v(a);
		EV ev{v};
		I i = ev.begin();
		S s = ev.end();
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY( (i == s));
		VERIFY(!(i != s));
		VERIFY( (s == i));
		VERIFY(!(s != i));
	}

	// iterator<false>, sentinel<true>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV const&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<true>>::value, "");

		static_assert(!has_equal<I, S>::value, "");
		static_assert(!has_equal<S, I>::value, "");
		static_assert(!has_not_equal<I, S>::value, "");
		static_assert(!has_not_equal<S, I>::value, "");
	}
	{
		using V = TestView<int,
			TestInputIterator<int>,
			TestInputIterator<int>,
			TestInputIterator<int const>,
			TestInputIterator<int const>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV const&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<true>>::value, "");

		static_assert(has_equal<I, S>::value, "");
		static_assert(has_equal<S, I>::value, "");
		static_assert(has_not_equal<I, S>::value, "");
		static_assert(has_not_equal<S, I>::value, "");

		int a[] = {11,12,13};
		V v(a);
		EV ev{v};
		I i = ev.begin();
		S s = ev.cend();
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY( (i == s));
		VERIFY(!(i != s));
		VERIFY( (s == i));
		VERIFY(!(s != i));
	}

	// iterator<true>, sentinel<false>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV const&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<false>>::value, "");

		static_assert(!has_equal<I, S>::value, "");
		static_assert(!has_equal<S, I>::value, "");
		static_assert(!has_not_equal<I, S>::value, "");
		static_assert(!has_not_equal<S, I>::value, "");
	}
	{
		using V = TestView<int,
			TestInputIterator<int>,
			TestInputIterator<int>,
			TestInputIterator<int const>,
			TestInputIterator<int const>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV const&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<false>>::value, "");

		static_assert(has_equal<I, S>::value, "");
		static_assert(has_equal<S, I>::value, "");
		static_assert(has_not_equal<I, S>::value, "");
		static_assert(has_not_equal<S, I>::value, "");

		int a[] = {11,12,13};
		V v(a);
		EV ev{v};
		I i = ev.cbegin();
		S s = ev.end();
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY( (i == s));
		VERIFY(!(i != s));
		VERIFY( (s == i));
		VERIFY(!(s != i));
	}

	// iterator<false>, sentinel<false>
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = decltype(hamon::declval<EV&>().begin());
		using S = decltype(hamon::declval<EV&>().end());

		//static_assert(hamon::is_same<I, EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, EV::sentinel<false>>::value, "");

		static_assert(has_equal<I, S>::value, "");
		static_assert(has_equal<S, I>::value, "");
		static_assert(has_not_equal<I, S>::value, "");
		static_assert(has_not_equal<S, I>::value, "");

		int a[] = {11,12,13};
		V v(a);
		EV ev{v};
		I i = ev.begin();
		S s = ev.end();
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY(!(i == s));
		VERIFY( (i != s));
		VERIFY(!(s == i));
		VERIFY( (s != i));
		++i;
		VERIFY( (i == s));
		VERIFY(!(i != s));
		VERIFY( (s == i));
		VERIFY(!(s != i));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewSentinelCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_compare_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
