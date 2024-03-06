/**
 *	@file	unit_test_ranges_stride_view_stride.cpp
 *
 *	@brief	stride() のテスト
 *
 *	constexpr range_difference_t<V> stride() const noexcept;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace stride_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = View<int>;
	using D = hamon::ranges::range_difference_t<V>;
	using SV = hamon::ranges::stride_view<V>;

	static_assert(hamon::is_same<D, decltype(hamon::declval<SV const&>().stride())>::value, "");

	int a[] = {1,2,3,4,5,6,7,8,9};
	V v(a);

	{
		SV sv{v, 1};
		VERIFY(sv.stride() == 1);
	}
	{
		SV sv{v, 2};
		VERIFY(sv.stride() == 2);
	}
	{
		SV sv{v, 3};
		VERIFY(sv.stride() == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewStrideTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
}

}	// namespace stride_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
