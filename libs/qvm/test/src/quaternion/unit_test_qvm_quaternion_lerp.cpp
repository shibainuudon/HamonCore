/**
 *	@file	unit_test_qvm_quaternion_lerp.cpp
 *
 *	@brief	lerpのテスト
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

TYPED_TEST(QuaternionFloatTest, LerpTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(std::is_same<decltype(lerp(quaternion{}, quaternion{}, T{})),  quaternion>::value, "");
	static_assert(std::is_same<decltype(lerp(quaternion{}, quaternion{}, 0.0f)), quaternion>::value, "");
	static_assert(std::is_same<decltype(lerp(quaternion{}, quaternion{}, 0.0L)), hamon::qvm::quaternion<long double>>::value, "");

	{
		HAMON_CONSTEXPR quaternion q1 {  0,  0,  0,  0 };
		HAMON_CONSTEXPR quaternion q2 { 10, 20, 30, 40 };

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0.0,  0.0,  0.0,  0.0), lerp(q1, q2, T(0.00)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 2.5,  5.0,  7.5, 10.0), lerp(q1, q2, T(0.25)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 5.0, 10.0, 15.0, 20.0), lerp(q1, q2, T(0.50)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 7.5, 15.0, 22.5, 30.0), lerp(q1, q2, T(0.75)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(10.0, 20.0, 30.0, 40.0), lerp(q1, q2, T(1.00)));
	}
	{
		HAMON_CONSTEXPR quaternion q1 { -10,  10,  20, -30 };
		HAMON_CONSTEXPR quaternion q2 {  10, -20, -30,  40 };

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-10.0,  10.0,  20.0, -30.0), lerp(q1, q2, 0.00f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( -5.0,   2.5,   7.5, -12.5), lerp(q1, q2, 0.25f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(  0.0,  -5.0,  -5.0,   5.0), lerp(q1, q2, 0.50f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(  5.0, -12.5, -17.5,  22.5), lerp(q1, q2, 0.75f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 10.0, -20.0, -30.0,  40.0), lerp(q1, q2, 1.00f));
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
