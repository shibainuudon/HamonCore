/**
 *	@file	unit_test_ranges_lazy_split_view_inner_iterator_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	inner-iterator() = default;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/concepts.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace inner_iterator_ctor_default_test
{

template <typename T>
struct NoDefaultForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	explicit HAMON_CXX11_CONSTEXPR NoDefaultForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR NoDefaultForwardIterator(NoDefaultForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR NoDefaultForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR NoDefaultForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T& operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const NoDefaultForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const NoDefaultForwardIterator& rhs) const { return !(*this == rhs); }
};

static_assert(hamon::input_iterator_t<NoDefaultForwardIterator<int>>::value, "");
static_assert(!hamon::forward_iterator_t<NoDefaultForwardIterator<int>>::value, "");

template <typename Iterator>
struct UnreachableView : hamon::ranges::view_base
{
	Iterator                      begin() const noexcept;
	hamon::unreachable_sentinel_t end()   const noexcept;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());
	static_assert(hamon::is_default_constructible<I>::value, "");

	I it{};
	(void)it;

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = UnreachableView<NoDefaultForwardIterator<int>>;
	using P = test_forward_static_sized_view<int, 1>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());
	static_assert(hamon::is_default_constructible<I>::value, "");

	I it{};
	(void)it;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewInnerIteratorCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace inner_iterator_ctor_default_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
