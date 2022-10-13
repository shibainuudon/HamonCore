/**
 *	@file	unit_test_qvm_matrix_mul_scalar.cpp
 *
 *	@brief	スカラー積のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x3MulScalarTest()
{
	using matrix3x3  = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;
	using matrix3x3f = hamon::qvm::matrix<float, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(std::is_same<decltype(std::declval<matrix3x3&>()  *= T{}),     matrix3x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3&>()  *= int{}),   matrix3x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3&>()  *= float{}), matrix3x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3i&>() *= T{}),     matrix3x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3i&>() *= int{}),   matrix3x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3i&>() *= float{}), matrix3x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3f&>() *= T{}),     matrix3x3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3f&>() *= int{}),   matrix3x3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3f&>() *= float{}), matrix3x3f&>::value, "");

	// matrix3x3 *= スカラー
	{
		matrix3x3 m1
		{
			vector3{ 1,  2,  3},
			vector3{ 5,  6,  7},
			vector3{ 9, 10, 11},
		};
		{
			auto t = (m1 *= 2);
			static_assert(std::is_same<decltype(t), matrix3x3>::value, "");
			VERIFY(vector3( 2,  4,  6) == m1[0]);
			VERIFY(vector3(10, 12, 14) == m1[1]);
			VERIFY(vector3(18, 20, 22) == m1[2]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(std::is_same<decltype(t), matrix3x3>::value, "");
			VERIFY(vector3( 5, 10, 15) == m1[0]);
			VERIFY(vector3(25, 30, 35) == m1[1]);
			VERIFY(vector3(45, 50, 55) == m1[2]);
			VERIFY(t == m1);
		}
	}
	{
		matrix3x3i m1
		{
			vector3{ 1,  2,  3},
			vector3{ 5,  6,  7},
			vector3{ 9, 10, 11},
		};
		{
			auto t = (m1 *= 2);
			static_assert(std::is_same<decltype(t), matrix3x3i>::value, "");
			VERIFY(vector3( 2,  4,  6) == m1[0]);
			VERIFY(vector3(10, 12, 14) == m1[1]);
			VERIFY(vector3(18, 20, 22) == m1[2]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(std::is_same<decltype(t), matrix3x3i>::value, "");
			VERIFY(vector3( 5, 10, 15) == m1[0]);
			VERIFY(vector3(25, 30, 35) == m1[1]);
			VERIFY(vector3(45, 50, 55) == m1[2]);
			VERIFY(t == m1);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x4MulScalarTest()
{
	using matrix3x4  = hamon::qvm::matrix<T, 3, 4>;
	using matrix3x4i = hamon::qvm::matrix<int, 3, 4>;
	using matrix3x4f = hamon::qvm::matrix<float, 3, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(std::is_same<decltype(std::declval<matrix3x4&>()  *= T{}),     matrix3x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4&>()  *= int{}),   matrix3x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4&>()  *= float{}), matrix3x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4i&>() *= T{}),     matrix3x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4i&>() *= int{}),   matrix3x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4i&>() *= float{}), matrix3x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4f&>() *= T{}),     matrix3x4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4f&>() *= int{}),   matrix3x4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4f&>() *= float{}), matrix3x4f&>::value, "");

	// matrix3x4 *= スカラー
	{
		matrix3x4 m1
		{
			vector4{ 1,  2,  3,  4},
			vector4{ 5,  6,  7,  8},
			vector4{ 9, 10, 11, 12},
		};
		{
			auto t = (m1 *= 2);
			static_assert(std::is_same<decltype(t), matrix3x4>::value, "");
			VERIFY(vector4( 2,  4,  6,  8) == m1[0]);
			VERIFY(vector4(10, 12, 14, 16) == m1[1]);
			VERIFY(vector4(18, 20, 22, 24) == m1[2]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(std::is_same<decltype(t), matrix3x4>::value, "");
			VERIFY(vector4( 5, 10, 15, 20) == m1[0]);
			VERIFY(vector4(25, 30, 35, 40) == m1[1]);
			VERIFY(vector4(45, 50, 55, 60) == m1[2]);
			VERIFY(t == m1);
		}
	}
	{
		matrix3x4i m1
		{
			vector4{ 1,  2,  3,  4},
			vector4{ 5,  6,  7,  8},
			vector4{ 9, 10, 11, 12},
		};
		{
			auto t = (m1 *= 2);
			static_assert(std::is_same<decltype(t), matrix3x4i>::value, "");
			VERIFY(vector4( 2,  4,  6,  8) == m1[0]);
			VERIFY(vector4(10, 12, 14, 16) == m1[1]);
			VERIFY(vector4(18, 20, 22, 24) == m1[2]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(std::is_same<decltype(t), matrix3x4i>::value, "");
			VERIFY(vector4( 5, 10, 15, 20) == m1[0]);
			VERIFY(vector4(25, 30, 35, 40) == m1[1]);
			VERIFY(vector4(45, 50, 55, 60) == m1[2]);
			VERIFY(t == m1);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x3MulScalarTest()
{
	using matrix4x3  = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x3i = hamon::qvm::matrix<int, 4, 3>;
	using matrix4x3f = hamon::qvm::matrix<float, 4, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(std::is_same<decltype(std::declval<matrix4x3&>()  *= T{}),     matrix4x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3&>()  *= int{}),   matrix4x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3&>()  *= float{}), matrix4x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3i&>() *= T{}),     matrix4x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3i&>() *= int{}),   matrix4x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3i&>() *= float{}), matrix4x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3f&>() *= T{}),     matrix4x3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3f&>() *= int{}),   matrix4x3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3f&>() *= float{}), matrix4x3f&>::value, "");

	// matrix4x3 *= スカラー
	{
		matrix4x3 m1
		{
			vector3{ 1,  2,  3},
			vector3{ 5,  6,  7},
			vector3{ 9, 10, 11},
			vector3{13, 14, 15},
		};
		{
			auto t = (m1 *= 2);
			static_assert(std::is_same<decltype(t), matrix4x3>::value, "");
			VERIFY(vector3( 2,  4,  6) == m1[0]);
			VERIFY(vector3(10, 12, 14) == m1[1]);
			VERIFY(vector3(18, 20, 22) == m1[2]);
			VERIFY(vector3(26, 28, 30) == m1[3]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(std::is_same<decltype(t), matrix4x3>::value, "");
			VERIFY(vector3( 5, 10, 15) == m1[0]);
			VERIFY(vector3(25, 30, 35) == m1[1]);
			VERIFY(vector3(45, 50, 55) == m1[2]);
			VERIFY(vector3(65, 70, 75) == m1[3]);
			VERIFY(t == m1);
		}
	}
	{
		matrix4x3i m1
		{
			vector3{ 1,  2,  3},
			vector3{ 5,  6,  7},
			vector3{ 9, 10, 11},
			vector3{13, 14, 15},
		};
		{
			auto t = (m1 *= 2);
			static_assert(std::is_same<decltype(t), matrix4x3i>::value, "");
			VERIFY(vector3( 2,  4,  6) == m1[0]);
			VERIFY(vector3(10, 12, 14) == m1[1]);
			VERIFY(vector3(18, 20, 22) == m1[2]);
			VERIFY(vector3(26, 28, 30) == m1[3]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(std::is_same<decltype(t), matrix4x3i>::value, "");
			VERIFY(vector3( 5, 10, 15) == m1[0]);
			VERIFY(vector3(25, 30, 35) == m1[1]);
			VERIFY(vector3(45, 50, 55) == m1[2]);
			VERIFY(vector3(65, 70, 75) == m1[3]);
			VERIFY(t == m1);
		}
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x4MulScalarTest()
{
	using matrix4x4  = hamon::qvm::matrix<T, 4, 4>;
	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;
	using matrix4x4f = hamon::qvm::matrix<float, 4, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(std::is_same<decltype(std::declval<matrix4x4&>()  *= T{}),     matrix4x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4&>()  *= int{}),   matrix4x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4&>()  *= float{}), matrix4x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4i&>() *= T{}),     matrix4x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4i&>() *= int{}),   matrix4x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4i&>() *= float{}), matrix4x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4f&>() *= T{}),     matrix4x4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4f&>() *= int{}),   matrix4x4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4f&>() *= float{}), matrix4x4f&>::value, "");

	// matrix4x4 *= スカラー
	{
		matrix4x4 m1
		{
			vector4{ 1,  2,  3,  4},
			vector4{ 5,  6,  7,  8},
			vector4{ 9, 10, 11, 12},
			vector4{13, 14, 15, 16},
		};
		{
			auto t = (m1 *= 2);
			static_assert(std::is_same<decltype(t), matrix4x4>::value, "");
			VERIFY(vector4( 2,  4,  6,  8) == m1[0]);
			VERIFY(vector4(10, 12, 14, 16) == m1[1]);
			VERIFY(vector4(18, 20, 22, 24) == m1[2]);
			VERIFY(vector4(26, 28, 30, 32) == m1[3]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(std::is_same<decltype(t), matrix4x4>::value, "");
			VERIFY(vector4( 5, 10, 15, 20) == m1[0]);
			VERIFY(vector4(25, 30, 35, 40) == m1[1]);
			VERIFY(vector4(45, 50, 55, 60) == m1[2]);
			VERIFY(vector4(65, 70, 75, 80) == m1[3]);
			VERIFY(t == m1);
		}
	}
	{
		matrix4x4i m1
		{
			vector4{ 1,  2,  3,  4},
			vector4{ 5,  6,  7,  8},
			vector4{ 9, 10, 11, 12},
			vector4{13, 14, 15, 16},
		};
		{
			auto t = (m1 *= 2);
			static_assert(std::is_same<decltype(t), matrix4x4i>::value, "");
			VERIFY(vector4( 2,  4,  6,  8) == m1[0]);
			VERIFY(vector4(10, 12, 14, 16) == m1[1]);
			VERIFY(vector4(18, 20, 22, 24) == m1[2]);
			VERIFY(vector4(26, 28, 30, 32) == m1[3]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(std::is_same<decltype(t), matrix4x4i>::value, "");
			VERIFY(vector4( 5, 10, 15, 20) == m1[0]);
			VERIFY(vector4(25, 30, 35, 40) == m1[1]);
			VERIFY(vector4(45, 50, 55, 60) == m1[2]);
			VERIFY(vector4(65, 70, 75, 80) == m1[3]);
			VERIFY(t == m1);
		}
	}

	return true;
}

TYPED_TEST(MatrixTest, MulScalarTest)
{
	using T = TypeParam;
	using matrix3x3  = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;
	using matrix3x3f = hamon::qvm::matrix<float, 3, 3>;
	using matrix3x4  = hamon::qvm::matrix<T, 3, 4>;
	using matrix3x4i = hamon::qvm::matrix<int, 3, 4>;
	using matrix3x4f = hamon::qvm::matrix<float, 3, 4>;
	using matrix4x3  = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x3i = hamon::qvm::matrix<int, 4, 3>;
	using matrix4x3f = hamon::qvm::matrix<float, 4, 3>;
	using matrix4x4  = hamon::qvm::matrix<T, 4, 4>;
	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;
	using matrix4x4f = hamon::qvm::matrix<float, 4, 4>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(std::is_same<decltype(matrix3x3{}  * T{}),     matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3{}  * int{}),   matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3i{} * int{}),   matrix3x3i>::value, "");
	static_assert(std::is_same<decltype(matrix3x3i{} * float{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(matrix3x3f{} * int{}),   matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(matrix3x3f{} * float{}), matrix3x3f>::value, "");

	static_assert(std::is_same<decltype(matrix3x4{}  * T{}),     matrix3x4>::value, "");
	static_assert(std::is_same<decltype(matrix3x4{}  * int{}),   matrix3x4>::value, "");
	static_assert(std::is_same<decltype(matrix3x4i{} * int{}),   matrix3x4i>::value, "");
	static_assert(std::is_same<decltype(matrix3x4i{} * float{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(matrix3x4f{} * int{}),   matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(matrix3x4f{} * float{}), matrix3x4f>::value, "");

	static_assert(std::is_same<decltype(matrix4x3{}  * T{}),     matrix4x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x3{}  * int{}),   matrix4x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x3i{} * int{}),   matrix4x3i>::value, "");
	static_assert(std::is_same<decltype(matrix4x3i{} * float{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(matrix4x3f{} * int{}),   matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(matrix4x3f{} * float{}), matrix4x3f>::value, "");

	static_assert(std::is_same<decltype(matrix4x4{}  * T{}),     matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4{}  * int{}),   matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4i{} * int{}),   matrix4x4i>::value, "");
	static_assert(std::is_same<decltype(matrix4x4i{} * float{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(matrix4x4f{} * int{}),   matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(matrix4x4f{} * float{}), matrix4x4f>::value, "");

	static_assert(std::is_same<decltype(T{}     * matrix3x3{}),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix3x3{}),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix3x3i{}), matrix3x3i>::value, "");
	static_assert(std::is_same<decltype(float{} * matrix3x3i{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix3x3f{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(float{} * matrix3x3f{}), matrix3x3f>::value, "");

	static_assert(std::is_same<decltype(T{}     * matrix3x4{}),  matrix3x4>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix3x4{}),  matrix3x4>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix3x4i{}), matrix3x4i>::value, "");
	static_assert(std::is_same<decltype(float{} * matrix3x4i{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix3x4f{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(float{} * matrix3x4f{}), matrix3x4f>::value, "");

	static_assert(std::is_same<decltype(T{}     * matrix4x3{}),  matrix4x3>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix4x3{}),  matrix4x3>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix4x3i{}), matrix4x3i>::value, "");
	static_assert(std::is_same<decltype(float{} * matrix4x3i{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix4x3f{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(float{} * matrix4x3f{}), matrix4x3f>::value, "");

	static_assert(std::is_same<decltype(T{}     * matrix4x4{}),  matrix4x4>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix4x4{}),  matrix4x4>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix4x4i{}), matrix4x4i>::value, "");
	static_assert(std::is_same<decltype(float{} * matrix4x4i{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(int{}   * matrix4x4f{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(float{} * matrix4x4f{}), matrix4x4f>::value, "");

	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			vector3{10, 12, 14},
			vector3{20, 22, 24},
			vector3{30, 32, 34},
		};
		// matrix3x3 * スカラー -> matrix3x3
		{
			HAMON_CONSTEXPR auto const t = m1 * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 30,  36,  42), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 60,  66,  72), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 90,  96, 102), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = m1 * 2.5;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 25,  30,  35), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 50,  55,  60), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 75,  80,  85), t[2]);
		}
		// スカラー * matrix3x3 -> matrix3x3
		{
			HAMON_CONSTEXPR auto const t = 4 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 40,  48,  56), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 80,  88,  96), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(120, 128, 136), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = -1.5 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-15, -18, -21), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-30, -33, -36), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-45, -48, -51), t[2]);
		}
	}
	{
		HAMON_CONSTEXPR matrix3x3i const m1
		{
			vector3{10, 12, 14},
			vector3{20, 22, 24},
			vector3{30, 32, 34},
		};
		{
			HAMON_CONSTEXPR auto const t = m1 * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 30,  36,  42), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 60,  66,  72), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 90,  96, 102), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = m1 * 2.5;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 25,  30,  35), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 50,  55,  60), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 75,  80,  85), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = 4 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 40,  48,  56), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 80,  88,  96), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(120, 128, 136), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = -1.5 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-15, -18, -21), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-30, -33, -36), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-45, -48, -51), t[2]);
		}
	}

	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			vector4{10, 12, 14, 16},
			vector4{20, 22, 24, 26},
			vector4{30, 32, 34, 36},
		};
		// matrix3x4 * スカラー -> matrix3x4
		{
			HAMON_CONSTEXPR auto const t = m1 * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 30,  36,  42,  48), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 60,  66,  72,  78), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 90,  96, 102, 108), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = m1 * 2.5;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 25,  30,  35,  40), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 50,  55,  60,  65), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 75,  80,  85,  90), t[2]);
		}
		// スカラー * matrix3x4 -> matrix3x4
		{
			HAMON_CONSTEXPR auto const t = 4 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 40,  48,  56,  64), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 80,  88,  96, 104), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(120, 128, 136, 144), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = -1.5 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-15, -18, -21, -24), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-30, -33, -36, -39), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-45, -48, -51, -54), t[2]);
		}
	}
	{
		HAMON_CONSTEXPR matrix3x4i const m1
		{
			vector4{10, 12, 14, 16},
			vector4{20, 22, 24, 26},
			vector4{30, 32, 34, 36},
		};
		{
			HAMON_CONSTEXPR auto const t = m1 * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 30,  36,  42,  48), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 60,  66,  72,  78), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 90,  96, 102, 108), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = m1 * 2.5;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 25,  30,  35,  40), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 50,  55,  60,  65), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 75,  80,  85,  90), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = 4 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 40,  48,  56,  64), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 80,  88,  96, 104), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(120, 128, 136, 144), t[2]);
		}
		{
			HAMON_CONSTEXPR auto const t = -1.5 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-15, -18, -21, -24), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-30, -33, -36, -39), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-45, -48, -51, -54), t[2]);
		}
	}

	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			vector3{10, 12, 14},
			vector3{20, 22, 24},
			vector3{30, 32, 34},
			vector3{40, 42, 44},
		};
		// matrix4x3 * スカラー -> matrix4x3
		{
			HAMON_CONSTEXPR auto const t = m1 * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 30,  36,  42), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 60,  66,  72), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 90,  96, 102), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(120, 126, 132), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = m1 * 2.5;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 25,  30,  35), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 50,  55,  60), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 75,  80,  85), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(100, 105, 110), t[3]);
		}
		// スカラー * matrix4x3 -> matrix4x3
		{
			HAMON_CONSTEXPR auto const t = 4 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 40,  48,  56), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 80,  88,  96), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(120, 128, 136), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(160, 168, 176), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = -1.5 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-15, -18, -21), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-30, -33, -36), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-45, -48, -51), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-60, -63, -66), t[3]);
		}
	}
	{
		HAMON_CONSTEXPR matrix4x3i const m1
		{
			vector3{10, 12, 14},
			vector3{20, 22, 24},
			vector3{30, 32, 34},
			vector3{40, 42, 44},
		};
		{
			HAMON_CONSTEXPR auto const t = m1 * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 30,  36,  42), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 60,  66,  72), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 90,  96, 102), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(120, 126, 132), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = m1 * 2.5;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 25,  30,  35), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 50,  55,  60), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 75,  80,  85), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(100, 105, 110), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = 4 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 40,  48,  56), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 80,  88,  96), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(120, 128, 136), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(160, 168, 176), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = -1.5 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-15, -18, -21), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-30, -33, -36), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-45, -48, -51), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-60, -63, -66), t[3]);
		}
	}

	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			vector4{10, 12, 14, 16},
			vector4{20, 22, 24, 26},
			vector4{30, 32, 34, 36},
			vector4{40, 42, 44, 46},
		};
		// matrix4x4 * スカラー -> matrix4x4
		{
			HAMON_CONSTEXPR auto const t = m1 * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 30,  36,  42,  48), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 60,  66,  72,  78), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 90,  96, 102, 108), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(120, 126, 132, 138), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = m1 * 2.5;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 25,  30,  35,  40), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 50,  55,  60,  65), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 75,  80,  85,  90), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(100, 105, 110, 115), t[3]);
		}
		// スカラー * matrix4x4 -> matrix4x4
		{
			HAMON_CONSTEXPR auto const t = 4 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 40,  48,  56,  64), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 80,  88,  96, 104), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(120, 128, 136, 144), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(160, 168, 176, 184), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = -1.5 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-15, -18, -21, -24), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-30, -33, -36, -39), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-45, -48, -51, -54), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-60, -63, -66, -69), t[3]);
		}
	}
	{
		HAMON_CONSTEXPR matrix4x4i const m1
		{
			vector4{10, 12, 14, 16},
			vector4{20, 22, 24, 26},
			vector4{30, 32, 34, 36},
			vector4{40, 42, 44, 46},
		};
		{
			HAMON_CONSTEXPR auto const t = m1 * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 30,  36,  42,  48), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 60,  66,  72,  78), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 90,  96, 102, 108), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(120, 126, 132, 138), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = m1 * 2.5;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 25,  30,  35,  40), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 50,  55,  60,  65), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 75,  80,  85,  90), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(100, 105, 110, 115), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = 4 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 40,  48,  56,  64), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 80,  88,  96, 104), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(120, 128, 136, 144), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(160, 168, 176, 184), t[3]);
		}
		{
			HAMON_CONSTEXPR auto const t = -1.5 * m1;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-15, -18, -21, -24), t[0]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-30, -33, -36, -39), t[1]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-45, -48, -51, -54), t[2]);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-60, -63, -66, -69), t[3]);
		}
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x3MulScalarTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x4MulScalarTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x3MulScalarTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x4MulScalarTest<T>());
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
