/**
 *	@file	unit_test_qvm_quaternion_length_sq.cpp
 *
 *	@brief	length_sqのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, LengthSqTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, length_sq(quaternion(0, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  9, length_sq(quaternion(3, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16, length_sq(quaternion(0, 4, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 25, length_sq(quaternion(0, 0,-5, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 36, length_sq(quaternion(0, 0, 0, 6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 30, length_sq(quaternion(1, 2, 3, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 30, length_sq(quaternion(1,-2, 3, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 30, length_sq(quaternion(1, 2, 3,-4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(109, length_sq(quaternion(4,-8, 5, 2)));
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
