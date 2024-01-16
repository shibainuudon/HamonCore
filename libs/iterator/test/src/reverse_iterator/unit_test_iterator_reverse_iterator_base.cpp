/**
 *	@file	unit_test_iterator_reverse_iterator_assign.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr Iterator base() const;
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace base_test {

struct ThrowOnCopy
{
	using T = int;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	int operator*() { return 0; }
	ThrowOnCopy(ThrowOnCopy &&) noexcept(true) {}
	ThrowOnCopy(ThrowOnCopy const&) noexcept(false) {}
};

static_assert(hamon::is_same<decltype(hamon::declval<hamon::reverse_iterator<ThrowOnCopy>&>().base()), ThrowOnCopy>::value, "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<ThrowOnCopy>&>().base()), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int n = 0;
	hamon::reverse_iterator<int*> const it(&n);
	VERIFY(it.base() == &n);
	static_assert(hamon::is_same<decltype(it.base()), int*>::value, "");
	static_assert(noexcept(it.base()), "");
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, BaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace base_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
