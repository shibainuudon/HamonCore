/**
 *	@file	unit_test_hive_op_assign_move.cpp
 *
 *	@brief	operator= のテスト
 *
 *	hive& operator=(hive&& x) noexcept(see below);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hive_test_helper.hpp"

namespace hamon_hive_test
{

namespace op_assign_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Hive = hamon::hive<T>;

	static_assert( hamon::is_move_assignable<Hive>::value, "");
	static_assert( hamon::is_nothrow_move_assignable<Hive>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Hive>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>() = hamon::declval<Hive&&>()), Hive&>::value, "");

	Hive v1;
	VERIFY(v1.empty());

	{
		Hive v2{1,2,3};
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	{
		auto& r = (v1 = hamon::move(v1));
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	{
		Hive v2{5,4,3,2};
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 4u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{14});
	}
	{
		Hive v2{};
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 0u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{0});
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

	static_assert( hamon::is_move_assignable<Hive>::value, "");
	static_assert( hamon::is_nothrow_move_assignable<Hive>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Hive>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>() = hamon::declval<Hive&&>()), Hive&>::value, "");

	Allocator a1{10};
	Hive v1{a1};
	VERIFY(v1.empty());

	// Allocator::is_always_equal == true_type なときは、コピーもムーブもできなくてもムーブ代入可能
	{
		Allocator a2{20};
		Hive v2{a2};
		v2.emplace(1);
		v2.emplace(2);
		v2.emplace(3);
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), 0,
			[](int lhs, T const& rhs) { return lhs + rhs.value; }) == 6);
		VERIFY(v1.get_allocator() == a1);
		VERIFY(v1.get_allocator() == a2);
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	using T = NonMovable;
	using Allocator = TestAllocator5<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_move_assignable<Hive>::value, "");
	static_assert( hamon::is_nothrow_move_assignable<Hive>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Hive>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>() = hamon::declval<Hive&&>()), Hive&>::value, "");

	Allocator a1{10};
	Hive v1{a1};
	VERIFY(v1.empty());

	// Allocator::propagate_on_container_move_assignment == true_type なときは、コピーもムーブもできなくてもムーブ代入可能
	{
		Allocator a2{20};
		Hive v2{a2};
		v2.emplace(1);
		v2.emplace(2);
		v2.emplace(3);
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), 0,
			[](int lhs, T const& rhs) { return lhs + rhs.value; }) == 6);
		VERIFY(v1.get_allocator() != a1);
		VERIFY(v1.get_allocator() == a2);
	}

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

HAMON_CXX20_CONSTEXPR bool test4()
{
	using T = MoveOnly;
	using Allocator = TestAllocator4<T>;
	using Hive = hamon::hive<T, Allocator>;

	static_assert( hamon::is_move_assignable<Hive>::value, "");
	static_assert(!hamon::is_nothrow_move_assignable<Hive>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Hive>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>() = hamon::declval<Hive&&>()), Hive&>::value, "");

	Allocator a1{10};
	Hive v1{a1};
	VERIFY(v1.empty());

	// Allocator::is_always_equal == false_type かつ、
	// Allocator::propagate_on_container_move_assignment == false_type なときは、ムーブ可能であればムーブ代入可能
	{
		Allocator a2{20};
		Hive v2{a2};
		v2.emplace(1);
		v2.emplace(2);
		v2.emplace(3);
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), 0,
			[](int lhs, T const& rhs) { return lhs + rhs.value; }) == 6);
		VERIFY(v1.get_allocator() == a1);
		VERIFY(v1.get_allocator() != a2);
	}
	{
		Allocator a2{10};
		Hive v2{a2};
		v2.emplace(4);
		v2.emplace(5);
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 2u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), 0,
			[](int lhs, T const& rhs) { return lhs + rhs.value; }) == 9);
		VERIFY(v1.get_allocator() == a1);
		VERIFY(v1.get_allocator() == a2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, OpAssignMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3());

#if (defined(HAMON_MSVC) && (HAMON_MSVC < 1930))
	// Visual Studio 2019 のとき、constexprとして評価しようとするとコンパイルエラーになる
	// (呼び出されないはずのコピーコンストラクタを呼び出そうとしてエラーになる)
	// Visual Studio 2019 のバグかと思われる
	EXPECT_TRUE(test4());
#else
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4());
#endif
}

}	// namespace op_assign_move_test

}	// namespace hamon_hive_test
