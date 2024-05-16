/**
 *	@file	unit_test_memory_uninitialized_fill_n.cpp
 *
 *	@brief	uninitialized_fill_n のテスト
 */

#include <hamon/memory/uninitialized_fill_n.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/type_traits/is_trivial.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace uninitialized_fill_n_test
{

struct X
{
};

static_assert(hamon::is_trivial<X>::value, "X is trivial");

static int constructed = 0;
static int assigned = 0;

struct Y
{
	Y() = default;
	Y(Y const&) = default;
	Y& operator=(Y const&) = default;

	Y(X const&) { ++constructed; }
	Y& operator=(X const&)& { ++assigned; return *this; }
	Y& operator=(X const&) && = delete;
	Y& operator=(X&&) = delete;
};

static_assert(hamon::is_trivial<Y>::value, "Y is trivial");

struct Z
{
	int value;
	Z() = delete;
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

GTEST_TEST(MemoryTest, UninitializedFillNTest)
{
	{
		int a[32];
		hamon::uninitialized_fill_n(a, 4, 42);
		EXPECT_EQ(42, a[0]);
		EXPECT_EQ(42, a[1]);
		EXPECT_EQ(42, a[2]);
		EXPECT_EQ(42, a[3]);
	}
	{
		Y b[100];

		hamon::uninitialized_fill_n(b, 10, X{});

		EXPECT_EQ(10, constructed);
		EXPECT_EQ( 0, assigned);
	}
	{
		std::allocator<Z> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 3;
		Z* p = alloc.allocate(size);

		// 未初期化領域pを初期化しつつ、値42で埋める
		hamon::uninitialized_fill_n(p, size, 42);

		// pの領域が初期化され、かつvからpに要素がコピーされているか確認
		EXPECT_EQ(42, p[0].value);
		EXPECT_EQ(42, p[1].value);
		EXPECT_EQ(42, p[2].value);

		// 要素を破棄
		hamon::destroy(p, p+size);

		// メモリ解放
		alloc.deallocate(p, size);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<ThrowOnCopy> alloc;

		const std::size_t size = 3;
		auto* p = alloc.allocate(size);

		const ThrowOnCopy x{42};

		EXPECT_EQ(1, ThrowOnCopy::count);
		EXPECT_EQ(0, ThrowOnCopy::copy_count);

		hamon::uninitialized_fill_n(p, size, x);

		EXPECT_EQ(4, ThrowOnCopy::count);
		EXPECT_EQ(3, ThrowOnCopy::copy_count);

		EXPECT_ANY_THROW(hamon::uninitialized_fill_n(p, size, x));

		EXPECT_EQ(4, ThrowOnCopy::count);
		EXPECT_EQ(3, ThrowOnCopy::copy_count);

		hamon::destroy(p, p+size);
		alloc.deallocate(p, size);

		EXPECT_EQ(1, ThrowOnCopy::count);
		EXPECT_EQ(0, ThrowOnCopy::copy_count);
	}
	EXPECT_EQ(0, ThrowOnCopy::count);
#endif
}

}	// namespace uninitialized_fill_n_test

}	// namespace hamon_memory_test
