/**
 *	@file	unit_test_memory_ranges_uninitialized_value_construct.cpp
 *
 *	@brief	ranges::uninitialized_value_construct のテスト
 */

#include <hamon/memory/ranges/uninitialized_value_construct.hpp>
#include <hamon/memory/ranges/destroy.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace ranges_uninitialized_value_construct_test
{

struct A
{
	A(){}
};

struct B
{
	B() = delete;
};

template <typename Void, typename... Args>
struct invocable_uninitialized_value_construct_impl
	: public hamon::false_type {};

template <typename... Args>
struct invocable_uninitialized_value_construct_impl<
	hamon::void_t<decltype(hamon::ranges::uninitialized_value_construct(hamon::declval<Args>()...))>, Args...>
	: public hamon::true_type {};

template <typename... Args>
using invocable_uninitialized_value_construct = invocable_uninitialized_value_construct_impl<void, Args...>;

static_assert(!invocable_uninitialized_value_construct<A>::value, "");
static_assert(!invocable_uninitialized_value_construct<A*>::value, "");
static_assert( invocable_uninitialized_value_construct<A*, A*>::value, "");
static_assert( invocable_uninitialized_value_construct<A[2]>::value, "");
static_assert(!invocable_uninitialized_value_construct<test_input_range<A>>::value, "");
static_assert( invocable_uninitialized_value_construct<test_forward_range<A>>::value, "");
static_assert(!invocable_uninitialized_value_construct<test_forward_range<B>>::value, "");
static_assert(!invocable_uninitialized_value_construct<test_input_range<A>::iterator, test_input_range<A>::sentinel>::value, "");
static_assert( invocable_uninitialized_value_construct<test_forward_range<A>::iterator, test_forward_range<A>::sentinel>::value, "");
static_assert(!invocable_uninitialized_value_construct<test_forward_range<B>::iterator, test_forward_range<B>::sentinel>::value, "");
static_assert(!invocable_uninitialized_value_construct<test_forward_range<A>::iterator, test_forward_range<B>::sentinel>::value, "");

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
bool test()
{
	{
		std::allocator<int> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 3;
		auto* p = alloc.allocate(size);

		using Range = RangeWrapper<int>;
		Range r(p, p + size);

		// 未初期化領域[p, p + size)を値構築
		auto ret = hamon::ranges::uninitialized_value_construct(r.begin(), r.end());
		static_assert(hamon::is_same<decltype(ret), typename Range::iterator>::value, "");
		VERIFY(ret == r.end());

		// pの領域が値構築されているか確認
		VERIFY(p[0] == 0);
		VERIFY(p[1] == 0);
		VERIFY(p[2] == 0);

		// オブジェクトを破棄
		hamon::ranges::destroy(r.begin(), r.end());

		// メモリ解放
		alloc.deallocate(p, size);
	}
	{
		std::allocator<int> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 4;
		auto* p = alloc.allocate(size);

		using Range = RangeWrapper<int>;
		Range r(p, p + size);

		// 未初期化領域[p, p + size)を値構築
		auto ret = hamon::ranges::uninitialized_value_construct(r);
		static_assert(hamon::is_same<decltype(ret), typename Range::iterator>::value, "");
		VERIFY(ret == r.end());

		// pの領域が値構築されているか確認
		VERIFY(p[0] == 0);
		VERIFY(p[1] == 0);
		VERIFY(p[2] == 0);
		VERIFY(p[3] == 0);

		// オブジェクトを破棄
		hamon::ranges::destroy(r);

		// メモリ解放
		alloc.deallocate(p, size);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesUninitializedValueConstructTest)
{
	//EXPECT_TRUE(test<test_input_range>());
	EXPECT_TRUE(test<test_forward_range>());
	EXPECT_TRUE(test<test_bidirectional_range>());
	EXPECT_TRUE(test<test_random_access_range>());
	EXPECT_TRUE(test<test_contiguous_range>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<ThrowOnCtor> alloc;
		auto* p = alloc.allocate(10);
		hamon::ranges::uninitialized_value_construct(p, p + 4);
		EXPECT_EQ(4, ThrowOnCtor::count);
		EXPECT_EQ(42, p[0].value);
		EXPECT_EQ(42, p[1].value);
		EXPECT_EQ(42, p[2].value);
		EXPECT_EQ(42, p[3].value);

		EXPECT_ANY_THROW(hamon::ranges::uninitialized_value_construct(p + 4, p + 6));
		EXPECT_EQ(4, ThrowOnCtor::count);

		hamon::ranges::destroy(p, p + 4);
		alloc.deallocate(p, 10);
		EXPECT_EQ(0, ThrowOnCtor::count);
	}
#endif
}

}	// namespace ranges_uninitialized_value_construct_test

}	// namespace hamon_memory_test
