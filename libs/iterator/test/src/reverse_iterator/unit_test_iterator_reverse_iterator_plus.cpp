/**
 *	@file	unit_test_iterator_reverse_iterator_plus.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	constexpr reverse_iterator operator+(difference_type n) const;
 * 
 *	template<class Iterator>
 *	constexpr reverse_iterator<Iterator> operator+(
 *		iter_difference_t<Iterator> n,
 *		const reverse_iterator<Iterator>& x);
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace plus_test {

template <bool NoExceptMove, bool NoExceptPlus, bool NoExceptMinus>
struct TestIterator
{
	using T = float;
	T*	m_ptr;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR TestIterator operator+(difference_type n) const noexcept(NoExceptPlus) { return {m_ptr + n}; }
	HAMON_CXX11_CONSTEXPR TestIterator operator-(difference_type n) const noexcept(NoExceptMinus) { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR T&           operator*() const noexcept { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR TestIterator() noexcept(true) : m_ptr(nullptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator && other) noexcept(NoExceptMove) : m_ptr(other.m_ptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator const& other) noexcept(true) : m_ptr(other.m_ptr) {}
};

static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<int*>>() + hamon::declval<int>()), hamon::reverse_iterator<int*>>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true>>>() + hamon::declval<int>()), hamon::reverse_iterator<TestIterator<true, true, true>>>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<int*>>()), hamon::reverse_iterator<int*>>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true>>>()), hamon::reverse_iterator<TestIterator<true, true, true>>>::value, "");

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() + hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true >>>() + hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false>>>() + hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true >>>() + hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, false>>>() + hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true >>>() + hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  false>>>() + hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, true >>>() + hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false>>>() + hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true >>>()), "");
static_assert(!noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false>>>()), "");
static_assert( noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true >>>()), "");
static_assert(!noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, false>>>()), "");
static_assert(!noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true >>>()), "");
static_assert(!noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  false>>>()), "");
static_assert(!noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<false, false, true >>>()), "");
static_assert(!noexcept(hamon::declval<int>() + hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false>>>()), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {1,2,3,4,5};
	hamon::reverse_iterator<int*> it(&a[5]);
	VERIFY(*it == 5);
	auto t1 = it + 2;
	VERIFY(*t1 == 3);
	auto t2 = 3 + it;
	VERIFY(*t2 == 2);
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, PlusTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace plus_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
