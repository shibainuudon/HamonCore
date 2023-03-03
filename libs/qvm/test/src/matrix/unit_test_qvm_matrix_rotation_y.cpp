/**
 *	@file	unit_test_qvm_matrix_rotation_y.cpp
 *
 *	@brief	rotation_y のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include <hamon/units/degree.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixFloatTest, RotationYTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;

	static_assert(hamon::is_same<decltype(matrix3x3::rotation_y(0.0f)), matrix3x3>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x3::rotation_y(0.0)),  matrix3x3>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x3::rotation_y(0.0L)), matrix3x3>::value, "");

	{
		HAMON_CXX11_CONSTEXPR auto const m = matrix3x3::rotation_y(hamon::degrees_to_radians(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(matrix3x3::identity(), m);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const m = matrix3x3::rotation_y(hamon::degrees_to_radians(45));
		HAMON_CXX11_CONSTEXPR matrix3x3 const expected
		{
			T(0.70710676908493042), T(0), T(-0.70710676908493042),
			T(0),                   T(1), T( 0),
			T(0.70710676908493042), T(0), T( 0.70710676908493042),
		};
		HAMON_CXX11_CONSTEXPR double error = 0.0000001;
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
		HAMON_CXX11_CONSTEXPR auto const m = matrix3x3::rotation_y(hamon::degrees_to_radians(90));
		HAMON_CXX11_CONSTEXPR matrix3x3 const expected
		{
			0,  0, -1,
			0,  1,  0,
			1,  0,  0,
		};
		HAMON_CXX11_CONSTEXPR double error = 0.000000000000001;
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
		HAMON_CXX11_CONSTEXPR auto const m1 = matrix3x3::rotation_y(hamon::degrees_to_radians(T(30)));
		HAMON_CXX11_CONSTEXPR auto const m2 = matrix3x3::rotation_y(hamon::units::degrees<T>{30});
		HAMON_CXX11_CONSTEXPR double error = 0.000000000000001;
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][0], (double)m2[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][1], (double)m2[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][2], (double)m2[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][0], (double)m2[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][1], (double)m2[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][2], (double)m2[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][0], (double)m2[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][1], (double)m2[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][2], (double)m2[2][2], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const m1 = matrix3x3::rotation_y(hamon::degrees_to_radians(T(45)));
		HAMON_CXX11_CONSTEXPR auto const m2 = matrix3x3::rotation_y(hamon::units::degrees<T>{45});
		HAMON_CXX11_CONSTEXPR double error = 0.000000000000001;
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][0], (double)m2[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][1], (double)m2[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][2], (double)m2[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][0], (double)m2[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][1], (double)m2[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][2], (double)m2[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][0], (double)m2[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][1], (double)m2[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][2], (double)m2[2][2], error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto const m1 = matrix3x3::rotation_y(hamon::degrees_to_radians(T(60)));
		HAMON_CXX11_CONSTEXPR auto const m2 = matrix3x3::rotation_y(hamon::units::degrees<T>{60});
		HAMON_CXX11_CONSTEXPR double error = 0.000000000000001;
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][0], (double)m2[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][1], (double)m2[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[0][2], (double)m2[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][0], (double)m2[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][1], (double)m2[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[1][2], (double)m2[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][0], (double)m2[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][1], (double)m2[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)m1[2][2], (double)m2[2][2], error);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
