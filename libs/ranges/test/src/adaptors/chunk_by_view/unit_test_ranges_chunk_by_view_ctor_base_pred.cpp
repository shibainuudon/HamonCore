/**
 *	@file	unit_test_ranges_chunk_by_view_ctor_base_pred.cpp
 *
 *	@brief	baseとpredを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit chunk_by_view(V base, Pred pred);
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace ctor_base_pred_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using F = hamon::ranges::less;
	using V = test_forward_view<int>;
	using CV = hamon::ranges::chunk_by_view<V, F>;

	static_assert( hamon::is_constructible<CV, V, F>::value, "");
	static_assert(!hamon::is_constructible<CV, V>::value, "");
	static_assert(!hamon::is_constructible<CV, F>::value, "");
	static_assert(!hamon::is_constructible<CV, V, F, int>::value, "");

	static_assert(!hamon::is_implicitly_constructible<CV, V, F>::value, "");

	int a[] = {1,2,3};
	V v(a);
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::chunk_by_view cv{v, F{}};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{v, F{}};
#endif
	(void)cv;

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<hamon::ranges::ref_view<int[3]>, F>;

	int a[] = {1,2,3};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::chunk_by_view cv{a, F{}};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{a, F{}};
#endif
	(void)cv;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewCtorBasePredTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_base_pred_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
