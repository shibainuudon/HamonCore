/**
 *	@file	unit_test_deque_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	deque(const deque& x);
 *	deque(const deque&, const type_identity_t<Allocator>&);
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = std::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;

	{
		Deque const v1{1,2,3};
		Deque v2{v1};
		VERIFY(v2.get_allocator() == v1.get_allocator());
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}
	{
		Allocator alloc;
		Deque const v1{1,2,3};
		Deque v2{v1, alloc};
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

GTEST_TEST(DequeTest, CtorCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<double>());
}

}	// namespace ctor_copy_test

}	// namespace hamon_deque_test
