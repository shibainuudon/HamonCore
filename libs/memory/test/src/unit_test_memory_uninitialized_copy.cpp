/**
 *	@file	unit_test_memory_uninitialized_copy.cpp
 *
 *	@brief	uninitialized_copy のテスト
 */

#include <hamon/memory/uninitialized_copy.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/is_trivial.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_copy_test
{

struct X
{
};

static_assert(hamon::is_trivial<X>::value, "X is trivial");

struct Y
{
	Y() = default;
	Y(Y const&) = default;
	Y& operator=(Y const&) = default;

	Y(X const&) { ++constructed; }
	Y& operator=(X const&)& { ++assigned; return *this; }
	Y& operator=(X const&) && = delete;
	Y& operator=(X&&) = delete;

	static int constructed;
	static int assigned;
};

int Y::constructed = 0;
int Y::assigned = 0;

static_assert(hamon::is_trivial<Y>::value, "Y is trivial");

struct Z
{
	int value;
	Z() : value(0){}
	Z(int v) : value(v){}
	Z(Z const& z) : value(z.value) {}
};

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	int value;

	static int count;
	static int copy_count;

	ThrowOnCopy() = delete;

	ThrowOnCopy(int v)
		: value(v)
	{
		count++;
	}

	ThrowOnCopy(ThrowOnCopy const& x)
		: value(x.value)
	{
		if (copy_count >= 5)
		{
			throw 0;
		}
		count++;
		copy_count++;
	}

	~ThrowOnCopy()
	{
		count--;
		copy_count--;
	}
};

int ThrowOnCopy::count = 0;
int ThrowOnCopy::copy_count = 0;
#endif

GTEST_TEST(MemoryTest, UninitializedCopyTest)
{
	{
		int a[] {1,2,3,4,5,6};
		int b[100];
		const std::size_t size = sizeof(a) / sizeof(a[0]);
		auto ret = hamon::uninitialized_copy(a, a + size, b);
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(4, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(6, b[5]);
		EXPECT_TRUE(ret == b + size);
	}
	{
		X a[100];
		Y b[100];

		const std::size_t size = 10;
		auto ret = hamon::uninitialized_copy(a, a + size, b);

		EXPECT_EQ((int)size, Y::constructed);
		EXPECT_EQ(0,         Y::assigned);

		EXPECT_TRUE(ret == b + size);
	}
	{
		const Z v[] = { 1, 2, 3 };

		hamon::allocator<Z> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 3;
		Z* p = alloc.allocate(size);

		// 未初期化領域pを初期化しつつ範囲vから要素をコピー
		auto ret = hamon::uninitialized_copy(v, v + size, p);
		EXPECT_TRUE(ret == p + size);

		// pの領域が初期化され、かつvからpに要素がコピーされているか確認
		EXPECT_EQ(1, p[0].value);
		EXPECT_EQ(2, p[1].value);
		EXPECT_EQ(3, p[2].value);

		// 要素を破棄
		hamon::destroy(p, p+size);

		// メモリ解放
		alloc.deallocate(p, size);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::allocator<ThrowOnCopy> alloc;

		const std::size_t size = 3;
		auto* p = alloc.allocate(size);

		const ThrowOnCopy v[] = {10,11,12,13};

		EXPECT_EQ(4, ThrowOnCopy::count);
		EXPECT_EQ(0, ThrowOnCopy::copy_count);

		hamon::uninitialized_copy(v, v + size, p);

		EXPECT_EQ(7, ThrowOnCopy::count);
		EXPECT_EQ(3, ThrowOnCopy::copy_count);

		EXPECT_ANY_THROW(hamon::uninitialized_copy(v, v + size, p));

		EXPECT_EQ(7, ThrowOnCopy::count);
		EXPECT_EQ(3, ThrowOnCopy::copy_count);

		hamon::destroy(p, p+size);
		alloc.deallocate(p, size);

		EXPECT_EQ(4, ThrowOnCopy::count);
		EXPECT_EQ(0, ThrowOnCopy::copy_count);
	}
	EXPECT_EQ(0, ThrowOnCopy::count);
#endif
}

}	// namespace uninitialized_copy_test

}	// namespace hamon_memory_test
