/**
 *	@file	unit_test_qvm_quaternion_rotation_y.cpp
 *
 *	@brief	rotation_yのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionFloatTest, RotationYTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(std::is_same<decltype(quaternion::rotation_y(0.0f)), quaternion>::value, "");
	static_assert(std::is_same<decltype(quaternion::rotation_y(0.0)),  quaternion>::value, "");
	static_assert(std::is_same<decltype(quaternion::rotation_y(0.0L)), quaternion>::value, "");

	HAMON_CONSTEXPR double const error = 0.0000001;

	{
		auto const q = quaternion::rotation_y(hamon::degrees_to_radians(0));
		EXPECT_EQ(quaternion::identity(), q);
	}
	{
		auto const q = quaternion::rotation_y(hamon::degrees_to_radians(45));
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.38268343236, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.92387953251, (double)q[3], error);
	}
	{
		auto const q = quaternion::rotation_y(hamon::degrees_to_radians(90));
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.70710678118, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.70710678118, (double)q[3], error);
	}
	{
		auto const q = quaternion::rotation_y(hamon::degrees_to_radians(180));
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 1.00000000000, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.00000000000, (double)q[3], error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
