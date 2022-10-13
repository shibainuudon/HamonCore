/**
 *	@file	unit_test_qvm_matrix_rotation.cpp
 *
 *	@brief	rotation のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/qvm/vector.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixFloatTest, RotationTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(std::is_same<decltype(matrix3x3::rotation(vector3{}, 0.0f)), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::rotation(vector3{}, 0.0)),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::rotation(vector3{}, 0.0L)), matrix3x3>::value, "");

	{
		auto const m = matrix3x3::rotation(
			vector3{1, 2, 3}, hamon::degrees_to_radians(90));

		HAMON_CONSTEXPR matrix3x3 const expected
		{
			T( 0.07142856717109680), T(0.94464081525802612), T(-0.32023677229881287),
			T(-0.65892654657363892), T(0.28571426868438721), T( 0.69583261013031006),
			T( 0.74880814552307129), T(0.16131016612052917), T( 0.64285707473754883),
		};
		HAMON_CONSTEXPR double error = 0.000001;
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
		auto const m = matrix3x3::rotation(
			vector3{-1, 1, 10}, hamon::degrees_to_radians(120));

		HAMON_CONSTEXPR matrix3x3 const expected
		{
			T(-0.48529410362243652), T( 0.84278708696365356), T(-0.23280812799930573),
			T(-0.87219887971878052), T(-0.48529410362243652), T( 0.06130953878164291),
			T(-0.06130953878164291), T( 0.23280812799930573), T( 0.97058844566345215),
		};
		HAMON_CONSTEXPR double error = 0.000001;
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
