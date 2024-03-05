/**
 *	@file	unit_test_ranges_chunk_by_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr value_type operator*() const;
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace iterator_dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;
	using I = decltype(hamon::declval<CV&>().begin());
	static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), typename I::value_type>::value, "");

	int a[] = {1,2,4,0,1,2};
	V v(a);
	CV cv(v, F{});
	auto it = cv.begin();
	int expected[] = {1,2,4};
	VERIFY(hamon::ranges::equal(*it, expected));
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
