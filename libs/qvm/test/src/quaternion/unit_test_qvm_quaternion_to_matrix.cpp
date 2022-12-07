/**
 *	@file	unit_test_qvm_quaternion_to_matrix.cpp
 *
 *	@brief	matrixへの変換のテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/qvm/matrix.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionFloatTest, ToMatrixTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert( std::is_constructible<matrix3x3, quaternion const&>::value, "");
	static_assert( std::is_nothrow_constructible<matrix3x3, quaternion const&>::value, "");
//	static_assert(!hamon::is_implicitly_constructible<matrix3x3, quaternion const&>::value, "");

	HAMON_CXX11_CONSTEXPR const double error = 0.000001;

	{
		HAMON_CXX11_CONSTEXPR auto q = quaternion::identity();
		HAMON_CXX11_CONSTEXPR matrix3x3 m(q);
		HAMON_CXX11_CONSTEXPR auto expected = matrix3x3::identity();

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		HAMON_CXX11_CONSTEXPR quaternion q { 1, 2, 3, 4 };
		HAMON_CXX11_CONSTEXPR matrix3x3 m(q);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-25, 28,-10), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-20,-19, 20), m[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 22,  4, -9), m[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR const auto angle = hamon::degrees_to_radians(30);
		HAMON_CXX11_CONSTEXPR const auto q = quaternion::rotation_x(angle);
		HAMON_CXX11_CONSTEXPR const matrix3x3 m(q);
		HAMON_CXX11_CONSTEXPR const auto expected = matrix3x3::rotation_x(angle);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
	{
		HAMON_CXX11_CONSTEXPR const auto angle = hamon::degrees_to_radians(45);
		HAMON_CXX11_CONSTEXPR const auto q = quaternion::rotation_y(angle);
		HAMON_CXX11_CONSTEXPR const matrix3x3 m(q);
		HAMON_CXX11_CONSTEXPR const auto expected = matrix3x3::rotation_y(angle);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
	{
		HAMON_CXX11_CONSTEXPR const auto angle = hamon::degrees_to_radians(60);
		HAMON_CXX11_CONSTEXPR const auto q = quaternion::rotation_z(angle);
		HAMON_CXX11_CONSTEXPR const matrix3x3 m(q);
		HAMON_CXX11_CONSTEXPR const auto expected = matrix3x3::rotation_z(angle);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
	{
		HAMON_CXX11_CONSTEXPR const vector3 axis{1, 2, 3};
		HAMON_CXX11_CONSTEXPR const auto angle = hamon::degrees_to_radians(90);
		HAMON_CXX11_CONSTEXPR const auto q = quaternion::rotation(axis, angle);
		HAMON_CXX11_CONSTEXPR const matrix3x3 m(q);
		HAMON_CXX11_CONSTEXPR const auto expected = matrix3x3::rotation(axis, angle);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
