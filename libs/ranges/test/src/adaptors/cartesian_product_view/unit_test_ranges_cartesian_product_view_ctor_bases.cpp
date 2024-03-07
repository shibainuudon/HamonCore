/**
 *	@file	unit_test_ranges_cartesian_product_view_ctor_bases.cpp
 *
 *	@brief	basesを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit cartesian_product_view(First first_base, Vs... bases);
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace ctor_bases_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V1 = test_input_view<int>;
	using V2 = test_forward_view<int>;
	using CV = hamon::ranges::cartesian_product_view<V1, V2>;

	static_assert( hamon::is_constructible<CV, V1, V2>::value, "");
	static_assert(!hamon::is_constructible<CV, V1>::value, "");
	static_assert(!hamon::is_constructible<CV, V2>::value, "");
	static_assert(!hamon::is_constructible<CV, V2, V1>::value, "");

	static_assert(!hamon::is_implicitly_constructible<CV, V1, V2>::value, "");

	int a1[] = {1,2,3};
	int a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::cartesian_product_view cv{v1, v2};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{v1, v2};
#endif
	(void)cv;

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using CV = hamon::ranges::cartesian_product_view<
		hamon::ranges::ref_view<int[3]>,
		hamon::ranges::ref_view<int[4]>>;

	int a1[] = {1,2,3};
	int a2[] = {1,2,3,4};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::cartesian_product_view cv{a1, a2};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{a1, a2};
#endif
	(void)cv;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewCtorBasesTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_bases_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
