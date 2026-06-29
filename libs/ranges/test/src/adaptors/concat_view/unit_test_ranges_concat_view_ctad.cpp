/**
 *	@file	unit_test_ranges_concat_view_ctad.cpp
 *
 *	@brief	推論補助のテスト
 *
 *	template<class... R>
 *	concat_view(R&&...) -> concat_view<views::all_t<R>...>;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/adaptors/owning_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test00()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::vector<int> v1{ 1, 2, 3 };
	hamon::vector<int> v2{ 4, 5 };
	hamon::array<int, 3> a{ 6, 7, 8 };

	hamon::ranges::concat_view cv{ v1, v2, a };
	static_assert(hamon::is_same<
		decltype(cv),
		hamon::ranges::concat_view<
		hamon::ranges::ref_view<hamon::vector<int>>,
		hamon::ranges::ref_view<hamon::vector<int>>,
		hamon::ranges::ref_view<hamon::array<int, 3>>
		>
	>::value, "");

	const int expected[] = {1,2,3,4,5,6,7,8};
	VERIFY(hamon::ranges::equal(cv, expected));
#endif

	return true;
}

HAMON_CXX20_CONSTEXPR bool test01()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::concat_view cv{
		hamon::vector<int>{1, 2, 3},
		hamon::vector<int>{4, 5},
		hamon::array<int, 3>{6, 7, 8}
	};
	static_assert(hamon::same_as<
		decltype(cv),
		hamon::ranges::concat_view<
		hamon::ranges::owning_view<hamon::vector<int>>,
		hamon::ranges::owning_view<hamon::vector<int>>,
		hamon::ranges::owning_view<hamon::array<int, 3>>
		>
	>);

	const int expected[] = {1,2,3,4,5,6,7,8};
	VERIFY(hamon::ranges::equal(cv, expected));
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewCtadTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctad_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
