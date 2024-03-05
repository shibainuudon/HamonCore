/**
 *	@file	unit_test_ranges_chunk_by_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end();
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;

	int a[] = {1,2,3};
	V v(a);
	CV cv(v, F{});
	auto sent = cv.end();
	VERIFY(sent != cv.begin());

	static_assert(!hamon::is_same<decltype(sent), decltype(cv.begin())>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_common_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;

	int a[] = {1,2,3};
	V v(a);
	CV cv(v, F{});
	auto sent = cv.end();
	VERIFY(sent != cv.begin());

	static_assert( hamon::is_same<decltype(sent), decltype(cv.begin())>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace end_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
