/**
 *	@file	unit_test_ranges_stride_view_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	constexpr explicit stride_view(V base, range_difference_t<V> stride);
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace ctor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using D = hamon::ranges::range_difference_t<V>;
	using SV = hamon::ranges::stride_view<V>;

	static_assert(!hamon::is_constructible<SV>::value, "");
	static_assert(!hamon::is_constructible<SV, V>::value, "");
	static_assert(!hamon::is_constructible<SV, D>::value, "");
	static_assert( hamon::is_constructible<SV, V, D>::value, "");
	static_assert(!hamon::is_constructible<SV, D, V>::value, "");
	static_assert(!hamon::is_constructible<SV, V, D, int>::value, "");

	static_assert(!hamon::is_implicitly_constructible<SV, V, D>::value, "");

	int a[] = {1,2,3};
	V v(a);
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::stride_view sv{v, 2};
	static_assert(hamon::is_same<decltype(sv), SV>::value, "");
#else
	SV sv{v, 2};
#endif
	(void)sv;

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = hamon::ranges::ref_view<int[3]>;
	using D = hamon::ranges::range_difference_t<V>;
	using SV = hamon::ranges::stride_view<V>;

	static_assert(!hamon::is_constructible<SV>::value, "");
	static_assert(!hamon::is_constructible<SV, V>::value, "");
	static_assert(!hamon::is_constructible<SV, D>::value, "");
	static_assert( hamon::is_constructible<SV, V, D>::value, "");
	static_assert( hamon::is_constructible<SV, int(&)[3], D>::value, "");
	static_assert(!hamon::is_constructible<SV, D, V>::value, "");
	static_assert(!hamon::is_constructible<SV, V, D, int>::value, "");

	static_assert(!hamon::is_implicitly_constructible<SV, V, D>::value, "");

	int a[] = {1,2,3};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::stride_view sv{a, 2};
	static_assert(hamon::is_same<decltype(sv), SV>::value, "");
#else
	SV sv{a, 2};
#endif
	(void)sv;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewCtorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
