/**
 *	@file	unit_test_qvm_matrix_plus.cpp
 *
 *	@brief	operator+のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace matrix_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x3PlusTest()
{
	using matrix3x3  = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;
	using matrix3x3f = hamon::qvm::matrix<float, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(std::is_same<decltype(std::declval<matrix3x3&>()  += matrix3x3{}),  matrix3x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3&>()  += matrix3x3i{}), matrix3x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3&>()  += matrix3x3f{}), matrix3x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3i&>() += matrix3x3{}),  matrix3x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3i&>() += matrix3x3i{}), matrix3x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3i&>() += matrix3x3f{}), matrix3x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3f&>() += matrix3x3{}),  matrix3x3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3f&>() += matrix3x3i{}), matrix3x3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x3f&>() += matrix3x3f{}), matrix3x3f&>::value, "");

	// matrix3x3 += matrix3x3
	{
		matrix3x3 m;

		auto t1 = (m += matrix3x3(
			vector3{ 0, -1,  2},
			vector3{ 4,  5, -6},
			vector3{-8,  9, 10}
		));
		static_assert(std::is_same<decltype(t1), matrix3x3>::value, "");
		VERIFY(t1[0] == vector3( 0, -1,  2));
		VERIFY(t1[1] == vector3( 4,  5, -6));
		VERIFY(t1[2] == vector3(-8,  9, 10));
		VERIFY(t1 == m);

		auto t2 = (m += matrix3x3i(
			vector3{10, 11, 12},
			vector3{10, 11, 12},
			vector3{10, 11, 12}
		));
		static_assert(std::is_same<decltype(t2), matrix3x3>::value, "");
		VERIFY(t2[0] == vector3(10, 10, 14));
		VERIFY(t2[1] == vector3(14, 16,  6));
		VERIFY(t2[2] == vector3( 2, 20, 22));
		VERIFY(t2 == m);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x4PlusTest()
{
	using matrix3x4  = hamon::qvm::matrix<T, 3, 4>;
	using matrix3x4i = hamon::qvm::matrix<int, 3, 4>;
	using matrix3x4f = hamon::qvm::matrix<float, 3, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(std::is_same<decltype(std::declval<matrix3x4&>()  += matrix3x4{}),  matrix3x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4&>()  += matrix3x4i{}), matrix3x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4&>()  += matrix3x4f{}), matrix3x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4i&>() += matrix3x4{}),  matrix3x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4i&>() += matrix3x4i{}), matrix3x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4i&>() += matrix3x4f{}), matrix3x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4f&>() += matrix3x4{}),  matrix3x4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4f&>() += matrix3x4i{}), matrix3x4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix3x4f&>() += matrix3x4f{}), matrix3x4f&>::value, "");

	// matrix3x4 += matrix3x4
	{
		matrix3x4 m;

		auto t1 = (m += matrix3x4(
			vector4{ 0, -1,  2, -3},
			vector4{ 4,  5, -6, -7},
			vector4{-8,  9, 10, 11}
		));
		static_assert(std::is_same<decltype(t1), matrix3x4>::value, "");
		VERIFY(t1[0] == vector4( 0, -1,  2, -3));
		VERIFY(t1[1] == vector4( 4,  5, -6, -7));
		VERIFY(t1[2] == vector4(-8,  9, 10, 11));
		VERIFY(t1 == m);

		auto t2 = (m += matrix3x4i(
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13}
		));
		static_assert(std::is_same<decltype(t2), matrix3x4>::value, "");
		VERIFY(t2[0] == vector4(10, 10, 14, 10));
		VERIFY(t2[1] == vector4(14, 16,  6,  6));
		VERIFY(t2[2] == vector4( 2, 20, 22, 24));
		VERIFY(t2 == m);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x3PlusTest()
{
	using matrix4x3  = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x3i = hamon::qvm::matrix<int, 4, 3>;
	using matrix4x3f = hamon::qvm::matrix<float, 4, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(std::is_same<decltype(std::declval<matrix4x3&>()  += matrix4x3{}),  matrix4x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3&>()  += matrix4x3i{}), matrix4x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3&>()  += matrix4x3f{}), matrix4x3&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3i&>() += matrix4x3{}),  matrix4x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3i&>() += matrix4x3i{}), matrix4x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3i&>() += matrix4x3f{}), matrix4x3i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3f&>() += matrix4x3{}),  matrix4x3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3f&>() += matrix4x3i{}), matrix4x3f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x3f&>() += matrix4x3f{}), matrix4x3f&>::value, "");

	// matrix4x3 += matrix4x3
	{
		matrix4x3 m;

		auto t1 = (m += matrix4x3(
			vector3{ 0, -1,  2},
			vector3{ 4,  5, -6},
			vector3{-8,  9, 10},
			vector3{12, 13, 14}
		));
		static_assert(std::is_same<decltype(t1), matrix4x3>::value, "");
		VERIFY(t1[0] == vector3( 0, -1,  2));
		VERIFY(t1[1] == vector3( 4,  5, -6));
		VERIFY(t1[2] == vector3(-8,  9, 10));
		VERIFY(t1[3] == vector3(12, 13, 14));
		VERIFY(t1 == m);

		auto t2 = (m += matrix4x3i(
			vector3{10, 11, 12},
			vector3{10, 11, 12},
			vector3{10, 11, 12},
			vector3{10, 11, 12}
		));
		static_assert(std::is_same<decltype(t2), matrix4x3>::value, "");
		VERIFY(t2[0] == vector3(10, 10, 14));
		VERIFY(t2[1] == vector3(14, 16,  6));
		VERIFY(t2[2] == vector3( 2, 20, 22));
		VERIFY(t2[3] == vector3(22, 24, 26));
		VERIFY(t2 == m);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x4PlusTest()
{
	using matrix4x4  = hamon::qvm::matrix<T, 4, 4>;
	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;
	using matrix4x4f = hamon::qvm::matrix<float, 4, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(std::is_same<decltype(std::declval<matrix4x4&>()  += matrix4x4{}),  matrix4x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4&>()  += matrix4x4i{}), matrix4x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4&>()  += matrix4x4f{}), matrix4x4&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4i&>() += matrix4x4{}),  matrix4x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4i&>() += matrix4x4i{}), matrix4x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4i&>() += matrix4x4f{}), matrix4x4i&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4f&>() += matrix4x4{}),  matrix4x4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4f&>() += matrix4x4i{}), matrix4x4f&>::value, "");
	static_assert(std::is_same<decltype(std::declval<matrix4x4f&>() += matrix4x4f{}), matrix4x4f&>::value, "");

	// matrix4x4 += matrix4x4
	{
		matrix4x4 m;

		auto t1 = (m += matrix4x4(
			vector4{ 0, -1,  2, -3},
			vector4{ 4,  5, -6, -7},
			vector4{-8,  9, 10, 11},
			vector4{12, 13, 14, 15}
		));
		static_assert(std::is_same<decltype(t1), matrix4x4>::value, "");
		VERIFY(t1[0] == vector4( 0, -1,  2, -3));
		VERIFY(t1[1] == vector4( 4,  5, -6, -7));
		VERIFY(t1[2] == vector4(-8,  9, 10, 11));
		VERIFY(t1[3] == vector4(12, 13, 14, 15));
		VERIFY(t1 == m);

		auto t2 = (m += matrix4x4i(
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13},
			vector4{10, 11, 12, 13}
		));
		static_assert(std::is_same<decltype(t2), matrix4x4>::value, "");
		VERIFY(t2[0] == vector4(10, 10, 14, 10));
		VERIFY(t2[1] == vector4(14, 16,  6,  6));
		VERIFY(t2[2] == vector4( 2, 20, 22, 24));
		VERIFY(t2[3] == vector4(22, 24, 26, 28));
		VERIFY(t2 == m);
	}

	return true;
}

TYPED_TEST(MatrixTest, PlusTest)
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

	static_assert(std::is_same<decltype(matrix3x3{}  + matrix3x3{}),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3{}  + matrix3x3i{}), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3i{} + matrix3x3i{}), matrix3x3i>::value, "");
	static_assert(std::is_same<decltype(matrix3x3i{} + matrix3x3f{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(matrix3x3f{} + matrix3x3i{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(matrix3x3f{} + matrix3x3f{}), matrix3x3f>::value, "");

	static_assert(std::is_same<decltype(matrix3x4{}  + matrix3x4{}),  matrix3x4>::value, "");
	static_assert(std::is_same<decltype(matrix3x4{}  + matrix3x4i{}), matrix3x4>::value, "");
	static_assert(std::is_same<decltype(matrix3x4i{} + matrix3x4i{}), matrix3x4i>::value, "");
	static_assert(std::is_same<decltype(matrix3x4i{} + matrix3x4f{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(matrix3x4f{} + matrix3x4i{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(matrix3x4f{} + matrix3x4f{}), matrix3x4f>::value, "");

	static_assert(std::is_same<decltype(matrix4x3{}  + matrix4x3{}),  matrix4x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x3{}  + matrix4x3i{}), matrix4x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x3i{} + matrix4x3i{}), matrix4x3i>::value, "");
	static_assert(std::is_same<decltype(matrix4x3i{} + matrix4x3f{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(matrix4x3f{} + matrix4x3i{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(matrix4x3f{} + matrix4x3f{}), matrix4x3f>::value, "");

	static_assert(std::is_same<decltype(matrix4x4{}  + matrix4x4{}),  matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4{}  + matrix4x4i{}), matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4i{} + matrix4x4i{}), matrix4x4i>::value, "");
	static_assert(std::is_same<decltype(matrix4x4i{} + matrix4x4f{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(matrix4x4f{} + matrix4x4i{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(matrix4x4f{} + matrix4x4f{}), matrix4x4f>::value, "");

	// matrix3x3 + matrix3x3 -> matrix3x3
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			vector3{-21,  22,  23},
			vector3{ 24, -25,  26},
			vector3{ 27,  28, -29},
		};
		HAMON_CONSTEXPR matrix3x3 const m2
		{
			vector3{ 31,  32, -33},
			vector3{ 34, -35,  36},
			vector3{-37,  38,  39},
		};
		HAMON_CONSTEXPR auto const m3 = m1 + m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector3( 10,  54, -10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector3( 58, -60,  62));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector3(-10,  66,  10));
	}
	{
		HAMON_CONSTEXPR matrix3x3i const m1
		{
			vector3{-21,  22,  23},
			vector3{ 24, -25,  26},
			vector3{ 27,  28, -29},
		};
		HAMON_CONSTEXPR matrix3x3 const m2
		{
			vector3{ 31,  32, -33},
			vector3{ 34, -35,  36},
			vector3{-37,  38,  39},
		};
		HAMON_CONSTEXPR auto const m3 = m1 + m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector3( 10,  54, -10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector3( 58, -60,  62));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector3(-10,  66,  10));
	}

	// matrix3x4 + matrix3x4 -> matrix3x4
	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			vector4{-21,  22,  23,  30},
			vector4{ 24, -25,  26,  31},
			vector4{ 27,  28, -29,  32},
		};
		HAMON_CONSTEXPR matrix3x4 const m2
		{
			vector4{ 31,  32, -33,  40},
			vector4{ 34, -35,  36, -41},
			vector4{-37,  38,  39,  42},
		};
		HAMON_CONSTEXPR auto const m3 = m1 + m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector4( 10,  54, -10,  70));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector4( 58, -60,  62, -10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector4(-10,  66,  10,  74));
	}
	{
		HAMON_CONSTEXPR matrix3x4i const m1
		{
			vector4{-21,  22,  23,  30},
			vector4{ 24, -25,  26,  31},
			vector4{ 27,  28, -29,  32},
		};
		HAMON_CONSTEXPR matrix3x4 const m2
		{
			vector4{ 31,  32, -33,  40},
			vector4{ 34, -35,  36, -41},
			vector4{-37,  38,  39,  42},
		};
		HAMON_CONSTEXPR auto const m3 = m1 + m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector4( 10,  54, -10,  70));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector4( 58, -60,  62, -10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector4(-10,  66,  10,  74));
	}

	// matrix4x3 + matrix4x3 -> matrix4x3
	{
		HAMON_CONSTEXPR matrix4x3 const m1
		{
			vector3{-21,  22,  23},
			vector3{ 24, -25,  26},
			vector3{ 27,  28, -29},
			vector3{-33,  34,  35},
		};
		HAMON_CONSTEXPR matrix4x3 const m2
		{
			vector3{ 31,  32, -33},
			vector3{ 34, -35,  36},
			vector3{-37,  38,  39},
			vector3{-43,  44, -45},
		};
		HAMON_CONSTEXPR auto const m3 = m1 + m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector3( 10,  54, -10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector3( 58, -60,  62));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector3(-10,  66,  10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[3], vector3(-76,  78, -10));
	}
	{
		HAMON_CONSTEXPR matrix4x3i const m1
		{
			vector3{-21,  22,  23},
			vector3{ 24, -25,  26},
			vector3{ 27,  28, -29},
			vector3{-33,  34,  35},
		};
		HAMON_CONSTEXPR matrix4x3 const m2
		{
			vector3{ 31,  32, -33},
			vector3{ 34, -35,  36},
			vector3{-37,  38,  39},
			vector3{-43,  44, -45},
		};
		HAMON_CONSTEXPR auto const m3 = m1 + m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector3( 10,  54, -10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector3( 58, -60,  62));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector3(-10,  66,  10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[3], vector3(-76,  78, -10));
	}

	// matrix4x4 + matrix4x4 -> matrix4x4
	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			vector4{-21,  22,  23,  30},
			vector4{ 24, -25,  26,  31},
			vector4{ 27,  28, -29,  32},
			vector4{-33,  34,  35, -36},
		};
		HAMON_CONSTEXPR matrix4x4 const m2
		{
			vector4{ 31,  32, -33,  40},
			vector4{ 34, -35,  36, -41},
			vector4{-37,  38,  39,  42},
			vector4{-43,  44, -45,  46},
		};
		HAMON_CONSTEXPR auto const m3 = m1 + m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector4( 10,  54, -10,  70));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector4( 58, -60,  62, -10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector4(-10,  66,  10,  74));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[3], vector4(-76,  78, -10,  10));
	}
	{
		HAMON_CONSTEXPR matrix4x4i const m1
		{
			vector4{-21,  22,  23,  30},
			vector4{ 24, -25,  26,  31},
			vector4{ 27,  28, -29,  32},
			vector4{-33,  34,  35, -36},
		};
		HAMON_CONSTEXPR matrix4x4 const m2
		{
			vector4{ 31,  32, -33,  40},
			vector4{ 34, -35,  36, -41},
			vector4{-37,  38,  39,  42},
			vector4{-43,  44, -45,  46},
		};
		HAMON_CONSTEXPR auto const m3 = m1 + m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[0], vector4( 10,  54, -10,  70));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[1], vector4( 58, -60,  62, -10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[2], vector4(-10,  66,  10,  74));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m3[3], vector4(-76,  78, -10,  10));
	}

#if (defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 110000))
	// gcc11 でcompiler internal errorになるのを回避
	EXPECT_TRUE(Matrix3x3PlusTest<T>());
	EXPECT_TRUE(Matrix3x4PlusTest<T>());
	EXPECT_TRUE(Matrix4x3PlusTest<T>());
	EXPECT_TRUE(Matrix4x4PlusTest<T>());
#else
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x3PlusTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x4PlusTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x3PlusTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x4PlusTest<T>());
#endif
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
