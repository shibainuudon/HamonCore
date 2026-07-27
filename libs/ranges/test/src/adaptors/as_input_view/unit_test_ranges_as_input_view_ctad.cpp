/**
 *	@file	unit_test_ranges_as_input_view_ctad.cpp
 *
 *	@brief	推論補助のテスト
 *
 *	template<class R>
 *	as_input_view(R&&) -> as_input_view<views::all_t<R>>;
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/adaptors/owning_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::array<int, 3> a{6,7,8};
	hamon::ranges::as_input_view aiv{ a };
	static_assert(hamon::is_same<
		decltype(aiv),
		hamon::ranges::as_input_view<
			hamon::ranges::ref_view<hamon::array<int, 3>>
		>
	>::value, "");

	const int expected[] = {6,7,8};
	VERIFY(hamon::ranges::equal(aiv, expected));
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::as_input_view aiv{hamon::array<int, 4>{1,2,3,4}};
	static_assert(hamon::is_same<
		decltype(aiv),
		hamon::ranges::as_input_view<
			hamon::ranges::owning_view<hamon::array<int, 4>>
		>
	>::value, "");

	const int expected[] = {1,2,3,4};
	VERIFY(hamon::ranges::equal(aiv, expected));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewCtadTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctad_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
