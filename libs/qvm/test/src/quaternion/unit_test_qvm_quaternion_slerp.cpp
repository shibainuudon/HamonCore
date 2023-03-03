/**
 *	@file	unit_test_qvm_quaternion_slerp.cpp
 *
 *	@brief	slerpのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

template <typename quaternion, typename T>
inline HAMON_CXX14_CONSTEXPR void
SlerpTest(quaternion const& q1, quaternion const& q2, T t, quaternion const& expected, double error)
{
	EXPECT_TRUE(q1 == slerp(q1, q2, T(-1.0)));
	EXPECT_TRUE(q1 == slerp(q1, q2, T(-0.1)));
	EXPECT_TRUE(q1 == slerp(q1, q2, T( 0.0)));
	EXPECT_TRUE(q2 == slerp(q1, q2, T( 1.0)));
	EXPECT_TRUE(q2 == slerp(q1, q2, T( 1.1)));
	EXPECT_TRUE(q2 == slerp(q1, q2, T( 2.0)));

	auto q = slerp(q1, q2, t);
	static_assert(hamon::is_same<decltype(q), quaternion>::value, "");
	EXPECT_NEAR((double)expected[0], (double)q[0], error);
	EXPECT_NEAR((double)expected[1], (double)q[1], error);
	EXPECT_NEAR((double)expected[2], (double)q[2], error);
	EXPECT_NEAR((double)expected[3], (double)q[3], error);
}

TYPED_TEST(QuaternionFloatTest, SlerpTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	HAMON_CONSTEXPR double const error = 0.000001;

	{
		auto const q1 = quaternion::rotation_x(hamon::degrees_to_radians(  0));
		auto const q2 = quaternion::rotation_x(hamon::degrees_to_radians(180));
		SlerpTest(q1, q2, T(0.25), quaternion::rotation_x(hamon::degrees_to_radians( 45)), error);
		SlerpTest(q1, q2, T(0.50), quaternion::rotation_x(hamon::degrees_to_radians( 90)), error);
		SlerpTest(q1, q2, T(0.75), quaternion::rotation_x(hamon::degrees_to_radians(135)), error);
	}
	{
		auto const q1 = quaternion::rotation_y(hamon::degrees_to_radians(  0));
		auto const q2 = quaternion::rotation_y(hamon::degrees_to_radians(  1));
		SlerpTest(q1, q2,   0.25f, quaternion::rotation_y(hamon::degrees_to_radians( 0.25)), error);
		SlerpTest(q1, q2,   0.50f, quaternion::rotation_y(hamon::degrees_to_radians( 0.50)), error);
		SlerpTest(q1, q2,   0.75f, quaternion::rotation_y(hamon::degrees_to_radians( 0.75)), error);
	}
	{
		auto const q1 = quaternion::rotation_z(hamon::degrees_to_radians( 30));
		auto const q2 = quaternion::rotation_z(hamon::degrees_to_radians(210));
		SlerpTest(q1, q2,   0.25,  quaternion::rotation_z(hamon::degrees_to_radians( 75)), error);
		SlerpTest(q1, q2,   0.50,  quaternion::rotation_z(hamon::degrees_to_radians(120)), error);
		SlerpTest(q1, q2,   0.75,  quaternion::rotation_z(hamon::degrees_to_radians(165)), error);
	}
	{
		auto const q1 = quaternion::rotation_x(hamon::degrees_to_radians(180));
		auto const q2 = quaternion::rotation_x(hamon::degrees_to_radians( 90));
		SlerpTest(q1, q2, T(0.25), quaternion::rotation_x(hamon::degrees_to_radians(157.5)), error);
		SlerpTest(q1, q2, T(0.50), quaternion::rotation_x(hamon::degrees_to_radians(135.0)), error);
		SlerpTest(q1, q2, T(0.75), quaternion::rotation_x(hamon::degrees_to_radians(112.5)), error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
