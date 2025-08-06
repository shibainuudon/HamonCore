/**
 *	@file	unit_test_hive_ctor_n_limits.cpp
 *
 *	@brief	n, block_limits を引数に取るコンストラクタのテスト
 *
 *	hive(size_type n, hive_limits block_limits, const Allocator& = Allocator());
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

namespace ctor_n_limits_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using Allocator = typename Hive::allocator_type;
	using SizeType = typename Hive::size_type;

	static_assert( hamon::is_constructible           <Hive, SizeType, hamon::hive_limits>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, SizeType, hamon::hive_limits>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, SizeType, hamon::hive_limits>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, SizeType, hamon::hive_limits>::value, "");

	static_assert( hamon::is_constructible           <Hive, SizeType, hamon::hive_limits, const Allocator&>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, SizeType, hamon::hive_limits, const Allocator&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, SizeType, hamon::hive_limits, const Allocator&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, SizeType, hamon::hive_limits, const Allocator&>::value, "");

	SizeType n{500};
	hamon::hive_limits block_limits{1, 100};
	Allocator alloc;

	{
		Hive v(n, block_limits);
		VERIFY(v.size() == n);
		VERIFY(*v.begin() == T{});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{0});
	}
	{
		Hive v{n, block_limits, alloc};
		VERIFY(v.size() == n);
		VERIFY(*v.begin() == T{});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{0});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorNLimitsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<double>());
}

}	// namespace ctor_n_limits_test

}	// namespace hamon_hive_test
