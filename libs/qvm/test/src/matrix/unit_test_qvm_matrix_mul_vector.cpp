/**
 *	@file	unit_test_qvm_matrix_mul_vector.cpp
 *
 *	@brief	ベクトルと行列の積のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool MulVectorTest()
{
	using matrix3x3  = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;
	using matrix3x3f = hamon::qvm::matrix<float, 3, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;
	using matrix4x4f = hamon::qvm::matrix<float, 4, 4>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::is_same<decltype(hamon::declval<vector3&>() *= matrix3x3{}),  vector3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3&>() *= matrix3x3i{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector3&>() *= matrix3x3f{}), vector3&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4&>() *= matrix4x4{}),  vector4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4&>() *= matrix4x4i{}), vector4&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<vector4&>() *= matrix4x4f{}), vector4&>::value, "");

	// vector3 *= matrix3x3
	{
		vector3 v { 1, 2, 3 };

		const matrix3x3 m
		{
			11, 12, 13,
			21, 22, 23,
			31, 32, 33,
		};

		auto t = (v *= m);
		VERIFY(vector3(146, 152, 158) == v);
		VERIFY(t == v);
	}

	// vector4 *= matrix4x4
	{
		vector4 v { 1, 2, 3, 4 };
		matrix4x4 const m
		{
			11, 12, 13, 14,
			21, 22, 23, 24,
			31, 32, 33, 34,
			41, 42, 43, 44,
		};

		auto t = (v *= m);
		VERIFY(vector4(310, 320, 330, 340) == v);
		VERIFY(t == v);
	}

	return true;
}

TYPED_TEST(MatrixTest, MulVectorTest)
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
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;
	using vector4  = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(hamon::is_same<decltype(vector3{}  * matrix3x3{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3{}  * matrix3x3i{}), vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * matrix3x3{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * matrix3x3i{}), vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * matrix3x3f{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * matrix3x3i{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * matrix3x3f{}), vector3f>::value, "");

	static_assert(hamon::is_same<decltype(vector3{}  * matrix3x4{}),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector3{}  * matrix3x4i{}), vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * matrix3x4{}),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * matrix3x4i{}), vector4i>::value, "");
	static_assert(hamon::is_same<decltype(vector3i{} * matrix3x4f{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * matrix3x4i{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector3f{} * matrix3x4f{}), vector4f>::value, "");

	static_assert(hamon::is_same<decltype(vector4{}  * matrix4x3{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector4{}  * matrix4x3i{}), vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * matrix4x3{}),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * matrix4x3i{}), vector3i>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * matrix4x3f{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} * matrix4x3i{}), vector3f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} * matrix4x3f{}), vector3f>::value, "");

	static_assert(hamon::is_same<decltype(vector4{}  * matrix4x4{}),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4{}  * matrix4x4i{}), vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * matrix4x4{}),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * matrix4x4i{}), vector4i>::value, "");
	static_assert(hamon::is_same<decltype(vector4i{} * matrix4x4f{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} * matrix4x4i{}), vector4f>::value, "");
	static_assert(hamon::is_same<decltype(vector4f{} * matrix4x4f{}), vector4f>::value, "");

	// vector3 * matrix3x3 -> vector3
	{
		HAMON_CONSTEXPR vector3 const v { -5, 6, 7 };
		HAMON_CONSTEXPR matrix3x3 const m
		{
			1, -2,  3,
			5,  6,  7,
			9, 10,-11,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(88, 116, -50), v * m);
	}

	// vector3 * matrix3x4 -> vector4
	{
		HAMON_CONSTEXPR vector3 v { 1, 2, 3 };
		HAMON_CONSTEXPR matrix3x4 m
		{
			1,  -2,   3,   4,
			5,   6,   7,   8,
			9,  10, -11, -12,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(38, 40, -16, -16), v * m);
	}
	{
		HAMON_CONSTEXPR vector3i v { 1, 2, 3 };
		HAMON_CONSTEXPR matrix3x4 m
		{
			1,  -2,   3,   4,
			5,   6,   7,   8,
			9,  10, -11, -12,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(38, 40, -16, -16), v * m);
	}

	// vector4 * matrix4x3 -> vector3
	{
		HAMON_CONSTEXPR vector4 v { -5, 6, 7, 8 };
		HAMON_CONSTEXPR matrix4x3 m
		{
			 1,  -2,   3,
			 5,   6,   7,
			 9,  10, -11,
			13, -14,  15,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(192, 4, 70), v * m);
	}
	{
		HAMON_CONSTEXPR vector4 v { -5, 6, 7, 8 };
		HAMON_CONSTEXPR matrix4x3i m
		{
			 1,  -2,   3,
			 5,   6,   7,
			 9,  10, -11,
			13, -14,  15,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(192, 4, 70), v * m);
	}

	// vector4 * matrix4x4 -> vector4
	{
		HAMON_CONSTEXPR vector4 const v { -5, 6, 7, 8 };
		HAMON_CONSTEXPR matrix4x4 const m
		{
			 1,  -2,   3,   4,
			 5,   6,   7,   8,
			 9,  10, -11, -12,
			13, -14,  15,  16,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(192, 4, 70, 72), v * m);
	}
	{
		HAMON_CONSTEXPR vector4 const v { -5, 6, 7, 8 };
		HAMON_CONSTEXPR matrix4x4i const m
		{
			 1,  -2,   3,   4,
			 5,   6,   7,   8,
			 9,  10, -11, -12,
			13, -14,  15,  16,
		};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(192, 4, 70, 72), v * m);
	}

	// TODO
	// matrix3x3 * vector3 -> vector3
	// matrix4x3 * vector3 -> vector4
	// matrix3x4 * vector4 -> vector3
	// matrix4x4 * vector4 -> vector4

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulVectorTest<T>());
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
