/**
 *	@file	unit_test_qvm_quaternion_rotation.cpp
 *
 *	@brief	rotationのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/qvm/vector.hpp>
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

TYPED_TEST(QuaternionFloatTest, RotationTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3{}, 0.0f)), quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3{}, 0.0)),  quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3{}, 0.0L)), quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3i{}, 0.0f)), quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3i{}, 0.0)),  quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3i{}, 0.0L)), quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3f{}, 0.0f)), quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3f{}, 0.0)),  quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion::rotation(vector3f{}, 0.0L)), quaternion>::value, "");

	HAMON_CXX11_CONSTEXPR double const error = 0.0000001;

	{
		HAMON_CXX11_CONSTEXPR auto q =
			quaternion::rotation(vector3{1, 0, 0}, hamon::degrees_to_radians(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion::identity(), q);
	}
	{
		HAMON_CXX11_CONSTEXPR auto q =
			quaternion::rotation(vector3{1, 0, 0}, hamon::degrees_to_radians(60));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378, (double)q[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto q =
			quaternion::rotation(vector3{0, 2, 0}, hamon::degrees_to_radians(60));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378, (double)q[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto q =
			quaternion::rotation(vector3{0, 0, -3}, hamon::degrees_to_radians(60));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.50000000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378, (double)q[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto q =
			quaternion::rotation(vector3{3, -4, 5}, hamon::degrees_to_radians(90));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.30000000000, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.40000000000, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)q[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR vector3 axis{1, 2, 3};
		HAMON_CXX11_CONSTEXPR auto const q1 =
			quaternion::rotation(axis, hamon::degrees_to_radians(T{30}));
		HAMON_CXX11_CONSTEXPR auto const q2 =
			quaternion::rotation(axis, hamon::units::degrees<T>{30});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[0], (double)q2[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[1], (double)q2[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[2], (double)q2[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[3], (double)q2[3], error);
	}
	{
		HAMON_CXX11_CONSTEXPR vector3 axis{3, -2, 1};
		HAMON_CXX11_CONSTEXPR auto const q1 =
			quaternion::rotation(axis, hamon::degrees_to_radians(T{45}));
		HAMON_CXX11_CONSTEXPR auto const q2 =
			quaternion::rotation(axis, hamon::units::degrees<T>{45});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[0], (double)q2[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[1], (double)q2[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[2], (double)q2[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)q1[3], (double)q2[3], error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
