/**
 *	@file	unit_test_ranges_enumerate_view_sentinel_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	constexpr sentinel(sentinel<!Const> other)
 *	  requires Const && convertible_to<sentinel_t<V>, sentinel_t<Base>>;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace sentinel_ctor_conv_test
{

template <typename T>
struct ConvertibleInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR ConvertibleInputIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ConvertibleInputIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ConvertibleInputIterator(ConvertibleInputIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ConvertibleInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void                      operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                        operator*() const { return *m_ptr; }
	template <typename U>
	HAMON_CXX11_CONSTEXPR bool operator==(const ConvertibleInputIterator<U>& rhs) const { return m_ptr == rhs.m_ptr; }
	template <typename U>
	HAMON_CXX11_CONSTEXPR bool operator!=(const ConvertibleInputIterator<U>& rhs) const { return !(*this == rhs); }
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
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{Iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{ConstIterator{m_last}}; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = TestView<int,
			ConvertibleInputIterator<int>,
			ConvertibleInputIterator<int>,
			ConvertibleInputIterator<int const>,
			ConvertibleInputIterator<int const>
		>;
		using EV = hamon::ranges::enumerate_view<V>;
		using S  = decltype(hamon::declval<EV&>().end());
		using CS = decltype(hamon::declval<EV const&>().end());
		static_assert(!hamon::is_constructible<S, CS>::value, "");
		static_assert( hamon::is_constructible<CS, S>::value, "");
		static_assert( hamon::is_implicitly_constructible<CS, S>::value, "");
		
		int a[] = { 1, 2, 3 };
		V v(a);
		EV ev(v);

		CS sent = ev.end();
		VERIFY(sent.base() == v.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewSentinelCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_conv_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
