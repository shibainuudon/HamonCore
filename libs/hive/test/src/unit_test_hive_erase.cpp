/**
 *	@file	unit_test_hive_erase.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class T, class Allocator, class U = T>
 *	typename hive<T, Allocator>::size_type
 *	erase(hive<T, Allocator>& c, const U& value);
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

namespace erase_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(erase(hamon::declval<Hive&>(), hamon::declval<T>())), SizeType>::value, "");
	static_assert(!noexcept(erase(hamon::declval<Hive&>(), hamon::declval<T>())), "");

	{
		Hive v = {3,1,4,1,5,2};
		auto r = hamon::erase(v, T{1});
		VERIFY(r == 2u);
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{14});
	}
	{
		Hive v = {1,2,3,4,5,6,7,8,9,10};
		auto r = hamon::erase(v, T{5});
		VERIFY(r == 1u);
		VERIFY(v.size() == 9u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{50});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, EraseTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace erase_test

}	// namespace hamon_hive_test
