﻿/**
 *	@file	unit_test_memory_ranges_uninitialized_move.cpp
 *
 *	@brief	ranges::uninitialized_move のテスト
 */

#include <hamon/memory/ranges/uninitialized_move.hpp>
#include <hamon/memory/ranges/destroy.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/list.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace ranges_uninitialized_move_test
{

struct A
{
	A(A const&){}
	A(A &&){}
};

struct B
{
	B(B const&){}
	B(B &&) = delete;
};

template <typename Void, typename... Args>
struct invocable_uninitialized_move_impl
	: public hamon::false_type {};

template <typename... Args>
struct invocable_uninitialized_move_impl<
	hamon::void_t<decltype(hamon::ranges::uninitialized_move(hamon::declval<Args>()...))>, Args...>
	: public hamon::true_type {};

template <typename... Args>
using invocable_uninitialized_move = invocable_uninitialized_move_impl<void, Args...>;

static_assert(invocable_uninitialized_move<
	input_iterator_wrapper<int>,   test_sentinel<input_iterator_wrapper<int>>,
	forward_iterator_wrapper<int>, test_sentinel<forward_iterator_wrapper<int>>>::value, "");
static_assert(!invocable_uninitialized_move<
	input_iterator_wrapper<int>,   test_sentinel<input_iterator_wrapper<int>>,
	input_iterator_wrapper<int>,   test_sentinel<input_iterator_wrapper<int>>>::value, "");
static_assert( invocable_uninitialized_move<A*, A*, A*, A*>::value, "");
static_assert(!invocable_uninitialized_move<B*, B*, B*, B*>::value, "");

static_assert(!invocable_uninitialized_move<test_input_range<int>, test_input_range<int>>::value, "");
static_assert( invocable_uninitialized_move<test_input_range<int>, test_forward_range<int>>::value, "");
static_assert(!invocable_uninitialized_move<test_forward_range<int>, test_input_range<int>>::value, "");
static_assert( invocable_uninitialized_move<test_forward_range<int>, test_forward_range<int>>::value, "");
static_assert( invocable_uninitialized_move<test_input_range<A>, test_forward_range<A>>::value, "");
static_assert(!invocable_uninitialized_move<test_input_range<B>, test_forward_range<B>>::value, "");

struct MoveOnly
{
	int value;
	MoveOnly(int v) : value(v) {}
	MoveOnly(MoveOnly const&) = delete;
	MoveOnly(MoveOnly&& t) : value(t.value) { t.value = -1; }
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class IRangeWrapper, template <typename> class ORangeWrapper>
bool test()
{
	using T = MoveOnly;
	using IRange = IRangeWrapper<T>;
	using ORange = ORangeWrapper<T>;
	using I = typename IRange::iterator;
	using O = typename ORange::iterator;

	{
		T a[] = {1,2,3};
		IRange r1(a);

		hamon::allocator<T> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 3;
		auto p = alloc.allocate(size);
		ORange r2(p, p + size);

		// 未初期化領域pを初期化しつつ範囲vから要素をムーブ
		auto ret = hamon::ranges::uninitialized_move(r1.begin(), r1.end(), r2.begin(), r2.end());
		static_assert(hamon::is_same<decltype(ret), hamon::ranges::uninitialized_move_result<I, O>>::value, "");
		VERIFY(ret.in  == r1.end());
		VERIFY(ret.out == r2.end());

		// pの領域が初期化され、かつvからpに要素がムーブされているか確認
		VERIFY(p[0].value == 1);
		VERIFY(p[1].value == 2);
		VERIFY(p[2].value == 3);
		VERIFY(a[0].value == -1);
		VERIFY(a[1].value == -1);
		VERIFY(a[2].value == -1);

		// 要素を破棄
		hamon::ranges::destroy(r2.begin(), r2.end());

		// メモリ解放
		alloc.deallocate(p, size);
	}
	{
		T a[] = {1,2,3};
		IRange r1(a);

		hamon::allocator<T> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 3;
		auto p = alloc.allocate(size);
		ORange r2(p, p + size);

		// 未初期化領域pを初期化しつつ範囲vから要素をムーブ
		auto ret = hamon::ranges::uninitialized_move(r1, r2);
		static_assert(hamon::is_same<decltype(ret), hamon::ranges::uninitialized_move_result<I, O>>::value, "");
		VERIFY(ret.in  == r1.end());
		VERIFY(ret.out == r2.end());

		// pの領域が初期化され、かつvからpに要素がムーブされているか確認
		VERIFY(p[0].value == 1);
		VERIFY(p[1].value == 2);
		VERIFY(p[2].value == 3);
		VERIFY(a[0].value == -1);
		VERIFY(a[1].value == -1);
		VERIFY(a[2].value == -1);

		// 要素を破棄
		hamon::ranges::destroy(r2);

		// メモリ解放
		alloc.deallocate(p, size);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesUninitializedMoveTest)
{
	EXPECT_TRUE((test<test_input_range,   test_forward_range>()));
	EXPECT_TRUE((test<test_forward_range, test_forward_range>()));

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::allocator<ThrowOnMove> alloc;

		const std::size_t size = 3;
		auto* p = alloc.allocate(size);

		hamon::list<ThrowOnMove> v;
		v.emplace_back(10);
		v.emplace_back(11);
		v.emplace_back(12);

		EXPECT_EQ(3, ThrowOnMove::count);
		EXPECT_EQ(0, ThrowOnMove::move_count);

		hamon::ranges::uninitialized_move(v.begin(), v.end(), p, p + size);

		EXPECT_EQ(6, ThrowOnMove::count);
		EXPECT_EQ(3, ThrowOnMove::move_count);

		EXPECT_ANY_THROW(hamon::ranges::uninitialized_move(v.begin(), v.end(), p, p + size));

		EXPECT_EQ(6, ThrowOnMove::count);
		EXPECT_EQ(3, ThrowOnMove::move_count);

		hamon::ranges::destroy(p, p + size);
		alloc.deallocate(p, size);

		EXPECT_EQ(3, ThrowOnMove::count);
		EXPECT_EQ(0, ThrowOnMove::move_count);
	}
	EXPECT_EQ(0, ThrowOnMove::count);
#endif
}

}	// namespace ranges_uninitialized_move_test

}	// namespace hamon_memory_test
