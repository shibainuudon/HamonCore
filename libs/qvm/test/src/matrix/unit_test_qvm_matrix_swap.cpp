/**
 *	@file	unit_test_qvm_matrix_swap.cpp
 *
 *	@brief	swapのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/concepts/swap.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x3SwapTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	matrix3x3 v1 =
	{
		11,12,13,
		21,22,23,
		31,32,33,
	};

	matrix3x3 v2 =
	{
		51,52,53,
		61,62,63,
		71,72,73,
	};

	v1.swap(v2);

	VERIFY(v1[0] == vector3{51,52,53});
	VERIFY(v1[1] == vector3{61,62,63});
	VERIFY(v1[2] == vector3{71,72,73});
	VERIFY(v2[0] == vector3{11,12,13});
	VERIFY(v2[1] == vector3{21,22,23});
	VERIFY(v2[2] == vector3{31,32,33});

	swap(v1, v2);

	VERIFY(v1[0] == vector3{11,12,13});
	VERIFY(v1[1] == vector3{21,22,23});
	VERIFY(v1[2] == vector3{31,32,33});
	VERIFY(v2[0] == vector3{51,52,53});
	VERIFY(v2[1] == vector3{61,62,63});
	VERIFY(v2[2] == vector3{71,72,73});

	hamon::ranges::swap(v1, v2);

	VERIFY(v1[0] == vector3{51,52,53});
	VERIFY(v1[1] == vector3{61,62,63});
	VERIFY(v1[2] == vector3{71,72,73});
	VERIFY(v2[0] == vector3{11,12,13});
	VERIFY(v2[1] == vector3{21,22,23});
	VERIFY(v2[2] == vector3{31,32,33});

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x4SwapTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	matrix3x4 v1 =
	{
		11,12,13,14,
		21,22,23,24,
		31,32,33,34,
	};

	matrix3x4 v2 =
	{
		51,52,53,54,
		61,62,63,64,
		71,72,73,74,
	};

	v1.swap(v2);

	VERIFY(v1[0] == vector4{51,52,53,54});
	VERIFY(v1[1] == vector4{61,62,63,64});
	VERIFY(v1[2] == vector4{71,72,73,74});
	VERIFY(v2[0] == vector4{11,12,13,14});
	VERIFY(v2[1] == vector4{21,22,23,24});
	VERIFY(v2[2] == vector4{31,32,33,34});

	swap(v1, v2);

	VERIFY(v1[0] == vector4{11,12,13,14});
	VERIFY(v1[1] == vector4{21,22,23,24});
	VERIFY(v1[2] == vector4{31,32,33,34});
	VERIFY(v2[0] == vector4{51,52,53,54});
	VERIFY(v2[1] == vector4{61,62,63,64});
	VERIFY(v2[2] == vector4{71,72,73,74});

	hamon::ranges::swap(v1, v2);

	VERIFY(v1[0] == vector4{51,52,53,54});
	VERIFY(v1[1] == vector4{61,62,63,64});
	VERIFY(v1[2] == vector4{71,72,73,74});
	VERIFY(v2[0] == vector4{11,12,13,14});
	VERIFY(v2[1] == vector4{21,22,23,24});
	VERIFY(v2[2] == vector4{31,32,33,34});

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x3SwapTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	matrix4x3 v1 =
	{
		11,12,13,
		21,22,23,
		31,32,33,
		41,42,43,
	};

	matrix4x3 v2 =
	{
		51,52,53,
		61,62,63,
		71,72,73,
		81,82,83,
	};

	v1.swap(v2);

	VERIFY(v1[0] == vector3{51,52,53});
	VERIFY(v1[1] == vector3{61,62,63});
	VERIFY(v1[2] == vector3{71,72,73});
	VERIFY(v1[3] == vector3{81,82,83});
	VERIFY(v2[0] == vector3{11,12,13});
	VERIFY(v2[1] == vector3{21,22,23});
	VERIFY(v2[2] == vector3{31,32,33});
	VERIFY(v2[3] == vector3{41,42,43});

	swap(v1, v2);

	VERIFY(v1[0] == vector3{11,12,13});
	VERIFY(v1[1] == vector3{21,22,23});
	VERIFY(v1[2] == vector3{31,32,33});
	VERIFY(v1[3] == vector3{41,42,43});
	VERIFY(v2[0] == vector3{51,52,53});
	VERIFY(v2[1] == vector3{61,62,63});
	VERIFY(v2[2] == vector3{71,72,73});
	VERIFY(v2[3] == vector3{81,82,83});

	hamon::ranges::swap(v1, v2);

	VERIFY(v1[0] == vector3{51,52,53});
	VERIFY(v1[1] == vector3{61,62,63});
	VERIFY(v1[2] == vector3{71,72,73});
	VERIFY(v1[3] == vector3{81,82,83});
	VERIFY(v2[0] == vector3{11,12,13});
	VERIFY(v2[1] == vector3{21,22,23});
	VERIFY(v2[2] == vector3{31,32,33});
	VERIFY(v2[3] == vector3{41,42,43});

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x4SwapTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	matrix4x4 v1 =
	{
		11,12,13,14,
		21,22,23,24,
		31,32,33,34,
		41,42,43,44,
	};

	matrix4x4 v2 =
	{
		51,52,53,54,
		61,62,63,64,
		71,72,73,74,
		81,82,83,84,
	};

	v1.swap(v2);

	VERIFY(v1[0] == vector4{51,52,53,54});
	VERIFY(v1[1] == vector4{61,62,63,64});
	VERIFY(v1[2] == vector4{71,72,73,74});
	VERIFY(v1[3] == vector4{81,82,83,84});
	VERIFY(v2[0] == vector4{11,12,13,14});
	VERIFY(v2[1] == vector4{21,22,23,24});
	VERIFY(v2[2] == vector4{31,32,33,34});
	VERIFY(v2[3] == vector4{41,42,43,44});

	swap(v1, v2);

	VERIFY(v1[0] == vector4{11,12,13,14});
	VERIFY(v1[1] == vector4{21,22,23,24});
	VERIFY(v1[2] == vector4{31,32,33,34});
	VERIFY(v1[3] == vector4{41,42,43,44});
	VERIFY(v2[0] == vector4{51,52,53,54});
	VERIFY(v2[1] == vector4{61,62,63,64});
	VERIFY(v2[2] == vector4{71,72,73,74});
	VERIFY(v2[3] == vector4{81,82,83,84});

	hamon::ranges::swap(v1, v2);

	VERIFY(v1[0] == vector4{51,52,53,54});
	VERIFY(v1[1] == vector4{61,62,63,64});
	VERIFY(v1[2] == vector4{71,72,73,74});
	VERIFY(v1[3] == vector4{81,82,83,84});
	VERIFY(v2[0] == vector4{11,12,13,14});
	VERIFY(v2[1] == vector4{21,22,23,24});
	VERIFY(v2[2] == vector4{31,32,33,34});
	VERIFY(v2[3] == vector4{41,42,43,44});

	return true;
}

TYPED_TEST(MatrixTest, SwapTest)
{
	using T = TypeParam;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x3SwapTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x4SwapTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x3SwapTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x4SwapTest<T>());
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
