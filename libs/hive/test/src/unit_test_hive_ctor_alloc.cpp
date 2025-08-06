/**
 *	@file	unit_test_hive_ctor_alloc.cpp
 *
 *	@brief	Allocatorを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit hive(const Allocator&) noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace ctor_alloc_test
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
	using Allocator = typename Hive::allocator_type;

	static_assert( hamon::is_constructible           <Hive, const Allocator&>::value, "");
	static_assert( hamon::is_nothrow_constructible   <Hive, const Allocator&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Hive, const Allocator&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, const Allocator&>::value, "");

	Allocator alloc;

	{
		Hive v(alloc);
		VERIFY(v.empty());
	}
	{
		Hive v{alloc};
		VERIFY(v.empty());
	}
	//{
	//	Hive v = {alloc};
	//	VERIFY(v.empty());
	//}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorAllocTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_alloc_test

}	// namespace hamon_hive_test
