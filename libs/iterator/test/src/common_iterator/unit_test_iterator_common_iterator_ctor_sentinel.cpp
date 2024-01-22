/**
 *	@file	unit_test_iterator_common_iterator_ctor_sentinel.cpp
 *
 *	@brief	センチネルからのコンストラクタのテスト
 *
 *	constexpr common_iterator(S s);
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace ctor_sentinel_test {

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

static_assert( hamon::is_constructible<hamon::common_iterator<int*, hamon::unreachable_sentinel_t>, hamon::unreachable_sentinel_t>::value, "");
static_assert(!hamon::is_constructible<hamon::common_iterator<int*, hamon::unreachable_sentinel_t>, int const*>::value, "");
static_assert(!hamon::is_constructible<hamon::common_iterator<int*, int const*>, hamon::unreachable_sentinel_t>::value, "");
static_assert( hamon::is_constructible<hamon::common_iterator<int*, int const*>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::common_iterator<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>, test_sentinel<input_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::is_constructible<hamon::common_iterator<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>, test_sentinel<input_iterator_wrapper<int const>>>::value, "");

HAMON_CXX14_CONSTEXPR bool test00()
{
	using I = input_iterator_wrapper<int>;
	using S = test_sentinel<I>;
	int a[] = {1, 2, 3};
	hamon::common_iterator<I, S> it1{I{&a[0]}};
	hamon::common_iterator<I, S> it2{S{&a[3]}};
	VERIFY(it1 != it2);
	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, CtorSentinelTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_sentinel_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
