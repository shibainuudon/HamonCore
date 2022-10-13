/**
 *	@file	unit_test_qvm_matrix_inverse.cpp
 *
 *	@brief	inverse のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, InverseTest)
{
	using T = TypeParam;
	using matrix2x2 = hamon::qvm::matrix<T, 2, 2>;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(std::is_same<decltype(inverse(matrix2x2{})), matrix2x2>::value, "");
	static_assert(std::is_same<decltype(inverse(matrix3x3{})), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(inverse(matrix4x4{})), matrix4x4>::value, "");

	// matrix2x2
	{
		HAMON_CONSTEXPR matrix2x2 const m
		{
			3, 4,
			1, 1,
		};

		HAMON_CONSTEXPR auto const m_inv = inverse(m);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-1,  4), m_inv[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 1, -3), m_inv[1]);

		// 逆行列の逆行列はもとの行列にもどる
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m, inverse(m_inv));

		// 行列とその逆行列をかけると単位行列になる
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(matrix2x2::identity(), m * m_inv);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(matrix2x2::identity(), m_inv * m);
	}

	// matrix3x3
	{
		HAMON_CONSTEXPR matrix3x3 const m
		{
			3, 2, 1,
			1, 3, 1,
			2, 2, 1,
		};

		HAMON_CONSTEXPR auto const m_inv = inverse(m);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1,  0, -1), m_inv[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1,  1, -2), m_inv[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-4, -2,  7), m_inv[2]);

		// 逆行列の逆行列はもとの行列にもどる
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m, inverse(m_inv));

		// 行列とその逆行列をかけると単位行列になる
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(matrix3x3::identity(), m * m_inv);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(matrix3x3::identity(), m_inv * m);
	}

	// matrix4x4
	{
		HAMON_CONSTEXPR matrix4x4 const m
		{
			 1,  0,  1,  2,
			-1,  1,  1,  1,
			 1, -1,  0,  1,
			 1,  1, -1, -2,
		};

		HAMON_CONSTEXPR auto const m_inv = inverse(m);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 1, -1, -1,  0), m_inv[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-1,  2,  2,  1), m_inv[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 4, -5, -7, -2), m_inv[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-2,  3,  4,  1), m_inv[3]);

		// 逆行列の逆行列はもとの行列にもどる
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m, inverse(m_inv));

		// 行列とその逆行列をかけると単位行列になる
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(matrix4x4::identity(), m * m_inv);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(matrix4x4::identity(), m_inv * m);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
