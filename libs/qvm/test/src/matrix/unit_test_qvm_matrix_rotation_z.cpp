/**
 *	@file	unit_test_qvm_matrix_rotation_z.cpp
 *
 *	@brief	rotation_z のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixFloatTest, RotationZTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	
	static_assert(std::is_same<decltype(matrix3x3::rotation_z(0.0f)), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::rotation_z(0.0)),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::rotation_z(0.0L)), matrix3x3>::value, "");

	{
		auto const m = matrix3x3::rotation_z(hamon::degrees_to_radians(0));
		EXPECT_EQ(matrix3x3::identity(), m);
	}
	{
		auto const m = matrix3x3::rotation_z(hamon::degrees_to_radians(60));
		HAMON_CONSTEXPR matrix3x3 const expected
		{
			T( 0.5),                 T(0.86602538824081421), T(0),
			T(-0.86602538824081421), T(0.5),                 T(0),
			T( 0),                   T(0),                   T(1),
		};
		HAMON_CONSTEXPR double error = 0.0000001;
		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
	{
		auto const m = matrix3x3::rotation_z(hamon::degrees_to_radians(90));
		HAMON_CONSTEXPR matrix3x3 const expected
		{
			 0,  1,  0,
			-1,  0,  0,
			 0,  0,  1,
		};
		HAMON_CONSTEXPR double error = 0.0000000000000001;
		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
