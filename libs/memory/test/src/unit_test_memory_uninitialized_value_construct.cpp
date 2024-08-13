/**
 *	@file	unit_test_memory_uninitialized_value_construct.cpp
 *
 *	@brief	uninitialized_value_construct のテスト
 */

#include <hamon/memory/uninitialized_value_construct.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include <list>

namespace hamon_memory_test
{

namespace uninitialized_value_construct_test
{

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCtor
{
	int value;

	static int count;

	ThrowOnCtor() : value(42)
	{
		if (count >= 5)
		{
			throw 0;
		}
		count++;
	}

	~ThrowOnCtor() { count--; }
};

int ThrowOnCtor::count = 0;
#endif

GTEST_TEST(MemoryTest, UninitializedValueConstructTest)
{
	{
		std::list<int> v;
		hamon::uninitialized_value_construct(v.begin(), v.end());
	}
	{
		hamon::allocator<int> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const hamon::size_t size = 3;
		auto* p = alloc.allocate(size);

		// 未初期化領域[p, p + size)を値構築
		hamon::uninitialized_value_construct(p, p + size);

		// pの領域が値構築されているか確認
		EXPECT_EQ(0, p[0]);
		EXPECT_EQ(0, p[1]);
		EXPECT_EQ(0, p[2]);

		// オブジェクトを破棄
		hamon::destroy(p, p + size);

		// メモリ解放
		alloc.deallocate(p, size);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::allocator<ThrowOnCtor> alloc;
		auto* p = alloc.allocate(10);
		hamon::uninitialized_value_construct(p, p + 4);
		EXPECT_EQ(4, ThrowOnCtor::count);
		EXPECT_EQ(42, p[0].value);
		EXPECT_EQ(42, p[1].value);
		EXPECT_EQ(42, p[2].value);
		EXPECT_EQ(42, p[3].value);

		EXPECT_ANY_THROW(hamon::uninitialized_value_construct(p + 4, p + 6));
		EXPECT_EQ(4, ThrowOnCtor::count);

		hamon::destroy(p, p + 4);
		alloc.deallocate(p, 10);
		EXPECT_EQ(0, ThrowOnCtor::count);
	}
#endif
}

}	// namespace uninitialized_value_construct_test

}	// namespace hamon_memory_test
