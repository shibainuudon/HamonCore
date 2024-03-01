/**
 *	@file	unit_test_ranges_slide_view_ctor_base_n.cpp
 *
 *	@brief	baseとnを引数に取るコンスタラクタのテスト
 *
 *	constexpr explicit slide_view(V base, range_difference_t<V> n);
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace ctor_base_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using D = hamon::ranges::range_difference_t<V>;
	using SV = hamon::ranges::slide_view<V>;

	static_assert(!hamon::is_constructible<SV>::value, "");
	static_assert(!hamon::is_constructible<SV, V>::value, "");
	static_assert(!hamon::is_constructible<SV, D>::value, "");
	static_assert( hamon::is_constructible<SV, V, D>::value, "");
	static_assert(!hamon::is_constructible<SV, V, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<SV, V, D>::value, "");

	int a[] = {1,2,3};
	V v(a);
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::slide_view sv{v, 2};
	static_assert(hamon::is_same<decltype(sv), SV>::value, "");
#else
	SV sv{v, 2};
#endif
	VERIFY(sv.begin() != sv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using SV = hamon::ranges::slide_view<hamon::views::all_t<int(&)[4]>>;

	int a[] = {1,2,3,4};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::slide_view sv{a, 2};
	static_assert(hamon::is_same<decltype(sv), SV>::value, "");
#else
	SV sv{a, 2};
#endif
	VERIFY(sv.begin() != sv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewCtorBaseNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_base_n_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
