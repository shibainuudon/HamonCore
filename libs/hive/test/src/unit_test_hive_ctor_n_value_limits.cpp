/**
 *	@file	unit_test_hive_ctor_n_value_limits.cpp
 *
 *	@brief	n, value, block_limits を引数に取るコンストラクタのテスト
 *
 *	hive(size_type n, const T& value, hive_limits block_limits, const Allocator& = Allocator());
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

namespace ctor_n_value_limits_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test_impl(hamon::hive_limits block_limits)
{
	using Hive = hamon::hive<T>;
	using Allocator = typename Hive::allocator_type;
	using SizeType = typename Hive::size_type;

	static_assert( hamon::is_constructible           <Hive, SizeType, const T&, hamon::hive_limits>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, SizeType, const T&, hamon::hive_limits>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, SizeType, const T&, hamon::hive_limits>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, SizeType, const T&, hamon::hive_limits>::value, "");

	static_assert( hamon::is_constructible           <Hive, SizeType, const T&, hamon::hive_limits, const Allocator&>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, SizeType, const T&, hamon::hive_limits, const Allocator&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, SizeType, const T&, hamon::hive_limits, const Allocator&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, SizeType, const T&, hamon::hive_limits, const Allocator&>::value, "");

	SizeType n{400};
	T value{42};
	Allocator alloc;

	{
		Hive v(n, value, block_limits);
		VERIFY(v.size() == n);
		VERIFY(*v.begin() == value);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == value * static_cast<T>(n));
	}
	{
		Hive v{n, value, block_limits, alloc};
		VERIFY(v.size() == n);
		VERIFY(*v.begin() == value);
		VERIFY(hamon::accumulate(v.rbegin(), v.rend(), T{}, hamon::plus<T>{}) == value * static_cast<T>(n));
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	VERIFY(test_impl<T>({7, 7}));
	VERIFY(test_impl<T>(hamon::hive<T>::block_capacity_hard_limits()));
	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorNValueLimitsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<double>());
}

}	// namespace ctor_n_value_limits_test

}	// namespace hamon_hive_test
