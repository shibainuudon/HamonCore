/**
 *	@file	unit_test_hive_assign_n_value.cpp
 *
 *	@brief	assign のテスト
 *
 *	void assign(size_type n, const T& x);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace assign_n_value_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().assign(hamon::declval<SizeType>(), hamon::declval<T const&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().assign(hamon::declval<SizeType>(), hamon::declval<T const&>())), "");

	Hive v;

	{
		v.assign(SizeType{100}, T{3});
		VERIFY(v.size() == 100u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{300});
	}
	{
		v.assign(SizeType{200}, T{4});
		VERIFY(v.size() == 200u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{800});
	}
	{
		v.assign(SizeType{0}, T{5});
		VERIFY(v.size() == 0u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{0});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, AssignNValueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace assign_n_value_test

}	// namespace hamon_hive_test
