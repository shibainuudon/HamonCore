/**
 *	@file	unit_test_iterator_reverse_iterator_arrow.cpp
 *
 *	@brief	operator-> のテスト
 *
 *	constexpr pointer operator->() const;
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace arrow_test {

template <bool NoExceptCopy, bool NoExceptArrow, bool NoExceptDecrement>
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
	HAMON_CXX11_CONSTEXPR T&            operator*() const noexcept(true) { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T*            operator->() const noexcept(NoExceptArrow) { return m_ptr; }
	HAMON_CXX11_CONSTEXPR TestIterator() noexcept(true) : m_ptr(nullptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator && other) noexcept(true) : m_ptr(other.m_ptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator const& other) noexcept(NoExceptCopy) : m_ptr(other.m_ptr) {}
};

template <typename T, typename = void>
struct has_arrow
	: public hamon::false_type {};

template <typename T>
struct has_arrow<T, hamon::void_t<decltype(hamon::declval<T>().operator->())>>
	: public hamon::true_type {};

static_assert( has_arrow<hamon::reverse_iterator<int*>>::value, "");
static_assert(!has_arrow<hamon::reverse_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!has_arrow<hamon::reverse_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert(!has_arrow<hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert(!has_arrow<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( has_arrow<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value, "");
static_assert( has_arrow<hamon::reverse_iterator<TestIterator<true,  true,  true>>>::value, "");
static_assert( has_arrow<hamon::reverse_iterator<TestIterator<false, true,  true>>>::value, "");
static_assert( has_arrow<hamon::reverse_iterator<TestIterator<true,  false, true>>>::value, "");
static_assert( has_arrow<hamon::reverse_iterator<TestIterator<true,  true,  false>>>::value, "");
static_assert( has_arrow<hamon::reverse_iterator<TestIterator<false, false, false>>>::value, "");

static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<int*>>().operator->()), int*>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<char const*>>().operator->()), char const*>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>().operator->()), int*>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true>>>().operator->()), float*>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true>>>().operator->()), float*>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true>>>().operator->()), float*>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false>>>().operator->()), float*>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false>>>().operator->()), float*>::value, "");

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>().operator->()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true>>>().operator->()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true>>>().operator->()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true>>>().operator->()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false>>>().operator->()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false>>>().operator->()), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {10,20,30};
	{
		hamon::reverse_iterator<int*> it(&a[1]);
		VERIFY(it.operator->() == &a[0]);
	}
	{
		hamon::reverse_iterator<int*> it(&a[2]);
		VERIFY(it.operator->() == &a[1]);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	long const a[] = {31,32};
	using I = contiguous_iterator_wrapper<long const>;
	I i{&a[1]};
	hamon::reverse_iterator<I> it{i};
	VERIFY(it.operator->() == &a[0]);
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, ArrowTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace arrow_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
