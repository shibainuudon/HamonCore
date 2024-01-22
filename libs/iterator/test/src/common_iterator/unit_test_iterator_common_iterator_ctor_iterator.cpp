/**
 *	@file	unit_test_iterator_common_iterator_ctor_iterator.cpp
 *
 *	@brief	イテレータからのコンストラクタのテスト
 *
 *	constexpr common_iterator(I i);
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace ctor_iterator_test {

static_assert( hamon::is_constructible<hamon::common_iterator<int*, hamon::unreachable_sentinel_t>, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::common_iterator<int*, hamon::unreachable_sentinel_t>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::common_iterator<int const*, hamon::unreachable_sentinel_t>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::common_iterator<int const*, hamon::unreachable_sentinel_t>, int const*>::value, "");
static_assert(!hamon::is_constructible<hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>, input_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>, input_iterator_wrapper<int const>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int n = 42;
	hamon::common_iterator<int*, int const*> it{&n};
	VERIFY(it.operator->() == &n);
	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, CtorIteratorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_iterator_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
