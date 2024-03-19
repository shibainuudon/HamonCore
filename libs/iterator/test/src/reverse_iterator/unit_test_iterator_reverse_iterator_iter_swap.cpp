/**
 *	@file	unit_test_iterator_reverse_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	template<indirectly_swappable<Iterator> Iterator2>
 *	friend constexpr void
 *	iter_swap(
 *		const reverse_iterator& x,
 *		const reverse_iterator<Iterator2>& y) noexcept(see below);
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace iter_swap_test {

template <typename T, typename U = T, typename = void>
struct has_iter_swap
	: public hamon::false_type {};

template <typename T, typename U>
struct has_iter_swap<T, U, hamon::void_t<decltype(hamon::ranges::iter_swap(hamon::declval<T>(), hamon::declval<U>()))>>
	: public hamon::true_type {};

template <bool NoExceptCopy, bool NoExceptDecrement, bool NoExceptIterSwap>
struct TestIterator
{
	using T = float;
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestIterator& operator++() noexcept { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator--() noexcept(NoExceptDecrement) { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator--(int);
	HAMON_CXX11_CONSTEXPR T& operator*() const noexcept(true) { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR TestIterator() noexcept(true) : m_ptr(nullptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator && other) noexcept(true) : m_ptr(other.m_ptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator const& other) noexcept(NoExceptCopy) : m_ptr(other.m_ptr) {}
	HAMON_CXX14_CONSTEXPR TestIterator& operator=(TestIterator && other) noexcept(true) { m_ptr = other.m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator=(TestIterator const& other) noexcept(NoExceptCopy) { m_ptr = other.m_ptr; return *this; }
	HAMON_CXX11_CONSTEXPR bool operator==(const TestIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestIterator& rhs) const { return !(*this == rhs); }
};

template <bool NoExceptCopy, bool NoExceptDecrement, bool NoExceptIterSwap>
HAMON_CXX14_CONSTEXPR void iter_swap(
	TestIterator<NoExceptCopy, NoExceptDecrement, NoExceptIterSwap> const&,
	TestIterator<NoExceptCopy, NoExceptDecrement, NoExceptIterSwap> const&) noexcept(NoExceptIterSwap);

static_assert(hamon::bidirectional_iterator_t<TestIterator<true,  true,  true>>::value, "");

static_assert( has_iter_swap<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*>>::value, "");
static_assert( has_iter_swap<hamon::reverse_iterator<int*>, hamon::reverse_iterator<long*>>::value, "");
static_assert(!has_iter_swap<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*>>::value, "");
static_assert(!has_iter_swap<hamon::reverse_iterator<int const*>, hamon::reverse_iterator<int const*>>::value, "");
static_assert( has_iter_swap<hamon::reverse_iterator<TestIterator<true, true, true>>, hamon::reverse_iterator<TestIterator<true, true, true>>>::value, "");

static_assert( noexcept(hamon::ranges::iter_swap(
	hamon::declval<hamon::reverse_iterator<int*>>(),
	hamon::declval<hamon::reverse_iterator<int*>>())), "");
static_assert( noexcept(hamon::ranges::iter_swap(
	hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true>>>(),
	hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true>>>())), "");
static_assert(!noexcept(hamon::ranges::iter_swap(
	hamon::declval<hamon::reverse_iterator<TestIterator<false, true, true>>>(),
	hamon::declval<hamon::reverse_iterator<TestIterator<false, true, true>>>())), "");
static_assert(!noexcept(hamon::ranges::iter_swap(
	hamon::declval<hamon::reverse_iterator<TestIterator<true, false, true>>>(),
	hamon::declval<hamon::reverse_iterator<TestIterator<true, false, true>>>())), "");
static_assert(!noexcept(hamon::ranges::iter_swap(
	hamon::declval<hamon::reverse_iterator<TestIterator<true, true, false>>>(),
	hamon::declval<hamon::reverse_iterator<TestIterator<true, true, false>>>())), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {10,20,30};
	hamon::reverse_iterator<int*> it1(&a[1]);
	hamon::reverse_iterator<int*> it2(&a[2]);

	VERIFY(a[0] == 10);
	VERIFY(a[1] == 20);
	VERIFY(a[2] == 30);

	hamon::ranges::iter_swap(it1, it2);

	VERIFY(a[0] == 20);
	VERIFY(a[1] == 10);
	VERIFY(a[2] == 30);

	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, IterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iter_swap_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
