/**
 *	@file	unit_test_qvm_matrix_frustum_rh.cpp
 *
 *	@brief	frustum_rh のテスト
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

TYPED_TEST(MatrixFloatTest, FrustumRHTest)
{
	using T = TypeParam;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	static_assert(hamon::is_same<
		decltype(matrix4x4::frustum_rh(T{}, T{}, T{}, T{}, T{}, T{})),
		matrix4x4
	>::value, "");
	
	{
		HAMON_CONSTEXPR T left   = 0;
		HAMON_CONSTEXPR T right  = 400;
		HAMON_CONSTEXPR T bottom = 0;
		HAMON_CONSTEXPR T top    = 300;
		HAMON_CONSTEXPR T nearz  = 1;
		HAMON_CONSTEXPR T farz   = 1000;

		HAMON_CONSTEXPR auto const m =
			matrix4x4::frustum_rh(left, right, bottom, top, nearz, farz);

		HAMON_CONSTEXPR matrix4x4 const expected
		{
			 T(0.005),  0,                        0,                       0,
			 0,         T(0.0066666666666666671), 0,                       0,
			 1,         1,                        T(-1.0010010004043579), -1,
			 0,         0,                        T(-1.0010010004043579),  0,
		};

		HAMON_CONSTEXPR double error = 0.000000001;
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
		HAMON_CONSTEXPR auto const m =
			matrix4x4::frustum_rh(
				-960,
				 960,
				-540,
				 540,
				0.001f,
				1000.0);		
		HAMON_CONSTEXPR matrix4x4 const expected
		{
			T(0.0000010416667161431785), 0,                        0,                       0,
			0,                           T(0.0000018518519398100), 0,                       0,
			0,                           0,                        T(-1.0000009536743164), -1,
			0,                           0,                        T(-0.0010000009788200),  0,
		};

		HAMON_CONSTEXPR double error = 0.0000001;
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
