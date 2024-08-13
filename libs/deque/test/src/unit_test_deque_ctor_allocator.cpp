/**
 *	@file	unit_test_deque_ctor_allocator.cpp
 *
 *	@brief	Allocatorを引数に取るコンストラクタのテスト
 *
 *	explicit deque(const Allocator&);
 */

#include <hamon/deque.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_allocator_test
{

struct S1
{
	S1() = delete;
};

struct S2
{
	S2() {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = hamon::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;

	static_assert( hamon::is_constructible<Deque, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Deque, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, Allocator const&>::value, "");

	{
		Allocator alloc;
		Deque v(alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	{
		Allocator alloc;
		Deque v{alloc};
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	//{
	//	Allocator alloc;
	//	Deque v = {alloc};		// explicit指定されているので、これはできない
	//	VERIFY(v.size() == 0);
	//	VERIFY(v.empty());
	//}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtorAllocatorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_allocator_test

}	// namespace hamon_deque_test
