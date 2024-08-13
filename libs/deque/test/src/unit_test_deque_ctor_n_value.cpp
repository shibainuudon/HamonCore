/**
 *	@file	unit_test_deque_ctor_n_value.cpp
 *
 *	@brief	要素数と値を引数に取るコンストラクタのテスト
 *
 *	deque(size_type n, const T& value, const Allocator& = Allocator());
 */

#include <hamon/deque.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_n_value_test
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
	using SizeType = typename Deque::size_type;

	static_assert( hamon::is_constructible<Deque, SizeType, T const&>::value, "");
	static_assert( hamon::is_constructible<Deque, SizeType, T const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, SizeType, T const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, SizeType, T const&, Allocator const&>::value, "");
//	static_assert( hamon::is_implicitly_constructible<Deque, SizeType, T const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Deque, SizeType, T const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, SizeType, T const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, SizeType, T const&, Allocator const&>::value, "");

	{
		T x{42};
		Allocator alloc;
		Deque v(3, x, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v[0] == x);
		VERIFY(v[1] == x);
		VERIFY(v[2] == x);
	}
	{
		T x{43};
		Deque v(2, x);
		VERIFY(v.size() == 2);
		VERIFY(!v.empty());
		VERIFY(v[0] == x);
		VERIFY(v[1] == x);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtorNValueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_n_value_test

}	// namespace hamon_deque_test
