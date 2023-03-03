/**
 *	@file	unit_test_qvm_matrix_at.cpp
 *
 *	@brief	atのテスト
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
inline HAMON_CXX14_CONSTEXPR bool Matrix3x3AtTest()
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
		static_assert(hamon::is_same<decltype(m.at(0)), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(1)), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(2)), vector3&>::value, "");
		VERIFY(m.at(0) == vector3( 0,  1,  2));
		VERIFY(m.at(1) == vector3( 4,  5,  6));
		VERIFY(m.at(2) == vector3( 8,  9, 10));

		m.at(0) = vector3(21,22,23);

		VERIFY(m.at(0) == vector3(21, 22, 23));
		VERIFY(m.at(1) == vector3( 4,  5,  6));
		VERIFY(m.at(2) == vector3( 8,  9, 10));
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x4AtTest()
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
		static_assert(hamon::is_same<decltype(m.at(0)), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(1)), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(2)), vector4&>::value, "");
		VERIFY(m.at(0) == vector4( 0,  1,  2,  3));
		VERIFY(m.at(1) == vector4( 4,  5,  6,  7));
		VERIFY(m.at(2) == vector4( 8,  9, 10, 11));

		m.at(0) = vector4(21,22,23,24);

		VERIFY(m.at(0) == vector4(21, 22, 23, 24));
		VERIFY(m.at(1) == vector4( 4,  5,  6,  7));
		VERIFY(m.at(2) == vector4( 8,  9, 10, 11));
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x3AtTest()
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
		static_assert(hamon::is_same<decltype(m.at(0)), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(1)), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(2)), vector3&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(3)), vector3&>::value, "");
		VERIFY(m.at(0) == vector3( 0,  1,  2));
		VERIFY(m.at(1) == vector3( 4,  5,  6));
		VERIFY(m.at(2) == vector3( 8,  9, 10));
		VERIFY(m.at(3) == vector3(12, 13, 14));

		m.at(0) = vector3(21,22,23);
		m.at(3) = vector3(31,32,33);

		VERIFY(m.at(0) == vector3(21, 22, 23));
		VERIFY(m.at(1) == vector3( 4,  5,  6));
		VERIFY(m.at(2) == vector3( 8,  9, 10));
		VERIFY(m.at(3) == vector3(31, 32, 33));
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x4AtTest()
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
		static_assert(hamon::is_same<decltype(m.at(0)), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(1)), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(2)), vector4&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(3)), vector4&>::value, "");
		VERIFY(m.at(0) == vector4( 0,  1,  2,  3));
		VERIFY(m.at(1) == vector4( 4,  5,  6,  7));
		VERIFY(m.at(2) == vector4( 8,  9, 10, 11));
		VERIFY(m.at(3) == vector4(12, 13, 14, 15));

		m.at(0) = vector4(21,22,23,24);
		m.at(3) = vector4(31,32,33,34);

		VERIFY(m.at(0) == vector4(21, 22, 23, 24));
		VERIFY(m.at(1) == vector4( 4,  5,  6,  7));
		VERIFY(m.at(2) == vector4( 8,  9, 10, 11));
		VERIFY(m.at(3) == vector4(31, 32, 33, 34));
	}

	return true;
}

TYPED_TEST(MatrixTest, AtTest)
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
		static_assert(hamon::is_same<decltype(m.at(0)), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(1)), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(2)), vector3 const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(0), vector3( 0,  1,  2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(1), vector3( 4,  5,  6));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(2), vector3( 8,  9, 10));
	}
	{
		HAMON_CONSTEXPR matrix3x4 const m
		{
			0,  1,  2,  3,
			4,  5,  6,  7,
			8,  9, 10, 11,
		};
		static_assert(hamon::is_same<decltype(m.at(0)), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(1)), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(2)), vector4 const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(0), vector4( 0,  1,  2,  3));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(1), vector4( 4,  5,  6,  7));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(2), vector4( 8,  9, 10, 11));
	}
	{
		HAMON_CONSTEXPR matrix4x3 const m
		{
			 0,  1,  2,
			 4,  5,  6,
			 8,  9, 10,
			12, 13, 14,
		};
		static_assert(hamon::is_same<decltype(m.at(0)), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(1)), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(2)), vector3 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(3)), vector3 const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(0), vector3( 0,  1,  2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(1), vector3( 4,  5,  6));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(2), vector3( 8,  9, 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(3), vector3(12, 13, 14));
	}
	{
		HAMON_CONSTEXPR matrix4x4 const m
		{
			 0,  1,  2,  3,
			 4,  5,  6,  7,
			 8,  9, 10, 11,
			12, 13, 14, 15,
		};
		static_assert(hamon::is_same<decltype(m.at(0)), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(1)), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(2)), vector4 const&>::value, "");
		static_assert(hamon::is_same<decltype(m.at(3)), vector4 const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(0), vector4( 0,  1,  2,  3));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(1), vector4( 4,  5,  6,  7));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(2), vector4( 8,  9, 10, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(m.at(3), vector4(12, 13, 14, 15));
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		matrix3x3 m;
		EXPECT_THROW((void)m.at(3), std::out_of_range);
	}
	{
		matrix3x3 const m;
		EXPECT_THROW((void)m.at(3), std::out_of_range);
	}
	{
		matrix3x4 m;
		EXPECT_THROW((void)m.at(3), std::out_of_range);
	}
	{
		matrix3x4 const m;
		EXPECT_THROW((void)m.at(3), std::out_of_range);
	}
	{
		matrix4x3 m;
		EXPECT_THROW((void)m.at(4), std::out_of_range);
	}
	{
		matrix4x3 const m;
		EXPECT_THROW((void)m.at(4), std::out_of_range);
	}
	{
		matrix4x4 m;
		EXPECT_THROW((void)m.at(4), std::out_of_range);
	}
	{
		matrix4x4 const m;
		EXPECT_THROW((void)m.at(4), std::out_of_range);
	}
#endif

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x3AtTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x4AtTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x3AtTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x4AtTest<T>());
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
