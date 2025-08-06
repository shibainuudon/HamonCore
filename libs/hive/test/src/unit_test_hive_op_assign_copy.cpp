/**
 *	@file	unit_test_hive_op_assign_copy.cpp
 *
 *	@brief	operator= のテスト
 *
 *	hive& operator=(const hive& x);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hive_test_helper.hpp"

namespace hamon_hive_test
{

namespace op_assign_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Hive = hamon::hive<T>;

	static_assert( hamon::is_copy_assignable<Hive>::value, "");
	static_assert(!hamon::is_nothrow_copy_assignable<Hive>::value, "");
	static_assert(!hamon::is_trivially_copy_assignable<Hive>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>() = hamon::declval<Hive const&>()), Hive&>::value, "");

	Hive v1;
	VERIFY(v1.empty());

	{
		Hive const v2{1,2,3};
		auto& r = (v1 = v2);
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 3u);
		VERIFY(v2.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{6});
	}
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
	{
		auto& r = (v1 = v1);
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
	}
HAMON_WARNING_POP()
	{
		Hive const v2{5,4,3,2};
		auto& r = (v1 = v2);
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 4u);
		VERIFY(v2.size() == 4u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{14});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{14});
	}
	{
		Hive const v2{};
		auto& r = (v1 = v2);
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 0u);
		VERIFY(v2.size() == 0u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{0});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{0});
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Allocator = TestAllocator4<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_copy_assignable<Hive>::value, "");
	static_assert(!hamon::is_nothrow_copy_assignable<Hive>::value, "");
	static_assert(!hamon::is_trivially_copy_assignable<Hive>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>() = hamon::declval<Hive const&>()), Hive&>::value, "");

	Allocator a1{10};
	Hive v1{a1};
	VERIFY(v1.empty());

	{
		Allocator a2{20};
		Hive const v2{{1,2,3}, a2};
		auto& r = (v1 = v2);
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 3u);
		VERIFY(v2.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(v1.get_allocator() == v2.get_allocator());
		VERIFY(v1.get_allocator() != a1);
		VERIFY(v1.get_allocator() == a2);
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test3()
{
	using Allocator = TestAllocator5<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_copy_assignable<Hive>::value, "");
	static_assert(!hamon::is_nothrow_copy_assignable<Hive>::value, "");
	static_assert(!hamon::is_trivially_copy_assignable<Hive>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>() = hamon::declval<Hive const&>()), Hive&>::value, "");

	Allocator a1{10};
	Hive v1{a1};
	VERIFY(v1.empty());

	{
		Allocator a2{20};
		Hive const v2{{1,2,3}, a2};
		auto& r = (v1 = v2);
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 3u);
		VERIFY(v2.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator() == a1);
		VERIFY(v1.get_allocator() != a2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, OpAssignCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<float>());
}

}	// namespace op_assign_copy_test

}	// namespace hamon_hive_test
