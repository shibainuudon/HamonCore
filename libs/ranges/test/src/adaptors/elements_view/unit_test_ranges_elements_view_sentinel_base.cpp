/**
 *	@file	unit_test_ranges_elements_view_sentinel_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr sentinel_t<Base> base() const;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace sentinel_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using S = hamon::ranges::sentinel_t<EV>;
		using BaseSent = hamon::ranges::sentinel_t<V>;

		static_assert(hamon::is_same<decltype(hamon::declval<S&>().base()), BaseSent>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<S const&>().base()), BaseSent>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev{v};

		auto sent = ev.end();
		VERIFY(sent.base() == v.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewSentinelBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_base_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
