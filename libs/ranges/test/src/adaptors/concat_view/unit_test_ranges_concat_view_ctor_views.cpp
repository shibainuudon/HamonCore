/**
 *	@file	unit_test_ranges_concat_view_ctor_views.cpp
 *
 *	@brief	views を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit concat_view(Views... views);
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace ctor_views_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V1 = test_input_view<int>;
	using V2 = test_forward_view<int>;
	using CV = hamon::ranges::concat_view<V1, V2>;

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
	hamon::ranges::concat_view cv{v1, v2};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{v1, v2};
#endif

	int const expected[] = {1,2,3,1,2,3,4};
	VERIFY(hamon::ranges::equal(cv, expected));

	return true;
}

HAMON_CXX20_CONSTEXPR bool test01()
{
	hamon::vector<int> v{ 1, 2, 3 };
	hamon::list<int> l{ 4, 5 };
	hamon::array<int, 3> a{ 6, 7, 8 };

	using CV = hamon::ranges::concat_view<
		hamon::ranges::ref_view<hamon::vector<int>>,
		hamon::ranges::ref_view<hamon::list<int>>,
		hamon::ranges::ref_view<hamon::array<int, 3>>
	>;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::concat_view cv{ v, l, a };
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{ v, l, a };
#endif

	int const expected[] = {1,2,3,4,5,6,7,8};
	VERIFY(hamon::ranges::equal(cv, expected));

	return true;
}

HAMON_CXX20_CONSTEXPR bool test02()
{
	auto con = {'c', 'o', 'n'};
    char cat[]{'c', 'a', 't', '\0'};
    auto cv{hamon::views::concat(con, cat)};
    VERIFY(hamon::ranges::equal(cv, "concat"));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewCtorViewsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace ctor_views_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
