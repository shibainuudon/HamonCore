/**
 *	@file	unit_test_ranges_split_view_ctor_base_pattern.cpp
 *
 *	@brief	baseとpatternを受け取るコンストラクタのテスト
 *
 *	constexpr explicit split_view(V base, Pattern pattern);
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace ctor_base_pattern_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<char>;
	using RV = hamon::ranges::split_view<V, P>;

	static_assert( hamon::is_constructible<RV, V, P>::value, "");
	static_assert(!hamon::is_constructible<RV, P, V>::value, "");
	static_assert(!hamon::is_constructible<RV, V>::value, "");
	static_assert(!hamon::is_constructible<RV, P>::value, "");

	static_assert(!hamon::is_implicitly_constructible<RV, V, P>::value, "");

	// TODO
//	static_assert( hamon::is_nothrow_constructible<RV, V, P>::value, "");
	
	int a1[] = {1, 2, 3, 4, 5};
	char a2[] = {0};
	V v(a1);
	P p(a2);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::split_view rv(v, p);
	static_assert(hamon::is_same<decltype(rv), RV>::value, "");
#else
	RV rv(v, p);
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewCtorBasePatternTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_base_pattern_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
