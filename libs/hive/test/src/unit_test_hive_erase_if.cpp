/**
 *	@file	unit_test_hive_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class T, class Allocator, class Predicate>
 *	typename hive<T, Allocator>::size_type
 *	erase_if(hive<T, Allocator>& c, Predicate pred);
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

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct is_zero
{
	template <typename T>
	constexpr bool operator()(T x) const noexcept
	{
		return x == T{0};
	}
};

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(erase_if(hamon::declval<Hive&>(), is_zero{})), SizeType>::value, "");
	static_assert(!noexcept(erase_if(hamon::declval<Hive&>(), is_zero{})), "");

	{
		Hive v = {3,1,4,1,5,2};
		auto r = hamon::erase_if(v, [](T x) { return x % 2 != 0; });
		VERIFY(r == 4u);
		VERIFY(v.size() == 2u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	{
		Hive v = {1,2,3,4,5,6,7,8,9,10};
		auto r = hamon::erase_if(v, [](T x) { return x >= 5; });
		VERIFY(r == 6u);
		VERIFY(v.size() == 4u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, EraseIfTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<short>());
}

}	// namespace erase_if_test

}	// namespace hamon_hive_test
