/**
 *	@file	unit_test_hive_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr hive() noexcept(noexcept(Allocator()));
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace ctor_default_test
{

struct S1
{
	S1() = delete;
};

struct S2
{
	S2() {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert( hamon::is_default_constructible<Hive>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<Hive>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<Hive>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<Hive>::value, "");

	{
		Hive v;
		VERIFY(v.empty());
	}
	{
		Hive v{};
		VERIFY(v.empty());
	}
	{
		Hive v = {};
		VERIFY(v.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_default_test

}	// namespace hamon_hive_test
