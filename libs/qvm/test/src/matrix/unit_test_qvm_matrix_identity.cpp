/**
 *	@file	unit_test_qvm_matrix_identity.cpp
 *
 *	@brief	identity のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, IdentityTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::is_same<decltype(matrix3x3::identity()), matrix3x3>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x4::identity()), matrix4x4>::value, "");

	{
		HAMON_CONSTEXPR auto const m = matrix3x3::identity();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(1, 0, 0), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(0, 1, 0), m[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(0, 0, 1), m[2]);
	}
	{
		HAMON_CONSTEXPR auto const m = matrix4x4::identity();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(1, 0, 0, 0), m[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(0, 1, 0, 0), m[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(0, 0, 1, 0), m[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(0, 0, 0, 1), m[3]);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
