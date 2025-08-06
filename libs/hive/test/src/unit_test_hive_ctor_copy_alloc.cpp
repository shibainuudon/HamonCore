/**
 *	@file	unit_test_hive_ctor_copy_alloc.cpp
 *
 *	@brief	コピーとAllocatorを引数に取るコンストラクタのテスト
 *
 *	hive(const hive& x, const type_identity_t<Allocator>& alloc);
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
#include "hive_test_helper.hpp"

namespace hamon_hive_test
{

namespace ctor_copy_alloc_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = TestAllocator2<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_constructible           <Hive, Hive const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, Hive const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, Hive const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, Hive const&, Allocator const&>::value, "");

	{
		Allocator alloc{10};
		Hive v1({T{1}, T{2}, T{3}}, alloc);
		Hive v2{v1, alloc};
		VERIFY(v2.size() == 3u);
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(v1.get_allocator() == v2.get_allocator());
		VERIFY(hamon::accumulate(v2.begin(),  v2.end(),  T{}, hamon::plus<T>{}) == T{6});
		VERIFY(hamon::accumulate(v2.rbegin(), v2.rend(), T{}, hamon::plus<T>{}) == T{6});
	}
	{
		Allocator alloc1{10};
		Allocator alloc2{20};
		Hive v1({T{1}, T{2}, T{3}, T{4}}, alloc1);
		Hive v2{v1, alloc2};
		VERIFY(v2.size() == 4u);
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(hamon::accumulate(v2.begin(),  v2.end(),  T{}, hamon::plus<T>{}) == T{10});
		VERIFY(hamon::accumulate(v2.rbegin(), v2.rend(), T{}, hamon::plus<T>{}) == T{10});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorCopyAllocTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace ctor_copy_alloc_test

}	// namespace hamon_hive_test
