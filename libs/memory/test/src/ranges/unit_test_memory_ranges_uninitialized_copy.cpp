/**
 *	@file	unit_test_memory_ranges_uninitialized_copy.cpp
 *
 *	@brief	ranges::uninitialized_copy のテスト
 */

#include <hamon/memory/ranges/uninitialized_copy.hpp>
#include <hamon/memory/ranges/destroy.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace ranges_uninitialized_copy_test
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
struct invocable_uninitialized_copy_impl
	: public hamon::false_type {};

template <typename... Args>
struct invocable_uninitialized_copy_impl<
	hamon::void_t<decltype(hamon::ranges::uninitialized_copy(hamon::declval<Args>()...))>, Args...>
	: public hamon::true_type {};

template <typename... Args>
using invocable_uninitialized_copy = invocable_uninitialized_copy_impl<void, Args...>;

static_assert(invocable_uninitialized_copy<
	input_iterator_wrapper<int>,   test_sentinel<input_iterator_wrapper<int>>,
	forward_iterator_wrapper<int>, test_sentinel<forward_iterator_wrapper<int>>>::value, "");
static_assert(!invocable_uninitialized_copy<
	input_iterator_wrapper<int>,   test_sentinel<input_iterator_wrapper<int>>,
	input_iterator_wrapper<int>,   test_sentinel<input_iterator_wrapper<int>>>::value, "");
static_assert( invocable_uninitialized_copy<A*, A*, A*, A*>::value, "");
static_assert(!invocable_uninitialized_copy<B*, B*, B*, B*>::value, "");

static_assert(!invocable_uninitialized_copy<test_input_range<int>, test_input_range<int>>::value, "");
static_assert( invocable_uninitialized_copy<test_input_range<int>, test_forward_range<int>>::value, "");
static_assert(!invocable_uninitialized_copy<test_forward_range<int>, test_input_range<int>>::value, "");
static_assert( invocable_uninitialized_copy<test_forward_range<int>, test_forward_range<int>>::value, "");
static_assert( invocable_uninitialized_copy<test_input_range<A>, test_forward_range<A>>::value, "");
static_assert(!invocable_uninitialized_copy<test_input_range<B>, test_forward_range<B>>::value, "");

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

template <template <typename> class IRangeWrapper, template <typename> class ORangeWrapper>
bool test()
{
	using T = int;
	using IRange = IRangeWrapper<T const>;
	using ORange = ORangeWrapper<T>;
	using I = typename IRange::iterator;
	using O = typename ORange::iterator;

	{
		const T a[] = {1,2,3};
		IRange r1(a);

		std::allocator<T> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 3;
		auto p = alloc.allocate(size);
		ORange r2(p, p + size);

		// 未初期化領域pを初期化しつつ範囲vから要素をコピー
		auto ret = hamon::ranges::uninitialized_copy(r1.begin(), r1.end(), r2.begin(), r2.end());
		static_assert(hamon::is_same<decltype(ret), hamon::ranges::uninitialized_copy_result<I, O>>::value, "");
		VERIFY(ret.in  == r1.end());
		VERIFY(ret.out == r2.end());

		// pの領域が初期化され、かつvからpに要素がコピーされているか確認
		VERIFY(p[0] == 1);
		VERIFY(p[1] == 2);
		VERIFY(p[2] == 3);

		// 要素を破棄
		hamon::ranges::destroy(r2.begin(), r2.end());

		// メモリ解放
		alloc.deallocate(p, size);
	}
	{
		const T a[] = {1,2,3};
		IRange r1(a);

		std::allocator<T> alloc;

		// メモリ確保。
		// この段階では、[p, p + size)の領域は未初期化
		const std::size_t size = 3;
		auto p = alloc.allocate(size);
		ORange r2(p, p + size);

		// 未初期化領域pを初期化しつつ範囲vから要素をコピー
		auto ret = hamon::ranges::uninitialized_copy(r1, r2);
		static_assert(hamon::is_same<decltype(ret), hamon::ranges::uninitialized_copy_result<I, O>>::value, "");
		VERIFY(ret.in  == r1.end());
		VERIFY(ret.out == r2.end());

		// pの領域が初期化され、かつvからpに要素がコピーされているか確認
		VERIFY(p[0] == 1);
		VERIFY(p[1] == 2);
		VERIFY(p[2] == 3);

		// 要素を破棄
		hamon::ranges::destroy(r2);

		// メモリ解放
		alloc.deallocate(p, size);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesUninitializedCopyTest)
{
	EXPECT_TRUE((test<test_input_range,   test_forward_range>()));
	EXPECT_TRUE((test<test_forward_range, test_forward_range>()));

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<ThrowOnCopy> alloc;

		const std::size_t size = 3;
		auto* p = alloc.allocate(size);

		const ThrowOnCopy v[] = {10,11,12,13};

		EXPECT_EQ(4, ThrowOnCopy::count);
		EXPECT_EQ(0, ThrowOnCopy::copy_count);

		hamon::ranges::uninitialized_copy(v, v + size, p, p + size);

		EXPECT_EQ(7, ThrowOnCopy::count);
		EXPECT_EQ(3, ThrowOnCopy::copy_count);

		EXPECT_ANY_THROW(hamon::ranges::uninitialized_copy(v, v + size, p, p + size));

		EXPECT_EQ(7, ThrowOnCopy::count);
		EXPECT_EQ(3, ThrowOnCopy::copy_count);

		hamon::ranges::destroy(p, p + size);
		alloc.deallocate(p, size);

		EXPECT_EQ(4, ThrowOnCopy::count);
		EXPECT_EQ(0, ThrowOnCopy::copy_count);
	}
	EXPECT_EQ(0, ThrowOnCopy::count);
#endif
}

}	// namespace ranges_uninitialized_copy_test

}	// namespace hamon_memory_test
