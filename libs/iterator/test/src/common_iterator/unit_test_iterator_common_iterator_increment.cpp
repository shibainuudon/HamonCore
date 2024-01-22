/**
 *	@file	unit_test_iterator_common_iterator_increment.cpp
 *
 *	@brief	operator++ のテスト
 *
 *	constexpr common_iterator& operator++();
 *	constexpr decltype(auto) operator++(int);
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace increment_test {

template <typename T>
struct TestIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T&            operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const TestIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestIterator& rhs) const { return !(*this == rhs); }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// forward_iterator<I>

	using CI = hamon::common_iterator<int*, hamon::unreachable_sentinel_t>;
	int a[] = {1, 2, 3};
	CI it{&a[0]};

	static_assert(hamon::is_same<decltype(++it), CI&>::value, "");
	static_assert(hamon::is_same<decltype(it++), CI>::value, "");

	VERIFY(*it == 1);
	auto t1 = ++it;
	VERIFY(*t1 == 2);
	VERIFY(*it == 2);
	auto t2 = it++;
	VERIFY(*t2 == 2);
	VERIFY(*it == 3);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// not forward_iterator<I> &&
	// requires(I& i) {{ *i++ } -> hamon::detail::can_reference; }

	using I = input_iterator_wrapper<int>;
	using CI = hamon::common_iterator<I, hamon::unreachable_sentinel_t>;
	int a[] = {1, 2, 3};
	CI it{I{&a[0]}};

	static_assert(hamon::is_same<decltype(++it), CI&>::value, "");
	static_assert(!hamon::is_same<decltype(it++), CI>::value, "");

	VERIFY(*it == 1);
	auto t1 = ++it;
	VERIFY(*t1 == 2);
	VERIFY(*it == 2);
	auto t2 = it++;
	VERIFY(*t2 == 2);
	VERIFY(*it == 3);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// not forward_iterator<I> &&
	// not requires(I& i) {{ *i++ } -> hamon::detail::can_reference; }

	using I = TestIterator<int>;
	using CI = hamon::common_iterator<I, hamon::unreachable_sentinel_t>;
	int a[] = {1, 2, 3};
	CI it{I{&a[0]}};

	static_assert(hamon::is_same<decltype(++it), CI&>::value, "");
	static_assert(hamon::is_same<decltype(it++), I>::value, "");

	VERIFY(*it == 1);
	auto t1 = ++it;
	VERIFY(*t1 == 2);
	VERIFY(*it == 2);
	auto t2 = it++;
	VERIFY(*t2 == 2);
	VERIFY(*it == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, IncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace increment_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
