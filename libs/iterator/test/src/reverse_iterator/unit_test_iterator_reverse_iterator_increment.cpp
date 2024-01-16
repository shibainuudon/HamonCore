/**
 *	@file	unit_test_iterator_reverse_iterator_increment.cpp
 *
 *	@brief	operator++ のテスト
 *
 *	constexpr reverse_iterator& operator++();
 *	constexpr reverse_iterator  operator++(int);
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace increment_test {

template <bool NoExceptCopy, bool NoExceptIncrement, bool NoExceptDecrement>
struct TestIterator
{
	using T = float;
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestIterator& operator++() noexcept(NoExceptIncrement) { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator--() noexcept(NoExceptDecrement) { --m_ptr; return *this; }
	HAMON_CXX11_CONSTEXPR T&            operator*() const noexcept { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR TestIterator() noexcept(true) : m_ptr(nullptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator && other) noexcept(true) : m_ptr(other.m_ptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator const& other) noexcept(NoExceptCopy) : m_ptr(other.m_ptr) {}
};

static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<int*>>()++), hamon::reverse_iterator<int*>>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<char const*>>()++), hamon::reverse_iterator<char const*>>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true>>>()++), hamon::reverse_iterator<TestIterator<true, true, true>>>::value, "");

static_assert(hamon::is_same<decltype(++hamon::declval<hamon::reverse_iterator<int*>>()), hamon::reverse_iterator<int*>&>::value, "");
static_assert(hamon::is_same<decltype(++hamon::declval<hamon::reverse_iterator<char const*>>()), hamon::reverse_iterator<char const*>&>::value, "");
static_assert(hamon::is_same<decltype(++hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true>>>()), hamon::reverse_iterator<TestIterator<true, true, true>>&>::value, "");

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>()++), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true >>>()++), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true >>>()++), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true >>>()++), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false>>>()++), "");

static_assert( noexcept(++hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(++hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true >>>()), "");
static_assert( noexcept(++hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true >>>()), "");
static_assert( noexcept(++hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true >>>()), "");
static_assert(!noexcept(++hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false>>>()), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {1,2,3,4,5};
	hamon::reverse_iterator<int*> it(&a[5]);
	VERIFY(*it == 5);
	auto t1 = ++it;
	VERIFY(*it == 4);
	VERIFY(*t1 == 4);
	auto t2 = it++;
	VERIFY(*it == 3);
	VERIFY(*t2 == 4);
	auto t3 = ++it;
	VERIFY(*it == 2);
	VERIFY(*t3 == 2);
	auto t4 = it++;
	VERIFY(*it == 1);
	VERIFY(*t4 == 2);
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, IncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace increment_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
