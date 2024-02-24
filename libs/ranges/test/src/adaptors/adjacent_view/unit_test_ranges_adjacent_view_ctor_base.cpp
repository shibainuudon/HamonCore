/**
 *	@file	unit_test_ranges_adjacent_view_ctor_base.cpp
 *
 *	@brief	baseを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit adjacent_view(V base);
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace ctor_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using AV = hamon::ranges::adjacent_view<V, 3>;

	static_assert( hamon::is_constructible<AV, V>::value, "");
	static_assert(!hamon::is_constructible<AV, int>::value, "");
	static_assert(!hamon::is_constructible<AV, V, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<AV, V>::value, "");

	int a[] = {1,2,3};
	V v(a);
	AV av{v};
	(void)av;
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewCtorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_base_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
