/**
 *	@file	unit_test_iterator_reverse_iterator_minus.cpp
 *
 *	@brief	operator- のテスト
 *
 *	constexpr reverse_iterator operator-(difference_type n) const;
 * 
 *	template<class Iterator1, class Iterator2>
 *	constexpr auto operator-(
 *		const reverse_iterator<Iterator1>& x,
 *		const reverse_iterator<Iterator2>& y) -> decltype(y.base() - x.base());
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace minus_test {

template <bool NoExceptMove, bool NoExceptPlus, bool NoExceptMinus, bool NoExceptSubtract>
struct TestIterator
{
	using T = float;
	T*	m_ptr;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR TestIterator    operator+(difference_type n) const noexcept(NoExceptPlus) { return {m_ptr + n}; }
	HAMON_CXX11_CONSTEXPR TestIterator    operator-(difference_type n) const noexcept(NoExceptMinus) { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type operator-(TestIterator const& rhs) const noexcept(NoExceptSubtract) { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR T&              operator*() const noexcept { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR TestIterator() noexcept(true) : m_ptr(nullptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator && other) noexcept(NoExceptMove) : m_ptr(other.m_ptr) {}
	HAMON_CXX11_CONSTEXPR TestIterator(TestIterator const& other) noexcept(true) : m_ptr(other.m_ptr) {}
};

static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<int*>>() - hamon::declval<int>()), hamon::reverse_iterator<int*>>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true, true>>>() - hamon::declval<int>()), hamon::reverse_iterator<TestIterator<true, true, true, true>>>::value, "");

static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<int*>>() - hamon::declval<hamon::reverse_iterator<int*>>()), hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true, true>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true, true, true, true>>>()), hamon::ptrdiff_t>::value, "");

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() - hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true,  true >>>() - hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true,  false>>>() - hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false, true >>>() - hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false, false>>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true,  true >>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true,  false>>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, false, true >>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, false, false>>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true,  true >>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true,  false>>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  false, true >>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  false, false>>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, true,  true >>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, true,  false>>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false, true >>>() - hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false, false>>>() - hamon::declval<int>()), "");

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() - hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true,  true >>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true,  true >>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true,  false>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  true,  false>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false, true >>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false, true >>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false, false>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true,  true,  false, false>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true,  true >>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true,  true >>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true,  false>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, true,  false>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, false, true >>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, false, true >>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, false, false>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<true,  false, false, false>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true,  true >>>() - hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true,  true >>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true,  false>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  true,  false>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  false, true >>>() - hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  false, true >>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  false, false>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<false, true,  false, false>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, true,  true >>>() - hamon::declval<hamon::reverse_iterator<TestIterator<false, false, true,  true >>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, true,  false>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<false, false, true,  false>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false, true >>>() - hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false, true >>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false, false>>>() - hamon::declval<hamon::reverse_iterator<TestIterator<false, false, false, false>>>()), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {1,2,3,4,5};
	hamon::reverse_iterator<int*> it(&a[1]);
	VERIFY(*it == 1);
	auto t1 = it - 3;
	VERIFY(*it == 1);
	VERIFY(*t1 == 4);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1,2,3,4,5};
	hamon::reverse_iterator<int*> it1(&a[1]);
	hamon::reverse_iterator<int*> it2(&a[4]);
	VERIFY((it1 - it2) == 3);
	VERIFY((it2 - it1) == -3);
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, MinusTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace minus_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
