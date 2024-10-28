/**
 *	@file	unit_test_deque_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	deque(deque&&);
 *	deque(deque&&, const type_identity_t<Allocator>&);
 */

#include <hamon/deque.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_move_test
{

template <typename T>
struct MyAllocator1
{
	using value_type = T;
	using is_always_equal = hamon::false_type;

	int id;

	MyAllocator1() : id(13) {}

	MyAllocator1(int i) : id(i) {}

	MyAllocator1(MyAllocator1 const& x) = default;

	MyAllocator1(MyAllocator1&& x) : id(x.id) { x.id = 0; }

	template <typename U>
	MyAllocator1(MyAllocator1<U> const& a) : id(a.id) {}

	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	bool operator==(MyAllocator1 const& rhs) const
	{
		return id == rhs.id;
	}

	bool operator!=(MyAllocator1 const& rhs) const
	{
		return id != rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = hamon::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;

	static_assert( hamon::is_constructible<Deque, Deque&&>::value, "");
	static_assert( hamon::is_constructible<Deque, Deque&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_DEQUE)
	static_assert( hamon::is_nothrow_constructible<Deque, Deque&&>::value, "");
	static_assert( hamon::is_nothrow_constructible<Deque, Deque&&, Allocator const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Deque, Deque&&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Deque, Deque&&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, Deque&&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, Deque&&, Allocator const&>::value, "");

	{
		Allocator alloc;
		Deque v1{{1,2,3}, alloc};
		Deque v2{hamon::move(v1)};
		VERIFY(v1.get_allocator() == alloc);
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(v1.empty());
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}
	{
		Allocator alloc;
		Deque v1{1,2,3};
		Deque v2{hamon::move(v1), alloc};
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(v1.empty());
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}

	return true;
}

template <typename T>
bool test2()
{
	using Allocator = MyAllocator1<T>;
	using Deque = hamon::deque<T, Allocator>;

	{
		Allocator alloc{42};
		Deque v1{{1,2,3}, alloc};
		Deque v2{hamon::move(v1)};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator().id == 0);
		VERIFY(v2.get_allocator().id == 42);
	}
	{
		Allocator alloc1{42};
		Allocator alloc2{43};
		Deque v1{{1,2,3}, alloc1};
		Deque v2{hamon::move(v1), alloc2};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator().id == 42);
		VERIFY(v2.get_allocator().id == 43);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtorMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

}	// namespace ctor_move_test

}	// namespace hamon_deque_test
