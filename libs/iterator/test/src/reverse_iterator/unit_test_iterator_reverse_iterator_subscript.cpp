/**
 *	@file	unit_test_iterator_reverse_iterator_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr unspecified operator[](difference_type n) const;
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace subscript_test {

template <typename T, bool NoExceptSubscript>
struct TestIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T;
	HAMON_CXX11_CONSTEXPR T operator*() const noexcept(true) { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T operator[](difference_type i) const noexcept(NoExceptSubscript) { return m_ptr[i]; }
};

struct ThrowOnCopy
{
	ThrowOnCopy(ThrowOnCopy &&) noexcept(true) {}
	ThrowOnCopy(ThrowOnCopy const&) noexcept(false) {}
};

static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<int*>>()[0]), int&>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<int const*>>()[0]), int const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>()[0]), int&>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<int, true>>>()[0]), int>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<float, true>>>()[0]), float>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<TestIterator<ThrowOnCopy, true>>>()[0]), ThrowOnCopy>::value, "");

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>()[0]), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>()[0]), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<int, true>>>()[0]), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<int, false>>>()[0]), "");
// TODO
//static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<ThrowOnCopy, true>>>()[0]), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<ThrowOnCopy, false>>>()[0]), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {1,2,3,4,5};
	hamon::reverse_iterator<int*> it(&a[4]);
	VERIFY(it[0] == 4);
	VERIFY(it[1] == 3);
	VERIFY(it[2] == 2);
	VERIFY(it[3] == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, SubscriptTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace subscript_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
