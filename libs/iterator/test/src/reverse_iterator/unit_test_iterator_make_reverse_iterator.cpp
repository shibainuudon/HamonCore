/**
 *	@file	unit_test_iterator_make_reverse_iterator.cpp
 *
 *	@brief	make_reverse_iterator のテスト
 */

#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace make_reverse_iterator_test
{

template <bool NoExceptMove>
struct TestIterator
{
	using T = float;
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR T& operator*() const noexcept(true) { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR TestIterator() noexcept(true) : m_ptr(nullptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator && other) noexcept(NoExceptMove) : m_ptr(other.m_ptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator const& other) noexcept(true) : m_ptr(other.m_ptr) {}
};

static_assert(hamon::is_same<
	decltype(hamon::make_reverse_iterator(hamon::declval<int*>())),
	hamon::reverse_iterator<int*>>::value, "");
static_assert(hamon::is_same<
	decltype(hamon::make_reverse_iterator(hamon::declval<TestIterator<true>>())),
	hamon::reverse_iterator<TestIterator<true>>>::value, "");
static_assert(hamon::is_same<
	decltype(hamon::make_reverse_iterator(hamon::declval<TestIterator<false>>())),
	hamon::reverse_iterator<TestIterator<false>>>::value, "");

static_assert( noexcept(hamon::make_reverse_iterator(hamon::declval<int*>())), "");
static_assert( noexcept(hamon::make_reverse_iterator(hamon::declval<TestIterator<true>>())), "");
static_assert(!noexcept(hamon::make_reverse_iterator(hamon::declval<TestIterator<false>>())), "");

inline HAMON_CXX14_CONSTEXPR bool make_reverse_iterator_test()
{
	char s[] = "123";
	auto it1 = hamon::make_reverse_iterator(s);
	hamon::reverse_iterator<char*> it2(s);
	return it1 == it2;
}

GTEST_TEST(IteratorTest, MakeReverseIteratorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(make_reverse_iterator_test());
}

}	// namespace make_reverse_iterator_test

}	// namespace hamon_iterator_test
