/**
 *	@file	unit_test_vector_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	constexpr vector(const vector& x);
 *	constexpr vector(const vector&, const type_identity_t<Allocator>&);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace ctor_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Allocator = std::allocator<T>;
	using Vector = hamon::vector<T, Allocator>;

	{
		Vector const v1{1,2,3};
		Vector v2{v1};
		VERIFY(v2.get_allocator() == v1.get_allocator());
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}
	{
		Allocator alloc;
		Vector const v1{1,2,3};
		Vector v2{v1, alloc};
		VERIFY(v2.get_allocator() == v1.get_allocator());
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, CtorCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace ctor_copy_test

}	// namespace hamon_vector_test
