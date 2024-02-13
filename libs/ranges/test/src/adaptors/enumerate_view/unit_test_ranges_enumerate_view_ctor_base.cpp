/**
 *	@file	unit_test_ranges_enumerate_view_ctor_base.cpp
 *
 *	@brief	baseを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit enumerate_view(V base);
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace ctor_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;

	static_assert( hamon::is_constructible<EV, V>::value, "");
	static_assert(!hamon::is_constructible<EV, int>::value, "");
	static_assert(!hamon::is_constructible<EV, V, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<EV, V>::value, "");

	int a[] = {1,2,3};
	V v(a);
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::enumerate_view ev{v};
	static_assert(hamon::is_same<decltype(ev), EV>::value, "");
#else
	EV ev{v};
#endif
	(void)ev;

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using EV = hamon::ranges::enumerate_view<hamon::ranges::ref_view<int[3]>>;

	int a[] = {1,2,3};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::enumerate_view ev{a};
	static_assert(hamon::is_same<decltype(ev), EV>::value, "");
#else
	EV ev{a};
#endif
	(void)ev;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewCtorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_base_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
