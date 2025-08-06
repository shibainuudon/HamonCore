/**
 *	@file	unit_test_hive_ctor_move_alloc.cpp
 *
 *	@brief	ムーブとAllocatorを引数に取るコンストラクタのテスト
 *
 *	hive(hive&&, const type_identity_t<Allocator>& alloc);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hive_test_helper.hpp"

namespace hamon_hive_test
{

namespace ctor_move_alloc_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Allocator = TestAllocator2<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_constructible           <Hive, Hive&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_HIVE)
	static_assert(!hamon::is_nothrow_constructible   <Hive, Hive&&, Allocator const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Hive, Hive&&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, Hive&&, Allocator const&>::value, "");

	{
		Allocator alloc{10};
		Hive v1({T{1}, T{2}, T{3}}, alloc);
		Hive v2{hamon::move(v1), alloc};
		VERIFY(v2.size() == 3u);
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	{
		Allocator alloc1{10};
		Allocator alloc2{20};
		Hive v1({T{1}, T{2}, T{3}, T{4}}, alloc1);
		Hive v2{hamon::move(v1), alloc2};
		VERIFY(v2.size() == 4u);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{10});
	}

	return true;
}

// コピーもムーブもできない型
struct NonMovable
{
	int value;

	HAMON_CXX14_CONSTEXPR NonMovable(int v) : value(v) {}

	NonMovable(NonMovable const&)            = delete;
	NonMovable(NonMovable &&)                = delete;
	NonMovable& operator=(NonMovable const&) = delete;
	NonMovable& operator=(NonMovable &&)     = delete;
};

HAMON_CXX20_CONSTEXPR bool test2()
{
	using T = NonMovable;
	using Allocator = TestAllocator1<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_constructible           <Hive, Hive&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_HIVE)
	static_assert( hamon::is_nothrow_constructible   <Hive, Hive&&, Allocator const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Hive, Hive&&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, Hive&&, Allocator const&>::value, "");

	Allocator alloc1{10};
	Allocator alloc2{20};
	Hive v1(alloc1);
	v1.emplace(1);
	v1.emplace(2);
	v1.emplace(3);
	v1.emplace(4);

	// Allocator::is_always_equal == true_type なときは、コピーもムーブもできなくてもコンストラクト可能
	Hive v2(hamon::move(v1), alloc2);
	VERIFY(v2.size() == 4u);
	VERIFY(hamon::accumulate(v2.begin(), v2.end(), 0,
		[](int lhs, T const& rhs) { return lhs + rhs.value; }) == 10);
	VERIFY(v2.get_allocator() == alloc1);
	VERIFY(v2.get_allocator() == alloc2);

	return true;
}

struct MoveOnly
{
	int value;

	HAMON_CXX14_CONSTEXPR MoveOnly(int v) : value(v) {}

	MoveOnly(MoveOnly const&) = delete;
	MoveOnly& operator=(MoveOnly const&) = delete;

	HAMON_CXX14_CONSTEXPR MoveOnly(MoveOnly&& x) HAMON_NOEXCEPT : value(x.value) {}
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly&& x) HAMON_NOEXCEPT { value = x.value; return *this; }
};

HAMON_CXX20_CONSTEXPR bool test3()
{
	using T = MoveOnly;
	using Allocator = TestAllocator2<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_constructible           <Hive, Hive&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_HIVE)
	static_assert(!hamon::is_nothrow_constructible   <Hive, Hive&&, Allocator const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Hive, Hive&&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, Hive&&, Allocator const&>::value, "");

	Allocator alloc1{10};
	Allocator alloc2{20};
	Hive v1(alloc1);
	v1.emplace(1);
	v1.emplace(2);
	v1.emplace(3);
	v1.emplace(4);

	// Allocator::is_always_equal == false_type なときは、ムーブ可能であればコンストラクト可能
	Hive v2(hamon::move(v1), alloc2);
	VERIFY(v2.size() == 4u);
	VERIFY(hamon::accumulate(v2.begin(), v2.end(), 0,
		[](int lhs, T const& rhs) { return lhs + rhs.value; }) == 10);
	VERIFY(v2.get_allocator() != alloc1);
	VERIFY(v2.get_allocator() == alloc2);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorMoveAllocTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

#if (defined(HAMON_MSVC) && (HAMON_MSVC < 1930))
	// Visual Studio 2019 のとき、constexprとして評価しようとするとコンパイルエラーになる
	// (呼び出されないはずのコピーコンストラクタを呼び出そうとしてエラーになる)
	// Visual Studio 2019 のバグかと思われる
	EXPECT_TRUE(test3());
#else
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3());
#endif
}

}	// namespace ctor_move_alloc_test

}	// namespace hamon_hive_test
