/**
 *	@file	unit_test_hive_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	bool empty() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().empty()), bool>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().empty()), "");

	{
		Hive v;
		VERIFY(v.empty());
		v.emplace(T{1});
		VERIFY(!v.empty());
		v.clear();
		VERIFY(v.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, EmptyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace empty_test

}	// namespace hamon_hive_test
