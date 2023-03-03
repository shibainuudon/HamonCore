/**
 *	@file	unit_test_qvm_matrix_bracket.cpp
 *
 *	@brief	operator[]のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x3BracketTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	{
		matrix3x3 m
		{
			0,  1,  2,
			4,  5,  6,
			8,  9, 10,
		};
		static_assert(hamon::is_same<decltype(m[0]), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m[1]), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m[2]), vector3&>::value, "");
		VERIFY(m[0] == vector3( 0,  1,  2));
		VERIFY(m[1] == vector3( 4,  5,  6));
		VERIFY(m[2] == vector3( 8,  9, 10));

		m[0] = vector3(21,22,23);

		VERIFY(m[0] == vector3(21, 22, 23));
		VERIFY(m[1] == vector3( 4,  5,  6));
		VERIFY(m[2] == vector3( 8,  9, 10));
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x4BracketTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		matrix3x4 m
		{
			0,  1,  2,  3,
			4,  5,  6,  7,
			8,  9, 10, 11,
		};
		static_assert(hamon::is_same<decltype(m[0]), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m[1]), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m[2]), vector4&>::value, "");
		VERIFY(m[0] == vector4( 0,  1,  2,  3));
		VERIFY(m[1] == vector4( 4,  5,  6,  7));
		VERIFY(m[2] == vector4( 8,  9, 10, 11));

		m[0] = vector4(21,22,23,24);

		VERIFY(m[0] == vector4(21, 22, 23, 24));
		VERIFY(m[1] == vector4( 4,  5,  6,  7));
		VERIFY(m[2] == vector4( 8,  9, 10, 11));
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x3BracketTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	{
		matrix4x3 m
		{
			 0,  1,  2,
			 4,  5,  6,
			 8,  9, 10,
			12, 13, 14,
		};
		static_assert(hamon::is_same<decltype(m[0]), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m[1]), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m[2]), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m[3]), vector3&>::value, "");
		VERIFY(m[0] == vector3( 0,  1,  2));
		VERIFY(m[1] == vector3( 4,  5,  6));
		VERIFY(m[2] == vector3( 8,  9, 10));
		VERIFY(m[3] == vector3(12, 13, 14));

		m[0] = vector3(21,22,23);
		m[3] = vector3(31,32,33);

		VERIFY(m[0] == vector3(21, 22, 23));
		VERIFY(m[1] == vector3( 4,  5,  6));
		VERIFY(m[2] == vector3( 8,  9, 10));
		VERIFY(m[3] == vector3(31, 32, 33));
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x4BracketTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		matrix4x4 m
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
			12, 13, 14, 15,
		};
		static_assert(hamon::is_same<decltype(m[0]), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m[1]), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m[2]), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m[3]), vector4&>::value, "");
		VERIFY(m[0] == vector4( 0,  1,  2,  3));
		VERIFY(m[1] == vector4( 4,  5,  6,  7));
		VERIFY(m[2] == vector4( 8,  9, 10, 11));
		VERIFY(m[3] == vector4(12, 13, 14, 15));

		m[0] = vector4(21,22,23,24);
		m[3] = vector4(31,32,33,34);

		VERIFY(m[0] == vector4(21, 22, 23, 24));
		VERIFY(m[1] == vector4( 4,  5,  6,  7));
		VERIFY(m[2] == vector4( 8,  9, 10, 11));
		VERIFY(m[3] == vector4(31, 32, 33, 34));
	}

	return true;
}

TYPED_TEST(MatrixTest, BracketTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		HAMON_CONSTEXPR matrix3x3 const m
		{
			0,  1,  2,
			4,  5,  6,
			8,  9, 10,
		};
		static_assert(hamon::is_same<decltype(m[0]), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[1]), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[2]), vector3 const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[0], vector3( 0,  1,  2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[1], vector3( 4,  5,  6));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[2], vector3( 8,  9, 10));
	}
	{
		HAMON_CONSTEXPR matrix3x4 const m
		{
			0,  1,  2,  3,
			4,  5,  6,  7,
			8,  9, 10, 11,
		};
		static_assert(hamon::is_same<decltype(m[0]), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[1]), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[2]), vector4 const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[0], vector4( 0,  1,  2,  3));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[1], vector4( 4,  5,  6,  7));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[2], vector4( 8,  9, 10, 11));
	}
	{
		HAMON_CONSTEXPR matrix4x3 const m
		{
			 0,  1,  2,
			 4,  5,  6,
			 8,  9, 10,
			12, 13, 14,
		};
		static_assert(hamon::is_same<decltype(m[0]), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[1]), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[2]), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[3]), vector3 const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[0], vector3( 0,  1,  2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[1], vector3( 4,  5,  6));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[2], vector3( 8,  9, 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[3], vector3(12, 13, 14));
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
			12, 13, 14, 15,
		};
		static_assert(hamon::is_same<decltype(m[0]), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[1]), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[2]), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m[3]), vector4 const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[0], vector4( 0,  1,  2,  3));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[1], vector4( 4,  5,  6,  7));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[2], vector4( 8,  9, 10, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m[3], vector4(12, 13, 14, 15));
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x3BracketTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x4BracketTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x3BracketTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x4BracketTest<T>());
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
