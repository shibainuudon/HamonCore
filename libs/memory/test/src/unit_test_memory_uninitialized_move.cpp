/**
 *	@file	unit_test_memory_uninitialized_move.cpp
 *
 *	@brief	uninitialized_move のテスト
 */

#include <hamon/memory/uninitialized_move.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include <list>

namespace hamon_memory_test
{

namespace uninitialized_move_test
{

static int copy_constructed = 0;
static int move_constructed = 0;
static int copy_assigned = 0;
static int move_assigned = 0;

struct Y
{
	Y() = default;
	Y(Y const&) { ++copy_constructed; }
	Y(Y &&) noexcept { ++move_constructed; }
	Y& operator=(Y const&) { ++copy_assigned; return *this; }
	Y& operator=(Y &&) { ++move_assigned; return *this; }
};

struct Z
{
	int value;
	Z() : value(0){}
	Z(int v) : value(v){}
	Z(Z&& z) : value(z.value) { z.value = -1; }
};

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnMove
{
	int value;

	static int count;
	static int move_count;

	ThrowOnMove() = delete;

	ThrowOnMove(int v)
		: value(v)
	{
		count++;
	}

	ThrowOnMove(ThrowOnMove&& x)
		: value(x.value)
	{
		if (move_count >= 5)
		{
			throw 0;
		}
		count++;
		move_count++;
	}

	~ThrowOnMove()
	{
		count--;
		move_count--;
	}
};

int ThrowOnMove::count = 0;
int ThrowOnMove::move_count = 0;
#endif

GTEST_TEST(MemoryTest, UninitializedMoveTest)
{
	{
		Y a[100];
		Y b[100];

		auto ret = hamon::uninitialized_move(a, a + 10, b);

		EXPECT_EQ( 0, copy_constructed);
		EXPECT_EQ(10, move_constructed);
		EXPECT_EQ( 0, copy_assigned);
		EXPECT_EQ( 0, move_assigned);

		EXPECT_TRUE(ret == b + 10);
	}
	{
		std::list<int> a = {10, 11, 12, 13};
		int b[10];

		auto ret = hamon::uninitialized_move(a.begin(), a.end(), b);

		EXPECT_EQ(10, b[0]);
		EXPECT_EQ(11, b[1]);
		EXPECT_EQ(12, b[2]);
		EXPECT_EQ(13, b[3]);

		EXPECT_TRUE(ret == b + 4);
	}
	{
		Z v[] = { 1, 2, 3 };

		hamon::allocator<Z> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const hamon::size_t size = 3;
		Z* p = alloc.allocate(size);

		// 未初期化領域pを初期化しつつ範囲vから要素をムーブ
		auto ret = hamon::uninitialized_move(v, v + size, p);
		EXPECT_TRUE(ret == p + size);

		// pの領域が初期化され、かつvからpに要素がムーブされているか確認
		EXPECT_EQ( 1, p[0].value);
		EXPECT_EQ( 2, p[1].value);
		EXPECT_EQ( 3, p[2].value);
		EXPECT_EQ(-1, v[0].value);
		EXPECT_EQ(-1, v[1].value);
		EXPECT_EQ(-1, v[2].value);

		// 要素を破棄
		hamon::destroy(p, p+size);

		// メモリ解放
		alloc.deallocate(p, size);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::allocator<ThrowOnMove> alloc;

		const hamon::size_t size = 3;
		auto* p = alloc.allocate(size);

		std::list<ThrowOnMove> v;
		v.emplace_back(10);
		v.emplace_back(11);
		v.emplace_back(12);

		EXPECT_EQ(3, ThrowOnMove::count);
		EXPECT_EQ(0, ThrowOnMove::move_count);

		hamon::uninitialized_move(v.begin(), v.end(), p);

		EXPECT_EQ(6, ThrowOnMove::count);
		EXPECT_EQ(3, ThrowOnMove::move_count);

		EXPECT_ANY_THROW(hamon::uninitialized_move(v.begin(), v.end(), p));

		EXPECT_EQ(6, ThrowOnMove::count);
		EXPECT_EQ(3, ThrowOnMove::move_count);

		hamon::destroy(p, p+size);
		alloc.deallocate(p, size);

		EXPECT_EQ(3, ThrowOnMove::count);
		EXPECT_EQ(0, ThrowOnMove::move_count);
	}
	EXPECT_EQ(0, ThrowOnMove::count);
#endif
}

}	// namespace uninitialized_move_test

}	// namespace hamon_memory_test
