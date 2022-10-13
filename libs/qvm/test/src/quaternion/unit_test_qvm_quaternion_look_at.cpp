/**
 *	@file	unit_test_qvm_quaternion_look_at.cpp
 *
 *	@brief	look_atのテスト
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

TYPED_TEST(QuaternionFloatTest, LookAtTest)
{
	using T = TypeParam;
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(std::is_same<decltype(quaternion::look_at(vector3{}, vector3{}, vector3{})), quaternion>::value, "");
	static_assert(std::is_same<decltype(quaternioni::look_at(vector3{}, vector3{}, vector3{})), quaternioni>::value, "");
	static_assert(std::is_same<decltype(quaternionf::look_at(vector3{}, vector3{}, vector3{})), quaternionf>::value, "");

	HAMON_CONSTEXPR double const error = 0.000001;

	{
		HAMON_CONSTEXPR auto q = quaternion::look_at(
			vector3{10, 10, 10},
			vector3{30, 10, 10},
			vector3{ 0,  1,  0});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.707107, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.707107, (double)q[3], error);
	}
	{
		HAMON_CONSTEXPR auto q = quaternion::look_at(
			vector3i{10, 10, 10},
			vector3i{10,  0, 10},
			vector3i{ 0,  1,  0});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.707107, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.707107, (double)q[3], error);
	}
	{
		HAMON_CONSTEXPR auto q = quaternion::look_at(
			vector3f{10, 10, 10},
			vector3f{ 0,  0,  0},
			vector3f{ 0,  1,  0});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.279848, (double)q[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.364705, (double)q[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.115917, (double)q[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.880476, (double)q[3], error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
