/**
 *	@file	unit_test_ranges_elements_view_sentinel_ctor_conv.cpp
 *
 *	@brief	sentinel<!Const>を引数に取るコンストラクタのテスト
 *
 *	constexpr sentinel(sentinel<!Const> other)
 *	  requires Const && convertible_to<sentinel_t<V>, sentinel_t<Base>>;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace sentinel_ctor_conv_test
{

template <typename T>
struct ConvertibleForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator(ConvertibleForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ConvertibleForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ConvertibleForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T& operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ConvertibleForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ConvertibleForwardIterator& rhs) const { return !(*this == rhs); }
};

template <typename Iterator>
struct ConvertibleSentinel
{
	Iterator m_it;

	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel() : m_it() {}

	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel(Iterator const& it) : m_it(it) {}

	template <typename U, typename = hamon::enable_if_t<hamon::convertible_to_t<U const&, Iterator>::value>>
	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel(ConvertibleSentinel<U> const& u) : m_it(u.m_it) {}
};

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(ConvertibleSentinel<T> const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return base(x.m_it) == base(y.m_it);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(ConvertibleSentinel<T> const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return !(x == y);
}

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			ConvertibleForwardIterator<Tuple>,
			test_sentinel<ConvertibleForwardIterator<Tuple>>,
			ConvertibleForwardIterator<Tuple const>,
			test_sentinel<ConvertibleForwardIterator<Tuple const>>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		using S  = hamon::ranges::sentinel_t<EV>;
		using CS = hamon::ranges::sentinel_t<EV const>;
		static_assert(!hamon::is_same<S, CS>::value, "");
		static_assert(!hamon::is_constructible<S, CS>::value, "");
		static_assert(!hamon::is_constructible<CS, S>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = TestView<Tuple,
			ConvertibleForwardIterator<Tuple>,
			ConvertibleSentinel<ConvertibleForwardIterator<Tuple>>,
			ConvertibleForwardIterator<Tuple const>,
			ConvertibleSentinel<ConvertibleForwardIterator<Tuple const>>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert( hamon::ranges::range_t<V const>::value, "");
		static_assert(!hamon::ranges::common_range_t<V>::value, "");
		static_assert(!hamon::ranges::common_range_t<V const>::value, "");

		using EV = hamon::ranges::elements_view<V, 0>;
		using S  = hamon::ranges::sentinel_t<EV>;
		using CS = hamon::ranges::sentinel_t<EV const>;
		static_assert(!hamon::is_same<S, CS>::value, "");
		static_assert(!hamon::is_constructible<S, CS>::value, "");
		static_assert( hamon::is_constructible<CS, S>::value, "");
		static_assert( hamon::is_implicitly_constructible<CS, S>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev{v};

		CS sent = ev.end();
		VERIFY(sent.base() == v.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewSentinelCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_conv_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
