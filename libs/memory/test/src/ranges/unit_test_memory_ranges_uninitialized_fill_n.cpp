﻿/**
 *	@file	unit_test_memory_ranges_uninitialized_fill_n.cpp
 *
 *	@brief	ranges::uninitialized_fill_n のテスト
 */

#include <hamon/memory/ranges/uninitialized_fill_n.hpp>
#include <hamon/memory/ranges/destroy.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace ranges_uninitialized_fill_n_test
{

struct A
{
	A(A const&){}
};

struct B
{
	B(B const&) = delete;
};

template <typename Void, typename... Args>
struct invocable_uninitialized_fill_n_impl
	: public hamon::false_type {};

template <typename... Args>
struct invocable_uninitialized_fill_n_impl<
	hamon::void_t<decltype(hamon::ranges::uninitialized_fill_n(hamon::declval<Args>()...))>, Args...>
	: public hamon::true_type {};

template <typename... Args>
using invocable_uninitialized_fill_n = invocable_uninitialized_fill_n_impl<void, Args...>;

static_assert(!invocable_uninitialized_fill_n<input_iterator_wrapper<int>, int, int>::value, "");
static_assert( invocable_uninitialized_fill_n<forward_iterator_wrapper<int>, int, int>::value, "");
static_assert( invocable_uninitialized_fill_n<A*, int, A const&>::value, "");
static_assert(!invocable_uninitialized_fill_n<B*, int, B const&>::value, "");

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
bool test()
{
	using T = int;
	using Range = RangeWrapper<T>;
	using I = typename Range::iterator;

	{
		std::allocator<T> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 3;
		auto p = alloc.allocate(size);
		Range r(p, p + size);

		// 未初期化領域pを初期化しつつ、値42で埋める
		auto ret = hamon::ranges::uninitialized_fill_n(r.begin(), size, 42);
		static_assert(hamon::is_same<decltype(ret), I>::value, "");
		VERIFY(ret == r.end());

		// pの領域が初期化され、かつvからpに要素がコピーされているか確認
		VERIFY(p[0] == 42);
		VERIFY(p[1] == 42);
		VERIFY(p[2] == 42);

		// 要素を破棄
		hamon::ranges::destroy(r.begin(), r.end());

		// メモリ解放
		alloc.deallocate(p, size);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesUninitializedFillNTest)
{
//	EXPECT_TRUE((test<test_input_range>()));
	EXPECT_TRUE((test<test_forward_range>()));
	EXPECT_TRUE((test<test_bidirectional_range>()));

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<ThrowOnCopy> alloc;

		const std::size_t size = 3;
		auto* p = alloc.allocate(size);

		const ThrowOnCopy x{42};

		EXPECT_EQ(1, ThrowOnCopy::count);
		EXPECT_EQ(0, ThrowOnCopy::copy_count);

		hamon::ranges::uninitialized_fill_n(p, size, x);

		EXPECT_EQ(4, ThrowOnCopy::count);
		EXPECT_EQ(3, ThrowOnCopy::copy_count);

		EXPECT_ANY_THROW(hamon::ranges::uninitialized_fill_n(p, size, x));

		EXPECT_EQ(4, ThrowOnCopy::count);
		EXPECT_EQ(3, ThrowOnCopy::copy_count);

		hamon::ranges::destroy(p, p + size);
		alloc.deallocate(p, size);

		EXPECT_EQ(1, ThrowOnCopy::count);
		EXPECT_EQ(0, ThrowOnCopy::copy_count);
	}
	EXPECT_EQ(0, ThrowOnCopy::count);
#endif
}

}	// namespace ranges_uninitialized_fill_n_test

}	// namespace hamon_memory_test
