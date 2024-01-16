/**
 *	@file	unit_test_iterator_reverse_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr reference operator*() const;
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace dereference_test {

template <bool NoExceptCopy, bool NoExceptDereference, bool NoExceptDecrement>
struct TestIterator
{
	using T = float;
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestIterator& operator++()    noexcept(true) { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator++(int) noexcept(true) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator--()    noexcept(NoExceptDecrement) { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator--(int) noexcept(true) { auto t = *this; --m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T             operator*() const noexcept(NoExceptDereference) { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR TestIterator() noexcept(true) : m_ptr(nullptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator && other) noexcept(true) : m_ptr(other.m_ptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator const& other) noexcept(NoExceptCopy) : m_ptr(other.m_ptr) {}
};

static_assert(hamon::is_same<decltype(*hamon::declval<hamon::reverse_iterator<int*>>()), int&>::value, "");
static_assert(hamon::is_same<decltype(*hamon::declval<hamon::reverse_iterator<char const*>>()), char const&>::value, "");
static_assert(hamon::is_same<decltype(*hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true>>>()), float>::value, "");

static_assert( noexcept(*hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(*hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true>>>()), "");
static_assert(!noexcept(*hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true>>>()), "");
static_assert(!noexcept(*hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true>>>()), "");
static_assert(!noexcept(*hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false>>>()), "");
static_assert(!noexcept(*hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false>>>()), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {10,20,30};
	{
		hamon::reverse_iterator<int*> it(&a[1]);
		VERIFY(*it == a[0]);
	}
	{
		hamon::reverse_iterator<int*> it(&a[2]);
		VERIFY(*it == a[1]);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, dereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace dereference_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
