/**
 *	@file	unit_test_ranges_zip_transform_view_ctor_fun_views.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	constexpr explicit zip_transform_view(F fun, Views... views);
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace ctor_fun_views_test
{

struct Add
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using F = Add;
	using V1 = test_input_view<int>;
	using V2 = test_forward_view<int>;
	using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

	static_assert( hamon::is_constructible<ZV, F, V1, V2>::value, "");
	static_assert(!hamon::is_constructible<ZV, V1, V2>::value, "");
	static_assert(!hamon::is_constructible<ZV, F, V1>::value, "");
	static_assert(!hamon::is_constructible<ZV, F, V2>::value, "");
	static_assert(!hamon::is_constructible<ZV, F, V2, V1>::value, "");

	static_assert(!hamon::is_implicitly_constructible<ZV, F, V1, V2>::value, "");

	F f;
	int a1[] = {1,2,3};
	int a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::zip_transform_view zv{f, v1, v2};
	static_assert(hamon::is_same<decltype(zv), ZV>::value, "");
#else
	ZV zv{f, v1, v2};
#endif
	(void)zv;

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using F = Add;
	using ZV = hamon::ranges::zip_transform_view<
		F,
		hamon::ranges::ref_view<int[3]>,
		hamon::ranges::ref_view<int[4]>>;

	F f;
	int a1[] = {1,2,3};
	int a2[] = {1,2,3,4};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::zip_transform_view zv{f, a1, a2};
	static_assert(hamon::is_same<decltype(zv), ZV>::value, "");
#else
	ZV zv{f, a1, a2};
#endif
	(void)zv;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewCtorFunViewsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_fun_views_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
