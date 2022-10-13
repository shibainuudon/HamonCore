/**
 *	@file	unit_test_qvm_matrix_diagonal.cpp
 *
 *	@brief	diagonal のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, DiagonalTest)
{
	using T = TypeParam;
	using matrix2x2 = hamon::qvm::matrix<T, 2, 2>;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(std::is_same<decltype(matrix2x2::diagonal(T{}, T{})), matrix2x2>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::diagonal(T{}, T{}, T{})), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x4::diagonal(T{}, T{}, T{}, T{})), matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix2x2::diagonal(vector2{})), matrix2x2>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::diagonal(vector3{})), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x4::diagonal(vector4{})), matrix4x4>::value, "");

	{
		HAMON_CONSTEXPR auto const m = matrix2x2::diagonal(1, 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(1, 0), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(0, 2), m[1]);
	}
	{
		HAMON_CONSTEXPR auto const m = matrix2x2::diagonal(vector2{-3, 4});
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-3, 0), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 0, 4), m[1]);
	}
	{
		HAMON_CONSTEXPR auto const m = matrix3x3::diagonal(1, 2, 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(1, 0, 0), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(0, 2, 0), m[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(0, 0, 3), m[2]);
	}
	{
		HAMON_CONSTEXPR auto const m = matrix3x3::diagonal(vector3{-4, 5, -6});
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-4,  0,  0), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0,  5,  0), m[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0,  0, -6), m[2]);
	}

	{
		HAMON_CONSTEXPR auto const m = matrix4x4::diagonal(1, 2, 3, 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(1, 0, 0, 0), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(0, 2, 0, 0), m[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(0, 0, 3, 0), m[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(0, 0, 0, 4), m[3]);
	}
	{
		HAMON_CONSTEXPR auto const m = matrix4x4::diagonal(vector4{-4, 5, -6, 7});
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-4,  0,  0,  0), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0,  5,  0,  0), m[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0,  0, -6,  0), m[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0,  0,  0,  7), m[3]);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
