/**
 *	@file	unit_test_hive_ctor_limits_alloc.cpp
 *
 *	@brief	block_limits, Allocator を引数に取るコンストラクタのテスト
 *
 *	constexpr hive(hive_limits block_limits, const Allocator&);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace ctor_limits_alloc_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using Allocator = typename Hive::allocator_type;

	static_assert( hamon::is_constructible           <Hive, hamon::hive_limits, const Allocator&>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, hamon::hive_limits, const Allocator&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, hamon::hive_limits, const Allocator&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, hamon::hive_limits, const Allocator&>::value, "");

	Allocator alloc;

	{
		Hive v{hamon::hive_limits{1, 100}, alloc};
		VERIFY(v.empty());
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{0});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorLimitsAllocTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<double>());
}

}	// namespace ctor_limits_alloc_test

}	// namespace hamon_hive_test
