/**
 *	@file	unit_test_qvm_quaternion_real.cpp
 *
 *	@brief	realのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, RealTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, quaternion( 0, 0, 0, 0).real());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, quaternion( 1, 2, 3, 4).real());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, quaternion(-1, 2, 3, 4).real());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, quaternion( 1,-2, 3, 4).real());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, quaternion( 1, 2,-3, 4).real());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, quaternion( 1, 2, 3,-4).real());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, quaternion( 5, 6, 7, 8).real());
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
