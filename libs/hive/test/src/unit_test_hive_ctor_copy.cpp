/**
 *	@file	unit_test_hive_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	hive(const hive& x);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hive_test_helper.hpp"

namespace hamon_hive_test
{

namespace ctor_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Allocator = TestAllocator2<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_copy_constructible<Hive>::value, "");
	static_assert(!hamon::is_nothrow_copy_constructible<Hive>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<Hive>::value, "");
	static_assert(!hamon::is_trivially_copy_constructible<Hive>::value, "");

	{
		Allocator alloc1{10};
		Allocator alloc2{20};
		Hive v1 = {{T{1}, T{2}, T{3}}, alloc2};
		Hive v2 = {v1};
		VERIFY(v2.size() == 3u);
		VERIFY(hamon::accumulate(v2.begin(),  v2.end(),  T{}, hamon::plus<T>{}) == T{6});
		VERIFY(hamon::accumulate(v2.rbegin(), v2.rend(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(v2.get_allocator() != alloc1);
		VERIFY(v2.get_allocator() == alloc2);
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Allocator = TestAllocator3<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_copy_constructible<Hive>::value, "");
	static_assert(!hamon::is_nothrow_copy_constructible<Hive>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<Hive>::value, "");
	static_assert(!hamon::is_trivially_copy_constructible<Hive>::value, "");

	{
		Allocator alloc1{10};
		Allocator alloc2{20};
		Hive v1 = {{T{1}, T{2}, T{3}}, alloc2};
		Hive v2 = {v1};
		VERIFY(v2.size() == 3u);
		VERIFY(hamon::accumulate(v2.begin(),  v2.end(),  T{}, hamon::plus<T>{}) == T{6});
		VERIFY(hamon::accumulate(v2.rbegin(), v2.rend(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(v2.get_allocator() != alloc1);
		VERIFY(v2.get_allocator() != alloc2);
		VERIFY(v2.get_allocator() == Allocator{});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<float>());
}

}	// namespace ctor_copy_test

}	// namespace hamon_hive_test
