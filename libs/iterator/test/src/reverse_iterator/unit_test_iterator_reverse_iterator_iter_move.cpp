/**
 *	@file	unit_test_iterator_reverse_iterator_iter_move.cpp
 *
 *	@brief	iter_move のテスト
 *
 *	friend constexpr iter_rvalue_reference_t<Iterator>
 *	iter_move(const reverse_iterator& i) noexcept(see below);
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace iter_move_test {

template <bool NoExceptCopy, bool NoExceptDecrement, bool NoExceptIterMove>
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

template <bool NoExceptCopy, bool NoExceptDecrement, bool NoExceptIterMove>
HAMON_CXX11_CONSTEXPR float&& iter_move(
	TestIterator<NoExceptCopy, NoExceptDecrement, NoExceptIterMove> const&) noexcept(NoExceptIterMove);

static_assert(hamon::bidirectional_iterator_t<TestIterator<true,  true,  true>>::value, "");

static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(hamon::declval<hamon::reverse_iterator<int*>>())), int&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true>>>())), float&&>::value, "");

static_assert( noexcept(hamon::ranges::iter_move(hamon::declval<hamon::reverse_iterator<int*>>())), "");
static_assert( noexcept(hamon::ranges::iter_move(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true>>>())), "");
static_assert(!noexcept(hamon::ranges::iter_move(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true>>>())), "");
static_assert(!noexcept(hamon::ranges::iter_move(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true>>>())), "");
static_assert(!noexcept(hamon::ranges::iter_move(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false>>>())), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {10,20,30};
	{
		hamon::reverse_iterator<int*> it(&a[1]);
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), int&&>::value, "");
		VERIFY(hamon::ranges::iter_move(it) == 10);
	}
	{
		hamon::reverse_iterator<int*> it(&a[2]);
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), int&&>::value, "");
		VERIFY(hamon::ranges::iter_move(it) == 20);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, IterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iter_move_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
