/**
 *	@file	unit_test_vector_ctor_n.cpp
 *
 *	@brief	要素数を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit vector(size_type n, const Allocator& = Allocator());
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
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
	using Vector = hamon::vector<T, Allocator>;
	using SizeType = typename Vector::size_type;

	static_assert( hamon::is_constructible<Vector, SizeType>::value, "");
	static_assert( hamon::is_constructible<Vector, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Vector, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Vector, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Vector, SizeType>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Vector, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, SizeType, Allocator const&>::value, "");

	{
		Allocator alloc;
		Vector v(3, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
		VERIFY(v[2] == T{});
	}
	{
		Vector v(2);
		VERIFY(v.size() == 2);
		VERIFY(!v.empty());
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, CtorNTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_n_test

}	// namespace hamon_vector_test
