/**
 *	@file	unit_test_iterator_reverse_iterator_plus_assign.cpp
 *
 *	@brief	operator+= のテスト
 *
 *	constexpr reverse_iterator& operator+=(difference_type n);
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace plus_assign_test {

template <bool NoExceptPlus, bool NoExceptMinus>
struct TestIterator
{
	using T = float;
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR void operator+=(difference_type n) noexcept(NoExceptPlus) { m_ptr += n; }
	HAMON_CXX14_CONSTEXPR void operator-=(difference_type n) noexcept(NoExceptMinus) { m_ptr -= n; }
	HAMON_CXX11_CONSTEXPR T&   operator*() const noexcept { return *m_ptr; }
};

static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<int*>>() += hamon::declval<int>()), hamon::reverse_iterator<int*>&>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true >>>() += hamon::declval<int>()), hamon::reverse_iterator<TestIterator<true,  true >>&>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false>>>() += hamon::declval<int>()), hamon::reverse_iterator<TestIterator<true,  false>>&>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<false, true >>>() += hamon::declval<int>()), hamon::reverse_iterator<TestIterator<false, true >>&>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<false, false>>>() += hamon::declval<int>()), hamon::reverse_iterator<TestIterator<false, false>>&>::value, "");

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() += hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  true >>>() += hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true,  false>>>() += hamon::declval<int>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, true >>>() += hamon::declval<int>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<false, false>>>() += hamon::declval<int>()), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {1,2,3,4,5};
	hamon::reverse_iterator<int*> it(&a[5]);
	VERIFY(*it == 5);
	auto t1 = it += 2;
	VERIFY(*it == 3);
	VERIFY(*t1 == 3);
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, PlusAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace plus_assign_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
