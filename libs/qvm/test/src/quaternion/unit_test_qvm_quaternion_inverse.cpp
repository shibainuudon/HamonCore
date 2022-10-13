/**
 *	@file	unit_test_qvm_quaternion_inverse.cpp
 *
 *	@brief	inverseのテスト
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

TYPED_TEST(QuaternionFloatTest, InverseTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		HAMON_CONSTEXPR quaternion q1(1, 2, 3, 4);
		HAMON_CONSTEXPR auto const q1_inv = inverse(q1);
		static_assert(std::is_same<decltype(q1_inv), quaternion const>::value, "");

		HAMON_CONSTEXPR double error = 0.000001;

		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.03333333333333333, (double)q1_inv[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.06666666666666666, (double)q1_inv[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.10000000000000000, (double)q1_inv[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.13333333333333333, (double)q1_inv[3], error);

		// あるクォータニオンとその逆クォータニオンをかけると単位クォータニオンになる
		HAMON_CONSTEXPR auto const q2 = q1 * q1_inv;
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)q2[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)q2[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)q2[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, (double)q2[3], error);
	}
	{
		HAMON_CONSTEXPR quaternion q1(9, 41, -5, 6);
		HAMON_CONSTEXPR auto const q1_inv = inverse(q1);
		static_assert(std::is_same<decltype(q1_inv), quaternion const>::value, "");

		HAMON_CONSTEXPR double error = 0.000001;

		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.00493691716950082, (double)q1_inv[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.02249040043883708, (double)q1_inv[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00274273176083379, (double)q1_inv[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00329127811300054, (double)q1_inv[3], error);

		// あるクォータニオンとその逆クォータニオンをかけると単位クォータニオンになる
		HAMON_CONSTEXPR auto const q2 = q1 * q1_inv;
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)q2[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)q2[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)q2[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, (double)q2[3], error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
