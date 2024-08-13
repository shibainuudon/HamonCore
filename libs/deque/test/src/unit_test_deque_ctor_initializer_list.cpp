/**
 *	@file	unit_test_deque_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取るコンストラクタのテスト
 *
 *	deque(initializer_list<T>, const Allocator& = Allocator());
 */

#include <hamon/deque.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_initializer_list_test
{

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

struct S2
{
	int value;
	HAMON_CXX11_CONSTEXPR S2(int v) : value(v) {}
};

HAMON_CXX11_CONSTEXPR bool operator==(S2 const& lhs, S2 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = hamon::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;

	static_assert( hamon::is_constructible<Deque, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_constructible<Deque, std::initializer_list<T>, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, std::initializer_list<T>, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Deque, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Deque, std::initializer_list<T>, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, std::initializer_list<T>, Allocator const&>::value, "");

	{
		Deque v = {T{1}, T{2}, T{3}};
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
	}
	{
		Allocator alloc;
		Deque v({T{3}, T{1}, T{4}, T{1}, T{5}}, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{3});
		VERIFY(v[1] == T{1});
		VERIFY(v[2] == T{4});
		VERIFY(v[3] == T{1});
		VERIFY(v[4] == T{5});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtorInitializerListTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
//	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());	// TODO Visual Studio 2019 だけ？
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_initializer_list_test

}	// namespace hamon_deque_test
