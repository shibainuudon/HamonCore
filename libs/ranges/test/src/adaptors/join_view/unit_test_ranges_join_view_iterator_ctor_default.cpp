/**
 *	@file	unit_test_ranges_join_view_iterator_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	iterator() = default;
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace iterator_ctor_default_test
{

template <typename T>
struct NoDefaultIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	//HAMON_CXX11_CONSTEXPR NoDefaultIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR NoDefaultIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR NoDefaultIterator(NoDefaultIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR NoDefaultIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR NoDefaultIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const NoDefaultIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const NoDefaultIterator& rhs) const { return !(*this == rhs); }
};

static_assert(!hamon::is_default_constructible<NoDefaultIterator<int>>::value, "");

template <typename T>
struct NoDefaultIterView : hamon::ranges::view_base
{
	T* m_first;

	using iterator = NoDefaultIterator<T>;
	using const_iterator = NoDefaultIterator<T const>;
	using sentinel = hamon::unreachable_sentinel_t;
	using const_sentinel = hamon::unreachable_sentinel_t;

	explicit HAMON_CXX11_CONSTEXPR NoDefaultIterView(T* first) : m_first(first) {}
	NoDefaultIterView(NoDefaultIterView&&) = default;
	NoDefaultIterView& operator=(NoDefaultIterView&&) = default;

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return hamon::unreachable_sentinel_t{}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return hamon::unreachable_sentinel_t{}; }
};

static_assert(hamon::ranges::input_range_t<NoDefaultIterView<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class InnerView, template <typename> class OuterView>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = OuterView<InnerView<int>>;
	using RV = hamon::ranges::join_view<V>;
	using I = hamon::ranges::iterator_t<RV>;
	static_assert(hamon::is_default_constructible<I>::value, "");
	I it1{};
	I it2{};
	VERIFY(it1 == it2);
	return true;
}

template <template <typename> class OuterView>
HAMON_CXX14_CONSTEXPR bool test01()
{
	VERIFY(test00<test_input_view, OuterView>());
	VERIFY(test00<test_forward_view, OuterView>());
	VERIFY(test00<test_bidirectional_view, OuterView>());
	VERIFY(test00<test_random_access_view, OuterView>());

	// InnerViewのイテレータが非DefaultConstructibleでも、
	// join_viewのイテレータはDefaultConstructible。
	VERIFY(test00<NoDefaultIterView, OuterView>());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test()
{
//	VERIFY(test01<test_input_view>());
	VERIFY(test01<test_forward_view>());
	VERIFY(test01<test_bidirectional_view>());
	VERIFY(test01<test_random_access_view>());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace iterator_ctor_default_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
