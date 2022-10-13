/**
 *	@file	unit_test_qvm_matrix_multiplies.cpp
 *
 *	@brief	operator*のテスト
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
inline HAMON_CXX14_CONSTEXPR bool Matrix3x3MultipliesTest()
{
	using matrix3x3  = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	// matrix3x3 *= matrix3x3
	{
		matrix3x3 m
		{
			vector3{  2,  4,  6 },
			vector3{ 10, 12, 14 },
			vector3{ 18, 20, 22 },
		};

		matrix3x3 const m1
		{
			vector3{  11, -12,  13 },
			vector3{  21,  22, -23 },
			vector3{ -31,  32,  33 },
		};

		auto t = (m *= m1);
		static_assert(std::is_same<decltype(t), matrix3x3>::value, "");
		VERIFY(vector3(-80, 256, 132) == m[0]);
		VERIFY(vector3(-72, 592, 316) == m[1]);
		VERIFY(vector3(-64, 928, 500) == m[2]);
		VERIFY(t == m);
	}
	{
		matrix3x3i m
		{
			vector3{  2,  4,  6 },
			vector3{ 10, 12, 14 },
			vector3{ 18, 20, 22 },
		};

		matrix3x3 const m1
		{
			vector3{  11, -12,  13 },
			vector3{  21,  22, -23 },
			vector3{ -31,  32,  33 },
		};

		auto t = (m *= m1);
		static_assert(std::is_same<decltype(t), matrix3x3i>::value, "");
		VERIFY(vector3(-80, 256, 132) == m[0]);
		VERIFY(vector3(-72, 592, 316) == m[1]);
		VERIFY(vector3(-64, 928, 500) == m[2]);
		VERIFY(t == m);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x4MultipliesTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix3x4i = hamon::qvm::matrix<int, 3, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	// matrix3x4 *= matrix4x4
	{
		matrix3x4 m
		{
			vector4{  2,  4,  6,  8 },
			vector4{ 10, 12, 14, 16 },
			vector4{ 18, 20, 22, 24 },
		};

		matrix4x4 const m1
		{
			vector4{  11, -12,  13,  14 },
			vector4{  21,  22, -23,  24 },
			vector4{ -31,  32,  33,  34 },
			vector4{  41,  42,  43, -44 },
		};

		auto t = (m *= m1);
		static_assert(std::is_same<decltype(t), matrix3x4>::value, "");
		VERIFY(vector4(248,  592,  476, -24) == m[0]);
		VERIFY(vector4(584, 1264, 1004, 200) == m[1]);
		VERIFY(vector4(920, 1936, 1532, 424) == m[2]);
		VERIFY(t == m);
	}
	{
		matrix3x4i m
		{
			vector4{  2,  4,  6,  8 },
			vector4{ 10, 12, 14, 16 },
			vector4{ 18, 20, 22, 24 },
		};

		matrix4x4 const m1
		{
			vector4{  11, -12,  13,  14 },
			vector4{  21,  22, -23,  24 },
			vector4{ -31,  32,  33,  34 },
			vector4{  41,  42,  43, -44 },
		};

		auto t = (m *= m1);
		static_assert(std::is_same<decltype(t), matrix3x4i>::value, "");
		VERIFY(vector4(248,  592,  476, -24) == m[0]);
		VERIFY(vector4(584, 1264, 1004, 200) == m[1]);
		VERIFY(vector4(920, 1936, 1532, 424) == m[2]);
		VERIFY(t == m);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x3MultipliesTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x3i = hamon::qvm::matrix<int, 4, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	// matrix4x3 *= matrix3x3
	{
		matrix4x3 m1
		{
			vector3{  2,  4,  6 },
			vector3{ 10, 12, 14 },
			vector3{ 18, 20, 22 },
			vector3{ 26, 28, 30 },
		};

		matrix3x3 const m2
		{
			vector3{  11, -12,  13 },
			vector3{  21,  22, -23 },
			vector3{ -31,  32,  33 },
		};

		auto t = (m1 *= m2);
		static_assert(std::is_same<decltype(t), matrix4x3>::value, "");
		VERIFY(vector3( -80,  256, 132) == m1[0]);
		VERIFY(vector3( -72,  592, 316) == m1[1]);
		VERIFY(vector3( -64,  928, 500) == m1[2]);
		VERIFY(vector3( -56, 1264, 684) == m1[3]);
		VERIFY(t == m1);
	}
	{
		matrix4x3i m1
		{
			vector3{  2,  4,  6 },
			vector3{ 10, 12, 14 },
			vector3{ 18, 20, 22 },
			vector3{ 26, 28, 30 },
		};

		matrix3x3 const m2
		{
			vector3{  11, -12,  13 },
			vector3{  21,  22, -23 },
			vector3{ -31,  32,  33 },
		};

		auto t = (m1 *= m2);
		static_assert(std::is_same<decltype(t), matrix4x3i>::value, "");
		VERIFY(vector3( -80,  256, 132) == m1[0]);
		VERIFY(vector3( -72,  592, 316) == m1[1]);
		VERIFY(vector3( -64,  928, 500) == m1[2]);
		VERIFY(vector3( -56, 1264, 684) == m1[3]);
		VERIFY(t == m1);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x4MultipliesTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	// matrix4x4 *= matrix4x4
	{
		matrix4x4 m
		{
			vector4{  2,  4,  6,  8 },
			vector4{ 10, 12, 14, 16 },
			vector4{ 18, 20, 22, 24 },
			vector4{ 26, 28, 30, 32 },
		};

		matrix4x4 const m1
		{
			vector4{  11, -12,  13,  14 },
			vector4{  21,  22, -23,  24 },
			vector4{ -31,  32,  33,  34 },
			vector4{  41,  42,  43, -44 },
		};

		auto t = (m *= m1);
		static_assert(std::is_same<decltype(t), matrix4x4>::value, "");
		VERIFY(vector4( 248,  592,  476, -24) == m[0]);
		VERIFY(vector4( 584, 1264, 1004, 200) == m[1]);
		VERIFY(vector4( 920, 1936, 1532, 424) == m[2]);
		VERIFY(vector4(1256, 2608, 2060, 648) == m[3]);
		VERIFY(t == m);
	}
	{
		matrix4x4i m
		{
			vector4{  2,  4,  6,  8 },
			vector4{ 10, 12, 14, 16 },
			vector4{ 18, 20, 22, 24 },
			vector4{ 26, 28, 30, 32 },
		};

		matrix4x4 const m1
		{
			vector4{  11, -12,  13,  14 },
			vector4{  21,  22, -23,  24 },
			vector4{ -31,  32,  33,  34 },
			vector4{  41,  42,  43, -44 },
		};

		auto t = (m *= m1);
		static_assert(std::is_same<decltype(t), matrix4x4i>::value, "");
		VERIFY(vector4( 248,  592,  476, -24) == m[0]);
		VERIFY(vector4( 584, 1264, 1004, 200) == m[1]);
		VERIFY(vector4( 920, 1936, 1532, 424) == m[2]);
		VERIFY(vector4(1256, 2608, 2060, 648) == m[3]);
		VERIFY(t == m);
	}

	return true;
}

TYPED_TEST(MatrixTest, MultipliesTest)
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

	static_assert(std::is_same<decltype(matrix3x3{}  * matrix3x3{}),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3{}  * matrix3x3i{}), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x3i{} * matrix3x3i{}), matrix3x3i>::value, "");
	static_assert(std::is_same<decltype(matrix3x3i{} * matrix3x3f{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(matrix3x3f{} * matrix3x3i{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(matrix3x3f{} * matrix3x3f{}), matrix3x3f>::value, "");

	static_assert(std::is_same<decltype(matrix3x3{}  * matrix3x4{}),  matrix3x4>::value, "");
	static_assert(std::is_same<decltype(matrix3x3{}  * matrix3x4i{}), matrix3x4>::value, "");
	static_assert(std::is_same<decltype(matrix3x3i{} * matrix3x4i{}), matrix3x4i>::value, "");
	static_assert(std::is_same<decltype(matrix3x3i{} * matrix3x4f{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(matrix3x3f{} * matrix3x4i{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(matrix3x3f{} * matrix3x4f{}), matrix3x4f>::value, "");

	static_assert(std::is_same<decltype(matrix3x4{}  * matrix4x3{}),  matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x4{}  * matrix4x3i{}), matrix3x3>::value, "");
	static_assert(std::is_same<decltype(matrix3x4i{} * matrix4x3i{}), matrix3x3i>::value, "");
	static_assert(std::is_same<decltype(matrix3x4i{} * matrix4x3f{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(matrix3x4f{} * matrix4x3i{}), matrix3x3f>::value, "");
	static_assert(std::is_same<decltype(matrix3x4f{} * matrix4x3f{}), matrix3x3f>::value, "");

	static_assert(std::is_same<decltype(matrix3x4{}  * matrix4x4{}),  matrix3x4>::value, "");
	static_assert(std::is_same<decltype(matrix3x4{}  * matrix4x4i{}), matrix3x4>::value, "");
	static_assert(std::is_same<decltype(matrix3x4i{} * matrix4x4i{}), matrix3x4i>::value, "");
	static_assert(std::is_same<decltype(matrix3x4i{} * matrix4x4f{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(matrix3x4f{} * matrix4x4i{}), matrix3x4f>::value, "");
	static_assert(std::is_same<decltype(matrix3x4f{} * matrix4x4f{}), matrix3x4f>::value, "");

	static_assert(std::is_same<decltype(matrix4x3{}  * matrix3x3{}),  matrix4x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x3{}  * matrix3x3i{}), matrix4x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x3i{} * matrix3x3i{}), matrix4x3i>::value, "");
	static_assert(std::is_same<decltype(matrix4x3i{} * matrix3x3f{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(matrix4x3f{} * matrix3x3i{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(matrix4x3f{} * matrix3x3f{}), matrix4x3f>::value, "");

	static_assert(std::is_same<decltype(matrix4x3{}  * matrix3x4{}),  matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x3{}  * matrix3x4i{}), matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x3i{} * matrix3x4i{}), matrix4x4i>::value, "");
	static_assert(std::is_same<decltype(matrix4x3i{} * matrix3x4f{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(matrix4x3f{} * matrix3x4i{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(matrix4x3f{} * matrix3x4f{}), matrix4x4f>::value, "");

	static_assert(std::is_same<decltype(matrix4x4{}  * matrix4x3{}),  matrix4x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x4{}  * matrix4x3i{}), matrix4x3>::value, "");
	static_assert(std::is_same<decltype(matrix4x4i{} * matrix4x3i{}), matrix4x3i>::value, "");
	static_assert(std::is_same<decltype(matrix4x4i{} * matrix4x3f{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(matrix4x4f{} * matrix4x3i{}), matrix4x3f>::value, "");
	static_assert(std::is_same<decltype(matrix4x4f{} * matrix4x3f{}), matrix4x3f>::value, "");

	static_assert(std::is_same<decltype(matrix4x4{}  * matrix4x4{}),  matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4{}  * matrix4x4i{}), matrix4x4>::value, "");
	static_assert(std::is_same<decltype(matrix4x4i{} * matrix4x4i{}), matrix4x4i>::value, "");
	static_assert(std::is_same<decltype(matrix4x4i{} * matrix4x4f{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(matrix4x4f{} * matrix4x4i{}), matrix4x4f>::value, "");
	static_assert(std::is_same<decltype(matrix4x4f{} * matrix4x4f{}), matrix4x4f>::value, "");

	// matrix3x3 * matrix3x3 -> matrix3x3
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			vector3{ 15, 3, -7 },
			vector3{ 11, 4, 12 },
			vector3{  2, 6, 13 },
		};
		HAMON_CONSTEXPR matrix3x3 const m2
		{
			vector3{ 1,  2,  3 },
			vector3{ 5,  6,  7 },
			vector3{ 9, 10,-11 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix3x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-33, -22, 143), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(139, 166, -71), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(149, 170, -95), t1[2]);

		HAMON_CONSTEXPR auto const t2 = m2 * m1;
		static_assert(std::is_same<decltype(t2), matrix3x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 43, 29,  56), t2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(155, 81, 128), t2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(223,  1, -86), t2[2]);
	}
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			vector3{ 15, 3, -7 },
			vector3{ 11, 4, 12 },
			vector3{  2, 6, 13 },
		};
		HAMON_CONSTEXPR matrix3x3i const m2
		{
			vector3{ 1,  2,  3 },
			vector3{ 5,  6,  7 },
			vector3{ 9, 10,-11 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix3x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-33, -22, 143), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(139, 166, -71), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(149, 170, -95), t1[2]);

		HAMON_CONSTEXPR auto const t2 = m2 * m1;
		static_assert(std::is_same<decltype(t2), matrix3x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 43, 29,  56), t2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(155, 81, 128), t2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(223,  1, -86), t2[2]);
	}

	// matrix3x3 * matrix3x4 -> matrix3x4
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			vector3{  1,  2,  3 },
			vector3{  5,  6,  7 },
			vector3{  9, 10, 11 },
		};
		HAMON_CONSTEXPR matrix3x4 const m2
		{
			vector4{ 11, 12, 13, 14 },
			vector4{ 21, 22, 23, 24 },
			vector4{ 31, 32, 33, 34 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix3x4 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(146, 152, 158, 164), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(398, 416, 434, 452), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(650, 680, 710, 740), t1[2]);
	}
	{
		HAMON_CONSTEXPR matrix3x3i const m1
		{
			vector3{  1,  2,  3 },
			vector3{  5,  6,  7 },
			vector3{  9, 10, 11 },
		};
		HAMON_CONSTEXPR matrix3x4 const m2
		{
			vector4{ 11, 12, 13, 14 },
			vector4{ 21, 22, 23, 24 },
			vector4{ 31, 32, 33, 34 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix3x4 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(146, 152, 158, 164), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(398, 416, 434, 452), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(650, 680, 710, 740), t1[2]);
	}

	// matrix3x4 * matrix4x4 -> matrix3x4
	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			vector4{ 11, 12, 13, 14 },
			vector4{ 21, 22, 23, 24 },
			vector4{ 31, 32, 33, 34 },
		};
		HAMON_CONSTEXPR matrix4x4 const m2
		{
			vector4{  1,  2,  3,  4 },
			vector4{  5,  6,  7,  8 },
			vector4{  9, 10, 11, 12 },
			vector4{ 13, 14, 15, 16 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix3x4 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 370, 420, 470, 520), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 650, 740, 830, 920), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 930,1060,1190,1320), t1[2]);
	}
	{
		HAMON_CONSTEXPR matrix3x4 const m1
		{
			vector4{ 11, 12, 13, 14 },
			vector4{ 21, 22, 23, 24 },
			vector4{ 31, 32, 33, 34 },
		};
		HAMON_CONSTEXPR matrix4x4i const m2
		{
			vector4{  1,  2,  3,  4 },
			vector4{  5,  6,  7,  8 },
			vector4{  9, 10, 11, 12 },
			vector4{ 13, 14, 15, 16 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix3x4 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 370, 420, 470, 520), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 650, 740, 830, 920), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 930,1060,1190,1320), t1[2]);
	}

	// matrix3x4 * matrix4x3 -> matrix3x3
	// matrix4x3 * matrix3x4 -> matrix4x4
	{
		HAMON_CONSTEXPR matrix3x4 m1
		{
			vector4{  1,  2,  3,  4 },
			vector4{  5,  6,  7,  8 },
			vector4{  9, 10, 11, 12 },
		};
		HAMON_CONSTEXPR matrix4x3 m2
		{
			vector3{ 11, 12, 13 },
			vector3{ 21, 22, 23 },
			vector3{ 31, 32, 33 },
			vector3{ 41, 42, 43 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix3x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 310, 320, 330), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 726, 752, 778), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(1142,1184,1226), t1[2]);

		HAMON_CONSTEXPR auto const t2 = m2 * m1;
		static_assert(std::is_same<decltype(t2), matrix4x4 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(188, 224, 260, 296), t2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(338, 404, 470, 536), t2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(488, 584, 680, 776), t2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(638, 764, 890,1016), t2[3]);
	}

	// matrix4x3 * matrix3x3 -> matrix4x3
	{
		HAMON_CONSTEXPR matrix4x3 m1
		{
			vector3{  15,   3,  -7 },
			vector3{  11,   4,  12 },
			vector3{   2,   6,  13 },
			vector3{   1,  14,   9 },
		};
		HAMON_CONSTEXPR matrix3x3 m2
		{
			vector3{   1,   2,   3 },
			vector3{   5,   6,   7 },
			vector3{   9,  10, -11 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix4x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( -33, -22, 143), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 139, 166, -71), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 149, 170, -95), t1[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 152, 176,   2), t1[3]);
	}
	{
		HAMON_CONSTEXPR matrix4x3i m1
		{
			vector3{  15,   3,  -7 },
			vector3{  11,   4,  12 },
			vector3{   2,   6,  13 },
			vector3{   1,  14,   9 },
		};
		HAMON_CONSTEXPR matrix3x3 m2
		{
			vector3{   1,   2,   3 },
			vector3{   5,   6,   7 },
			vector3{   9,  10, -11 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix4x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( -33, -22, 143), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 139, 166, -71), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 149, 170, -95), t1[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 152, 176,   2), t1[3]);
	}

	// matrix4x4 * matrix4x4 -> matrix4x4
	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			vector4{  15,   3,  -7,   4 },
			vector4{  11,   4,  12,  -8 },
			vector4{   2,   6,  13,  10 },
			vector4{   1,  14,   9,   5 },
		};
		HAMON_CONSTEXPR matrix4x4 const m2
		{
			vector4{   1,   2,   3,   4 },
			vector4{   5,   6,   7,   8 },
			vector4{   9,  10, -11, -12 },
			vector4{  13, -14,  15,  16 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  19,  -78,  203,  232), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  35,  278, -191, -196), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 279,   30,   55,   60), t1[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 217,  106,   77,   88), t1[3]);

		HAMON_CONSTEXPR auto const t2 = m2 * m1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  47,   85,   92,   38), t2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 163,  193,  200,   82), t2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 211, -167, -194, -214), t2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  87,  297,   80,  394), t2[3]);
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			vector4{  15,   3,  -7,   4 },
			vector4{  11,   4,  12,  -8 },
			vector4{   2,   6,  13,  10 },
			vector4{   1,  14,   9,   5 },
		};
		HAMON_CONSTEXPR matrix4x4i const m2
		{
			vector4{   1,   2,   3,   4 },
			vector4{   5,   6,   7,   8 },
			vector4{   9,  10, -11, -12 },
			vector4{  13, -14,  15,  16 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  19,  -78,  203,  232), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  35,  278, -191, -196), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 279,   30,   55,   60), t1[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 217,  106,   77,   88), t1[3]);

		HAMON_CONSTEXPR auto const t2 = m2 * m1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  47,   85,   92,   38), t2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 163,  193,  200,   82), t2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 211, -167, -194, -214), t2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  87,  297,   80,  394), t2[3]);
	}
	{
		HAMON_CONSTEXPR matrix4x4i const m1
		{
			vector4{  15,   3,  -7,   4 },
			vector4{  11,   4,  12,  -8 },
			vector4{   2,   6,  13,  10 },
			vector4{   1,  14,   9,   5 },
		};
		HAMON_CONSTEXPR matrix4x4i const m2
		{
			vector4{   1,   2,   3,   4 },
			vector4{   5,   6,   7,   8 },
			vector4{   9,  10, -11, -12 },
			vector4{  13, -14,  15,  16 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  19,  -78,  203,  232), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  35,  278, -191, -196), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 279,   30,   55,   60), t1[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 217,  106,   77,   88), t1[3]);

		HAMON_CONSTEXPR auto const t2 = m2 * m1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  47,   85,   92,   38), t2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 163,  193,  200,   82), t2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 211, -167, -194, -214), t2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  87,  297,   80,  394), t2[3]);
	}

	// matrix4x4 * matrix4x3 -> matrix4x3
	{
		HAMON_CONSTEXPR matrix4x4i const m1
		{
			vector4{  1,  2,  3,  4 },
			vector4{  5,  6,  7,  8 },
			vector4{  9, 10, 11, 12 },
			vector4{ 13, 14, 15, 16 },
		};
		HAMON_CONSTEXPR matrix4x3 const m2
		{
			vector3{ 11, 12, 13 },
			vector3{ 21, 22, 23 },
			vector3{ 31, 32, 33 },
			vector3{ 41, 42, 43 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix4x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 310, 320, 330), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 726, 752, 778), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(1142,1184,1226), t1[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(1558,1616,1674), t1[3]);
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m1
		{
			vector4{  1,  2,  3,  4 },
			vector4{  5,  6,  7,  8 },
			vector4{  9, 10, 11, 12 },
			vector4{ 13, 14, 15, 16 },
		};
		HAMON_CONSTEXPR matrix4x3i const m2
		{
			vector3{ 11, 12, 13 },
			vector3{ 21, 22, 23 },
			vector3{ 31, 32, 33 },
			vector3{ 41, 42, 43 },
		};

		HAMON_CONSTEXPR auto const t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), matrix4x3 const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 310, 320, 330), t1[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 726, 752, 778), t1[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(1142,1184,1226), t1[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(1558,1616,1674), t1[3]);
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x3MultipliesTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x4MultipliesTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x3MultipliesTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x4MultipliesTest<T>());
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
