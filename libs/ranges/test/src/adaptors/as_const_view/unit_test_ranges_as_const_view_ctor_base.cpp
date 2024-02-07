/**
 *	@file	unit_test_ranges_as_const_view_ctor_base.cpp
 *
 *	@brief	baseを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit as_const_view(V base);
 */

#include <hamon/ranges/adaptors/as_const_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_const_view_test
{
namespace ctor_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using CV = hamon::ranges::as_const_view<V>;

	static_assert( hamon::is_constructible<CV, V>::value, "");
	static_assert(!hamon::is_constructible<CV, int>::value, "");
	static_assert(!hamon::is_constructible<CV, V, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<CV, V>::value, "");
	
	int a[] = {1,2,3};
	V v(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::as_const_view cv{v};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{v};
#endif

	VERIFY(*(cv.begin()) == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsConstViewCtorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_base_test
}	// namespace as_const_view_test
}	// namespace hamon_ranges_test
