/**
 *	@file	unit_test_qvm_matrix_perspective_lh.cpp
 *
 *	@brief	perspective_lh のテスト
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

TYPED_TEST(MatrixFloatTest, PerspectiveLHTest)
{
	using T = TypeParam;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	static_assert(std::is_same<
		decltype(matrix4x4::perspective_lh(T{}, T{}, T{}, T{})),
		matrix4x4
	>::value, "");

	{
		HAMON_CONSTEXPR T fovy = hamon::degrees_to_radians(45.0f);
		HAMON_CONSTEXPR T aspect = 4.0f / 3.0f;
		HAMON_CONSTEXPR T zn = 1;
		HAMON_CONSTEXPR T zf = 10;

		auto const m = matrix4x4::perspective_lh(fovy, aspect, zn, zf);

		HAMON_CONSTEXPR matrix4x4 const expected
		{
			T(1.81066006185294), 0,                     0,                      0,
			0,                   T(2.4142134877530865), 0,                      0,
			0,                   0,                     T( 1.111111164093017),  1,
			0,                   0,                     T(-1.111111164093017),  0,
		};

		HAMON_CONSTEXPR double error = 0.0000001;
		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		auto const m = matrix4x4::perspective_lh(
			hamon::degrees_to_radians(60.0f),
			T(16.0 / 9.0),
			0.5f,
			5000);

		HAMON_CONSTEXPR matrix4x4 const expected
		{
			T(0.97427853921501106), 0,                     0,                   0,
			0,                      T(1.7320507492870254), 0,                   0,
			0,                      0,                     T( 1.0001000165939), 1,
			0,                      0,                     T(-0.5000500082969), 0,
		};

		HAMON_CONSTEXPR double error = 0.000001;
		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
