/**
 *	@file	unit_test_qvm_matrix_look_to_lh.cpp
 *
 *	@brief	look_to_lh のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixFloatTest, LookToLHTest)
{
	using T = TypeParam;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(hamon::is_same<
		decltype(matrix4x4::look_to_lh(vector3{}, vector3{}, vector3{})),
		matrix4x4
	>::value, "");

	{
		HAMON_CONSTEXPR vector3 const eye(1, 2, 3);
		HAMON_CONSTEXPR vector3 const at(4, 5, 6);
		HAMON_CONSTEXPR vector3 const up(0, 1, 0);
		HAMON_CONSTEXPR vector3 const direction = at - eye;

		HAMON_CONSTEXPR auto const m = matrix4x4::look_to_lh(eye, direction, up);

		HAMON_CONSTEXPR matrix4x4 const expected
		{
			 0.707107f, -0.408248f,  0.57735f, 0,
			 0,          0.816497f,  0.57735f, 0,
			-0.707107f, -0.408248f,  0.57735f, 0,
			 1.41421f,   0,         -3.4641f,  1,
		};

		HAMON_CONSTEXPR double const error = 0.00001;
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		HAMON_CONSTEXPR vector3 const eye(12, 7, -1);
		HAMON_CONSTEXPR vector3 const at(-5, 41, 1);
		HAMON_CONSTEXPR vector3 const up(0, 0, 1);
		HAMON_CONSTEXPR vector3 const direction = at - eye;

		HAMON_CONSTEXPR auto const m = matrix4x4::look_to_lh(eye, direction, up);

		HAMON_CONSTEXPR matrix4x4 const expected
		{
			-0.894427f,  0.0234969f, -0.446596f,  0,
			-0.447214f, -0.0469938f,  0.893192f,  0,
			-0,          0.998619f,   0.0525407f, 0,
			13.8636f,    1.04561f,   -0.840651f,  1,
		};

		HAMON_CONSTEXPR double const error = 0.0001;
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
