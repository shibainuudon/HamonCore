/**
 *	@file	unit_test_deque_ctor_n.cpp
 *
 *	@brief	要素数を引数に取るコンストラクタのテスト
 *
 *	explicit deque(size_type n, const Allocator& = Allocator());
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_n_test
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
	HAMON_CXX11_CONSTEXPR S2() : value(42) {}
};

HAMON_CXX11_CONSTEXPR bool operator==(S2 const& lhs, S2 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = std::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;
	using SizeType = typename Deque::size_type;

	static_assert( hamon::is_constructible<Deque, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Deque, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Deque, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Deque, SizeType, Allocator const&>::value, "");

	{
		Allocator alloc;
		Deque v(3, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
		VERIFY(v[2] == T{});
	}
	{
		Deque v(2);
		VERIFY(v.size() == 2);
		VERIFY(!v.empty());
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtorNTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<int>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<S1>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_n_test

}	// namespace hamon_deque_test
