/**
 *	@file	unit_test_qvm_matrix_viewport.cpp
 *
 *	@brief	viewport のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, ViewportTest)
{
	using T = TypeParam;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;

	static_assert(std::is_same<
		decltype(matrix4x4::viewport(T{}, T{}, T{}, T{}, T{}, T{})),
		matrix4x4
	>::value, "");

	{
		HAMON_CONSTEXPR auto const m =
			matrix4x4::viewport(0, 0, 640, 480, 0, 1);

		HAMON_CONSTEXPR matrix4x4 const expected
		{
			320,   0, 0, 0,
			  0, 240, 0, 0,
			  0,   0, 1, 0,
			320, 240, 0, 1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		HAMON_CONSTEXPR auto const m =
			matrix4x4::viewport(10, 20, 800, 600, -1, 1);

		HAMON_CONSTEXPR matrix4x4 const expected
		{
			400,   0,  0, 0,
			  0, 300,  0, 0,
			  0,   0,  2, 0,
			410, 320, -1, 1,
		};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, m);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
