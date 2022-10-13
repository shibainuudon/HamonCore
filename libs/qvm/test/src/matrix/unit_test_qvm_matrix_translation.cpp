/**
 *	@file	unit_test_qvm_matrix_translation.cpp
 *
 *	@brief	translation のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, TranslationTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector2  = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(std::is_same<decltype(matrix3x3::translation(0,    0)),    matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::translation(0.0f, 0.0f)), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::translation(0.0,  0.0f)), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::translation(0.0L, 0)),    matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::translation(vector2{})),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::translation(vector2i{})), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3::translation(vector2f{})), matrix3x3>::value, "");

	static_assert(std::is_same<decltype(matrix4x4::translation(0.0f, 0.0f, 0.0f)), matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4::translation(0,    0.0,  0.0L)), matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4::translation(vector3{})),  matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4::translation(vector3i{})), matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4::translation(vector3f{})), matrix4x4>::value, "");

	// matrix3x3
	{
		HAMON_CONSTEXPR auto const m = matrix3x3::translation(1, 2);
		HAMON_CONSTEXPR matrix3x3 const expected
		{
			1,  0,  0,
			0,  1,  0,
			1,  2,  1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		HAMON_CONSTEXPR auto const m = matrix3x3::translation(vector2{3, 4});
		HAMON_CONSTEXPR matrix3x3 const expected
		{
			1,  0,  0,
			0,  1,  0,
			3,  4,  1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m);
	}

	// matrix4x4
	{
		HAMON_CONSTEXPR auto const m = matrix4x4::translation(-4, 5, -6);
		HAMON_CONSTEXPR matrix4x4 const expected
		{
			 1,  0,  0,  0,
			 0,  1,  0,  0,
			 0,  0,  1,  0,
			-4,  5, -6,  1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		HAMON_CONSTEXPR auto const m = matrix4x4::translation(vector3{3, 4, 5});
		HAMON_CONSTEXPR matrix4x4 const expected
		{
			1,  0,  0,  0,
			0,  1,  0,  0,
			0,  0,  1,  0,
			3,  4,  5,  1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
