/**
 *	@file	unit_test_qvm_matrix_minus.cpp
 *
 *	@brief	operator-のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// gcc11,12,13でinternal compiler errorになるのを回避
#if (defined(HAMON_GCC_VERSION) && (110000 <= HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 140000))
#  define HAMON_QVM_MATRIX_MINUS_CONSTEXPR
#  define HAMON_QVM_MATRIX_MINUS_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#else
#  define HAMON_QVM_MATRIX_MINUS_CONSTEXPR              HAMON_CXX14_CONSTEXPR
#  define HAMON_QVM_MATRIX_MINUS_CONSTEXPR_EXPECT_TRUE  HAMON_CXX14_CONSTEXPR_EXPECT_TRUE
#endif

template <typename T>
inline HAMON_QVM_MATRIX_MINUS_CONSTEXPR bool Matrix3x3MinusTest()
{
	using matrix3x3  = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;
	using matrix3x3f = hamon::qvm::matrix<float, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3&>()  -= matrix3x3{}),  matrix3x3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3&>()  -= matrix3x3i{}), matrix3x3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3&>()  -= matrix3x3f{}), matrix3x3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3i&>() -= matrix3x3{}),  matrix3x3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3i&>() -= matrix3x3i{}), matrix3x3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3i&>() -= matrix3x3f{}), matrix3x3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3f&>() -= matrix3x3{}),  matrix3x3f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3f&>() -= matrix3x3i{}), matrix3x3f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x3f&>() -= matrix3x3f{}), matrix3x3f&>::value, "");

	// matrix3x3 -= matrix3x3
	{
		matrix3x3 m;

		auto t1 = (m -= matrix3x3(
			vector3{ 0, -1,  2},
			vector3{ 4,  5, -6},
			vector3{-8,  9, 10}
		));
		static_assert(hamon::is_same<decltype(t1), matrix3x3>::value, "");
		VERIFY(t1[0] == -vector3( 0, -1,  2));
		VERIFY(t1[1] == -vector3( 4,  5, -6));
		VERIFY(t1[2] == -vector3(-8,  9, 10));
		VERIFY(t1 == m);

		auto t2 = (m -= matrix3x3i(
			vector3{10, 11, 12},
			vector3{10, 11, 12},
			vector3{10, 11, 12}
		));
		static_assert(hamon::is_same<decltype(t2), matrix3x3>::value, "");
		VERIFY(t2[0] == -vector3(10, 10, 14));
		VERIFY(t2[1] == -vector3(14, 16,  6));
		VERIFY(t2[2] == -vector3( 2, 20, 22));
		VERIFY(t2 == m);
	}

	return true;
}

template <typename T>
inline HAMON_QVM_MATRIX_MINUS_CONSTEXPR bool Matrix3x4MinusTest()
{
	using matrix3x4  = hamon::qvm::matrix<T, 3, 4>;
	using matrix3x4i = hamon::qvm::matrix<int, 3, 4>;
	using matrix3x4f = hamon::qvm::matrix<float, 3, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4&>()  -= matrix3x4{}),  matrix3x4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4&>()  -= matrix3x4i{}), matrix3x4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4&>()  -= matrix3x4f{}), matrix3x4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4i&>() -= matrix3x4{}),  matrix3x4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4i&>() -= matrix3x4i{}), matrix3x4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4i&>() -= matrix3x4f{}), matrix3x4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4f&>() -= matrix3x4{}),  matrix3x4f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4f&>() -= matrix3x4i{}), matrix3x4f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix3x4f&>() -= matrix3x4f{}), matrix3x4f&>::value, "");

	// matrix3x4 -= matrix3x4
	{
		matrix3x4 m;

		auto t1 = (m -= matrix3x4(
			vector4{ 0, -1,  2, -3},
			vector4{ 4,  5, -6, -7},
			vector4{-8,  9, 10, 11}
		));
		static_assert(hamon::is_same<decltype(t1), matrix3x4>::value, "");
		VERIFY(t1[0] == -vector4( 0, -1,  2, -3));
		VERIFY(t1[1] == -vector4( 4,  5, -6, -7));
		VERIFY(t1[2] == -vector4(-8,  9, 10, 11));
		VERIFY(t1 == m);

		auto t2 = (m -= matrix3x4i(
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13}
		));
		static_assert(hamon::is_same<decltype(t2), matrix3x4>::value, "");
		VERIFY(t2[0] == -vector4(10, 10, 14, 10));
		VERIFY(t2[1] == -vector4(14, 16,  6,  6));
		VERIFY(t2[2] == -vector4( 2, 20, 22, 24));
		VERIFY(t2 == m);
	}

	return true;
}

template <typename T>
inline HAMON_QVM_MATRIX_MINUS_CONSTEXPR bool Matrix4x3MinusTest()
{
	using matrix4x3  = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x3i = hamon::qvm::matrix<int, 4, 3>;
	using matrix4x3f = hamon::qvm::matrix<float, 4, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3&>()  -= matrix4x3{}),  matrix4x3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3&>()  -= matrix4x3i{}), matrix4x3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3&>()  -= matrix4x3f{}), matrix4x3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3i&>() -= matrix4x3{}),  matrix4x3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3i&>() -= matrix4x3i{}), matrix4x3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3i&>() -= matrix4x3f{}), matrix4x3i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3f&>() -= matrix4x3{}),  matrix4x3f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3f&>() -= matrix4x3i{}), matrix4x3f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x3f&>() -= matrix4x3f{}), matrix4x3f&>::value, "");

	// matrix4x3 -= matrix4x3
	{
		matrix4x3 m;

		auto t1 = (m -= matrix4x3(
			vector3{ 0, -1,  2},
			vector3{ 4,  5, -6},
			vector3{-8,  9, 10},
			vector3{12, 13, 14}
		));
		static_assert(hamon::is_same<decltype(t1), matrix4x3>::value, "");
		VERIFY(t1[0] == -vector3( 0, -1,  2));
		VERIFY(t1[1] == -vector3( 4,  5, -6));
		VERIFY(t1[2] == -vector3(-8,  9, 10));
		VERIFY(t1[3] == -vector3(12, 13, 14));
		VERIFY(t1 == m);

		auto t2 = (m -= matrix4x3i(
			vector3{10, 11, 12},
			vector3{10, 11, 12},
			vector3{10, 11, 12},
			vector3{10, 11, 12}
		));
		static_assert(hamon::is_same<decltype(t2), matrix4x3>::value, "");
		VERIFY(t2[0] == -vector3(10, 10, 14));
		VERIFY(t2[1] == -vector3(14, 16,  6));
		VERIFY(t2[2] == -vector3( 2, 20, 22));
		VERIFY(t2[3] == -vector3(22, 24, 26));
		VERIFY(t2 == m);
	}

	return true;
}

template <typename T>
inline HAMON_QVM_MATRIX_MINUS_CONSTEXPR bool Matrix4x4MinusTest()
{
	using matrix4x4  = hamon::qvm::matrix<T, 4, 4>;
	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;
	using matrix4x4f = hamon::qvm::matrix<float, 4, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4&>()  -= matrix4x4{}),  matrix4x4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4&>()  -= matrix4x4i{}), matrix4x4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4&>()  -= matrix4x4f{}), matrix4x4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4i&>() -= matrix4x4{}),  matrix4x4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4i&>() -= matrix4x4i{}), matrix4x4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4i&>() -= matrix4x4f{}), matrix4x4i&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4f&>() -= matrix4x4{}),  matrix4x4f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4f&>() -= matrix4x4i{}), matrix4x4f&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<matrix4x4f&>() -= matrix4x4f{}), matrix4x4f&>::value, "");

	// matrix4x4 -= matrix4x4
	{
		matrix4x4 m;

		auto t1 = (m -= matrix4x4(
			vector4{ 0, -1,  2, -3},
			vector4{ 4,  5, -6, -7},
			vector4{-8,  9, 10, 11},
			vector4{12, 13, 14, 15}
		));
		static_assert(hamon::is_same<decltype(t1), matrix4x4>::value, "");
		VERIFY(t1[0] == -vector4( 0, -1,  2, -3));
		VERIFY(t1[1] == -vector4( 4,  5, -6, -7));
		VERIFY(t1[2] == -vector4(-8,  9, 10, 11));
		VERIFY(t1[3] == -vector4(12, 13, 14, 15));
		VERIFY(t1 == m);

		auto t2 = (m -= matrix4x4i(
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13}
		));
		static_assert(hamon::is_same<decltype(t2), matrix4x4>::value, "");
		VERIFY(t2[0] == -vector4(10, 10, 14, 10));
		VERIFY(t2[1] == -vector4(14, 16,  6,  6));
		VERIFY(t2[2] == -vector4( 2, 20, 22, 24));
		VERIFY(t2[3] == -vector4(22, 24, 26, 28));
		VERIFY(t2 == m);
	}

	return true;
}

TYPED_TEST(MatrixTest, MinusTest)
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

	static_assert(hamon::is_same<decltype(matrix3x3{}  - matrix3x3{}),  matrix3x3>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x3{}  - matrix3x3i{}), matrix3x3>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x3i{} - matrix3x3i{}), matrix3x3i>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x3i{} - matrix3x3f{}), matrix3x3f>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x3f{} - matrix3x3i{}), matrix3x3f>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x3f{} - matrix3x3f{}), matrix3x3f>::value, "");

	static_assert(hamon::is_same<decltype(matrix3x4{}  - matrix3x4{}),  matrix3x4>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x4{}  - matrix3x4i{}), matrix3x4>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x4i{} - matrix3x4i{}), matrix3x4i>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x4i{} - matrix3x4f{}), matrix3x4f>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x4f{} - matrix3x4i{}), matrix3x4f>::value, "");
	static_assert(hamon::is_same<decltype(matrix3x4f{} - matrix3x4f{}), matrix3x4f>::value, "");

	static_assert(hamon::is_same<decltype(matrix4x3{}  - matrix4x3{}),  matrix4x3>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x3{}  - matrix4x3i{}), matrix4x3>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x3i{} - matrix4x3i{}), matrix4x3i>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x3i{} - matrix4x3f{}), matrix4x3f>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x3f{} - matrix4x3i{}), matrix4x3f>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x3f{} - matrix4x3f{}), matrix4x3f>::value, "");

	static_assert(hamon::is_same<decltype(matrix4x4{}  - matrix4x4{}),  matrix4x4>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x4{}  - matrix4x4i{}), matrix4x4>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x4i{} - matrix4x4i{}), matrix4x4i>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x4i{} - matrix4x4f{}), matrix4x4f>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x4f{} - matrix4x4i{}), matrix4x4f>::value, "");
	static_assert(hamon::is_same<decltype(matrix4x4f{} - matrix4x4f{}), matrix4x4f>::value, "");

	// matrix3x3 - matrix3x3 -> matrix3x3
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			vector3{10, 11, 12},
			vector3{20, 21, 22},
			vector3{30, 31, 32},
		};
		HAMON_CONSTEXPR matrix3x3 const m2
		{
			vector3{0, 9, 1},
			vector3{8, 4, 7},
			vector3{6, 5, 3},
		};
		HAMON_CONSTEXPR auto const m3 = m1 - m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector3(10,  2, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector3(12, 17, 15));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector3(24, 26, 29));
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			vector3{10, 11, 12},
			vector3{20, 21, 22},
			vector3{30, 31, 32},
		};
		HAMON_CONSTEXPR matrix3x3i const m2
		{
			vector3{0, 9, 1},
			vector3{8, 4, 7},
			vector3{6, 5, 3},
		};
		HAMON_CONSTEXPR auto const m3 = m1 - m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector3(10,  2, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector3(12, 17, 15));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector3(24, 26, 29));
	}

	// matrix3x4 - matrix3x4 -> matrix3x4
	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			vector4{10, 11, 12, 13},
			vector4{20, 21, 22, 23},
			vector4{30, 31, 32, 33},
		};
		HAMON_CONSTEXPR matrix3x4 const m2
		{
			vector4{0, 9, 1, 2},
			vector4{8, 4, 7, 9},
			vector4{6, 5, 3, 1},
		};
		HAMON_CONSTEXPR auto const m3 = m1 - m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector4(10,  2, 11, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector4(12, 17, 15, 14));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector4(24, 26, 29, 32));
	}
	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			vector4{10, 11, 12, 13},
			vector4{20, 21, 22, 23},
			vector4{30, 31, 32, 33},
		};
		HAMON_CONSTEXPR matrix3x4i const m2
		{
			vector4{0, 9, 1, 2},
			vector4{8, 4, 7, 9},
			vector4{6, 5, 3, 1},
		};
		HAMON_CONSTEXPR auto const m3 = m1 - m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector4(10,  2, 11, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector4(12, 17, 15, 14));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector4(24, 26, 29, 32));
	}

	// matrix4x3 - matrix4x3 -> matrix4x3
	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			vector3{10, 11, 12},
			vector3{20, 21, 22},
			vector3{30, 31, 32},
			vector3{40, 41, 42},
		};
		HAMON_CONSTEXPR matrix4x3 const m2
		{
			vector3{0, 9, 1},
			vector3{8, 4, 7},
			vector3{6, 5, 3},
			vector3{4, 8, 5},
		};
		HAMON_CONSTEXPR auto const m3 = m1 - m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector3(10,  2, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector3(12, 17, 15));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector3(24, 26, 29));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[3], vector3(36, 33, 37));
	}
	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			vector3{10, 11, 12},
			vector3{20, 21, 22},
			vector3{30, 31, 32},
			vector3{40, 41, 42},
		};
		HAMON_CONSTEXPR matrix4x3i const m2
		{
			vector3{0, 9, 1},
			vector3{8, 4, 7},
			vector3{6, 5, 3},
			vector3{4, 8, 5},
		};
		HAMON_CONSTEXPR auto const m3 = m1 - m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector3(10,  2, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector3(12, 17, 15));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector3(24, 26, 29));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[3], vector3(36, 33, 37));
	}

	// matrix4x4 - matrix4x4 -> matrix4x4
	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			vector4{10, 11, 12, 13},
			vector4{20, 21, 22, 23},
			vector4{30, 31, 32, 33},
			vector4{40, 41, 42, 43},
		};
		HAMON_CONSTEXPR matrix4x4 const m2
		{
			vector4{0, 9, 1, 2},
			vector4{8, 4, 7, 9},
			vector4{6, 5, 3, 1},
			vector4{4, 8, 5, 0},
		};
		HAMON_CONSTEXPR auto const m3 = m1 - m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector4(10,  2, 11, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector4(12, 17, 15, 14));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector4(24, 26, 29, 32));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[3], vector4(36, 33, 37, 43));
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			vector4{10, 11, 12, 13},
			vector4{20, 21, 22, 23},
			vector4{30, 31, 32, 33},
			vector4{40, 41, 42, 43},
		};
		HAMON_CONSTEXPR matrix4x4i const m2
		{
			vector4{0, 9, 1, 2},
			vector4{8, 4, 7, 9},
			vector4{6, 5, 3, 1},
			vector4{4, 8, 5, 0},
		};
		HAMON_CONSTEXPR auto const m3 = m1 - m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector4(10,  2, 11, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector4(12, 17, 15, 14));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector4(24, 26, 29, 32));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[3], vector4(36, 33, 37, 43));
	}

	HAMON_QVM_MATRIX_MINUS_CONSTEXPR_EXPECT_TRUE(Matrix3x3MinusTest<T>());
	HAMON_QVM_MATRIX_MINUS_CONSTEXPR_EXPECT_TRUE(Matrix3x4MinusTest<T>());
	HAMON_QVM_MATRIX_MINUS_CONSTEXPR_EXPECT_TRUE(Matrix4x3MinusTest<T>());
	HAMON_QVM_MATRIX_MINUS_CONSTEXPR_EXPECT_TRUE(Matrix4x4MinusTest<T>());
}

#undef HAMON_QVM_MATRIX_MINUS_CONSTEXPR
#undef HAMON_QVM_MATRIX_MINUS_CONSTEXPR_EXPECT_TRUE

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
