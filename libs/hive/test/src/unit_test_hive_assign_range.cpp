/**
 *	@file	unit_test_hive_assign_range.cpp
 *
 *	@brief	assign_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	void assign_range(R&& rg);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_hive_test
{

namespace assign_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Hive = hamon::hive<T>;
	using Range = RangeWrapper<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().assign_range(hamon::declval<Range>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().assign_range(hamon::declval<Range>())), "");

	Hive v;

	{
		T a[] = {1,2,3,4};
		v.assign_range(Range{a});
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
	}
	{
		T a[] = {5,6,7};
		v.assign_range(Range{a});
		VERIFY(v.size() == 3u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{18});
	}
	{
		T a[] = {5,4,3,2,1,0};
		v.assign_range(Range{a});
		VERIFY(v.size() == 6u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{15});
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return
		test_impl<T, test_input_range>() &&
		test_impl<T, test_forward_range>() &&
		test_impl<T, test_bidirectional_range>() &&
		test_impl<T, test_random_access_range>() &&
		test_impl<T, test_contiguous_range>() &&
		test_impl<T, test_input_sized_range>() &&
		test_impl<T, test_forward_sized_range>() &&
		test_impl<T, test_bidirectional_sized_range>() &&
		test_impl<T, test_random_access_sized_range>() &&
		test_impl<T, test_contiguous_sized_range>();
}

#undef VERIFY

GTEST_TEST(HiveTest, AssignRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace assign_range_test

}	// namespace hamon_hive_test
