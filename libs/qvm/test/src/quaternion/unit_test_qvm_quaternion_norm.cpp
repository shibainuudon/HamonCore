/**
 *	@file	unit_test_qvm_quaternion_norm.cpp
 *
 *	@brief	normのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/cmath/fabs.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, NormTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, norm(quaternion( 0, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, norm(quaternion( 3, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, norm(quaternion(-3, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, norm(quaternion( 0, 4, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, norm(quaternion( 0,-4, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, norm(quaternion( 0, 0, 5, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, norm(quaternion( 0, 0,-5, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, norm(quaternion( 0, 0, 0, 6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, norm(quaternion( 0, 0, 0,-6)));

	HAMON_CONSTEXPR double const error = 0.000001;
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(5.47722557505, (double)norm(quaternion(1, 2, 3, 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(5.47722557505, (double)norm(quaternion(1,-2,-3, 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.4403065089, (double)norm(quaternion(4,-8, 5, 2)), error);
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
