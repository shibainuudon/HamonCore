/**
 *	@file	unit_test_qvm_quaternion_rotation_y.cpp
 *
 *	@brief	rotation_yのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include <hamon/units/degree.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionFloatTest, RotationYTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(hamon::is_same<decltype(quaternion::rotation_y(0.0f)), quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation_y(0.0)),  quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation_y(0.0L)), quaternion>::value, "");

	HAMON_CXX11_CONSTEXPR double const error = 0.0000001;

	{
		HAMON_CXX11_CONSTEXPR auto const q =
			quaternion::rotation_y(hamon::degrees_to_radians(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion::identity(), q);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const q =
			quaternion::rotation_y(hamon::degrees_to_radians(45));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.38268343236, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.92387953251, (double)q[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const q =
			quaternion::rotation_y(hamon::degrees_to_radians(90));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)q[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const q =
			quaternion::rotation_y(hamon::degrees_to_radians(180));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const q1 =
			quaternion::rotation_y(hamon::degrees_to_radians(T{30}));
		HAMON_CXX11_CONSTEXPR auto const q2 =
			quaternion::rotation_y(hamon::units::degrees<T>{30});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[0], (double)q2[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[1], (double)q2[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[2], (double)q2[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[3], (double)q2[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const q1 =
			quaternion::rotation_y(hamon::degrees_to_radians(T{45}));
		HAMON_CXX11_CONSTEXPR auto const q2 =
			quaternion::rotation_y(hamon::units::degrees<T>{45});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[0], (double)q2[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[1], (double)q2[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[2], (double)q2[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[3], (double)q2[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const q1 =
			quaternion::rotation_y(hamon::degrees_to_radians(T{60}));
		HAMON_CXX11_CONSTEXPR auto const q2 =
			quaternion::rotation_y(hamon::units::degrees<T>{60});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[0], (double)q2[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[1], (double)q2[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[2], (double)q2[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[3], (double)q2[3], error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
