/**
 *	@file	unit_test_ranges_concat_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap() のテスト
 *
 *	friend constexpr void iter_swap(const iterator& x, const iterator& y) noexcept(see below)
 *		requires see below;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace iterator_iter_swap_test
{

template <typename T>
struct ValueForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX11_CONSTEXPR ValueForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ValueForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ValueForwardIterator(ValueForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ValueForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueForwardIterator& rhs) const { return !(*this == rhs); }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V1 = test_forward_view<int>;
		using V2 = test_input_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_iter_swap<I>::value, "");
//		static_assert(!noexcept(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), "");
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_swap(hamon::declval<I>(), hamon::declval<I>())), void>::value, "");
	}
	{
		using V1 = test_forward_view<int const>;
		using V2 = test_input_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_iter_swap<I>::value, "");
	}
	{
		using V1 = test_view<int, ValueForwardIterator<int>>;
		using V2 = test_input_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_iter_swap<I>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a1[] = {1,2};
	int a2[] = {3,4,5};

	auto cv = hamon::views::concat(a1, a2);

	auto it1 = cv.begin();
	auto it2 = cv.begin() + 3;
//	static_assert(!noexcept(hamon::ranges::iter_swap(it1, it2)), "");
	static_assert(hamon::is_same<decltype(hamon::ranges::iter_swap(it1, it2)), void>::value, "");

	VERIFY(*it1 == 1);
	VERIFY(*it2 == 4);
	VERIFY(a1[0] == 1);
	VERIFY(a2[1] == 4);

	hamon::ranges::iter_swap(it1, it2);
	VERIFY(*it1 == 4);
	VERIFY(*it2 == 1);
	VERIFY(a1[0] == 4);
	VERIFY(a2[1] == 1);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V1 = test_forward_view<int>;
	using V2 = test_input_view<int>;

	int a1[] = {1,2};
	int a2[] = {3,4,5};

	V1 v1(a1);
	V2 v2(a2);
	auto cv = hamon::views::concat(v1, v2);

	auto it1 = cv.begin();
	it1++;
	auto it2 = cv.begin();
	it2++;
	it2++;
	VERIFY(*it1 == 2);
	VERIFY(*it2 == 3);
	VERIFY(a1[1] == 2);
	VERIFY(a2[0] == 3);

	hamon::ranges::iter_swap(it1, it2);
	VERIFY(*it1 == 3);
	VERIFY(*it2 == 2);
	VERIFY(a1[1] == 3);
	VERIFY(a2[0] == 2);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_iter_swap_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
