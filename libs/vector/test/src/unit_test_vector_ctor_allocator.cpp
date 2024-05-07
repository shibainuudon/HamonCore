/**
 *	@file	unit_test_vector_ctor_allocator.cpp
 *
 *	@brief	Allocatorを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit vector(const Allocator&) noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
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
	using Allocator = std::allocator<T>;
	using Vector = hamon::vector<T, Allocator>;

	static_assert( hamon::is_constructible<Vector, Allocator const&>::value, "");
	static_assert( hamon::is_nothrow_constructible<Vector, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Vector, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, Allocator const&>::value, "");

	{
		Allocator alloc;
		Vector v(alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	{
		Allocator alloc;
		Vector v{alloc};
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	//{
	//	Allocator alloc;
	//	Vector v = {alloc};		// explicit指定されているので、これはできない
	//	VERIFY(v.size() == 0);
	//	VERIFY(v.empty());
	//}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, CtorAllocatorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_allocator_test

}	// namespace hamon_vector_test
