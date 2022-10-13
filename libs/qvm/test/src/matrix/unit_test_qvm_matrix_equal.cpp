/**
 *	@file	unit_test_qvm_matrix_equal.cpp
 *
 *	@brief	equalのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, EqualTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3b = hamon::qvm::matrix<bool, 3, 3>;

	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
		};

		HAMON_CONSTEXPR matrix3x3 const m2
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
		};

		HAMON_CONSTEXPR auto const m3 = hamon::qvm::equal(m1, m2);
		static_assert(std::is_same<decltype(m3), matrix3x3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][2]);
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
		};

		HAMON_CONSTEXPR matrix3x3 const m2
		{
			1, 1, 2,
			3, 4, 5,
			6, 7, 8,
		};

		HAMON_CONSTEXPR auto const m3 = hamon::qvm::equal(m1, m2);
		static_assert(std::is_same<decltype(m3), matrix3x3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][2]);
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
		};

		HAMON_CONSTEXPR matrix3x3 const m2
		{
			0, 1, 2,
			3, 0, 5,
			6, 7, 8,
		};

		HAMON_CONSTEXPR auto const m3 = hamon::qvm::equal(m1, m2);
		static_assert(std::is_same<decltype(m3), matrix3x3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][2]);
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
		};

		HAMON_CONSTEXPR matrix3x3 const m2
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 7,
		};

		HAMON_CONSTEXPR auto const m3 = hamon::qvm::equal(m1, m2);
		static_assert(std::is_same<decltype(m3), matrix3x3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[0][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[1][2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  m3[2][1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, m3[2][2]);
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
