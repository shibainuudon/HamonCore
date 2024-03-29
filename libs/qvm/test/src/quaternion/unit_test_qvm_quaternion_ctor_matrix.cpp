﻿/**
 *	@file	unit_test_qvm_quaternion_ctor_matrix.cpp
 *
 *	@brief	matrixを受け取る、quaternionのコンストラクタのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/qvm/matrix.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionFloatTest, CtorMatrixTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;

	static_assert( hamon::is_constructible<quaternion, matrix3x3 const&>::value, "");
	static_assert( hamon::is_nothrow_constructible<quaternion, matrix3x3 const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<quaternion, matrix3x3 const&>::value, "");

	HAMON_CONSTEXPR const double error = 0.0000001;

	{
		HAMON_CXX14_CONSTEXPR const auto m = matrix3x3::identity();
		HAMON_CXX14_CONSTEXPR const quaternion q(m);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quaternion::identity(), q);
	}
	{
		HAMON_CXX14_CONSTEXPR const auto angle = hamon::degrees_to_radians(30);
		HAMON_CXX14_CONSTEXPR const auto m = matrix3x3::rotation_x(angle);
		HAMON_CXX14_CONSTEXPR const quaternion q(m);
		HAMON_CXX14_CONSTEXPR const auto expected = quaternion::rotation_x(angle);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[0], (double)q[0], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[1], (double)q[1], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[2], (double)q[2], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[3], (double)q[3], error);
	}
	{
		HAMON_CXX14_CONSTEXPR const auto angle = hamon::degrees_to_radians(45);
		HAMON_CXX14_CONSTEXPR const auto m = matrix3x3::rotation_y(angle);
		HAMON_CXX14_CONSTEXPR const quaternion q(m);
		HAMON_CXX14_CONSTEXPR const auto expected = quaternion::rotation_y(angle);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[0], (double)q[0], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[1], (double)q[1], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[2], (double)q[2], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[3], (double)q[3], error);
	}
	{
		HAMON_CXX14_CONSTEXPR const auto angle = hamon::degrees_to_radians(90);
		HAMON_CXX14_CONSTEXPR const auto m = matrix3x3::rotation_z(angle);
		HAMON_CXX14_CONSTEXPR const quaternion q(m);
		HAMON_CXX14_CONSTEXPR const auto expected = quaternion::rotation_z(angle);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[0], (double)q[0], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[1], (double)q[1], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[2], (double)q[2], error);
		HAMON_CXX14_CONSTEXPR_EXPECT_NEAR((double)expected[3], (double)q[3], error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
