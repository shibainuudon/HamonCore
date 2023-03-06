/**
 *	@file	unit_test_qvm_quaternion_swap.cpp
 *
 *	@brief	swapのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/concepts/swap.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool SwapTest()
{
	using quaternion = hamon::qvm::quaternion<T>;

	quaternion q1{1, 2, 3, 4};
	quaternion q2{5, 6, 7, 8};

	q1.swap(q2);

	VERIFY(q1 == quaternion(5, 6, 7, 8));
	VERIFY(q2 == quaternion(1, 2, 3, 4));

	swap(q1, q2);

	VERIFY(q1 == quaternion(1, 2, 3, 4));
	VERIFY(q2 == quaternion(5, 6, 7, 8));

	hamon::ranges::swap(q1, q2);

	VERIFY(q1 == quaternion(5, 6, 7, 8));
	VERIFY(q2 == quaternion(1, 2, 3, 4));

	return true;
}

TYPED_TEST(QuaternionTest, SwapTest)
{
	using T = TypeParam;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
