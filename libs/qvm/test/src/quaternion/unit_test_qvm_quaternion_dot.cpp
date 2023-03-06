/**
 *	@file	unit_test_qvm_quaternion_dot.cpp
 *
 *	@brief	dotのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, DotTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, dot(quaternion( 0, 0, 0, 0), quaternion( 0, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, dot(quaternion( 1,-2, 3,-4), quaternion( 1, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, dot(quaternion( 1,-2, 3,-4), quaternion( 0, 1, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, dot(quaternion( 1,-2, 3,-4), quaternion( 0, 0, 1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, dot(quaternion( 1,-2, 3,-4), quaternion( 0, 0, 0, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, dot(quaternion( 1,-2, 3,-4), quaternion(-1, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, dot(quaternion( 1,-2, 3,-4), quaternion( 0,-1, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, dot(quaternion( 1,-2, 3,-4), quaternion( 0, 0,-1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, dot(quaternion( 1,-2, 3,-4), quaternion( 0, 0, 0,-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, dot(quaternion( 1,-2, 3,-4), quaternion( 2, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, dot(quaternion( 1,-2, 3,-4), quaternion( 0, 2, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, dot(quaternion( 1,-2, 3,-4), quaternion( 0, 0, 2, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8, dot(quaternion( 1,-2, 3,-4), quaternion( 0, 0, 0, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, dot(quaternion( 1,-2, 3,-4), quaternion( 1, 1, 1, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, dot(quaternion( 1,-2, 3,-4), quaternion( 1,-1, 1,-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, dot(quaternion( 1,-2, 3,-4), quaternion( 1,-2, 3,-4)));
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
