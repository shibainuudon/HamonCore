/**
 *	@file	unit_test_qvm_matrix_copy_assign.cpp
 *
 *	@brief	matrix のコピー代入のテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x3CopyAssignTest()
{
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x3i = hamon::qvm::matrix<int, 3, 3>;
	using matrix3x3f = hamon::qvm::matrix<float, 3, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(hamon::is_copy_assignable<matrix3x3>::value, "");
	static_assert(hamon::is_nothrow_copy_assignable<matrix3x3>::value, "");
	static_assert(hamon::is_trivially_copy_assignable<matrix3x3>::value, "");

	matrix3x3 m1
	{
		0,  1,  2,
		4,  5,  6,
		8,  9, 10,
	};
	VERIFY(m1[0] == vector3{ 0,  1,  2});
	VERIFY(m1[1] == vector3{ 4,  5,  6});
	VERIFY(m1[2] == vector3{ 8,  9, 10});

	m1 = matrix3x3
	{
		-2, 3, -4,
		-2, 3, -4,
		-2, 3, -4,
	};
	VERIFY(m1[0] == vector3{-2, 3, -4});
	VERIFY(m1[1] == vector3{-2, 3, -4});
	VERIFY(m1[2] == vector3{-2, 3, -4});

	m1 = matrix3x3i
	{
		 3, -4,  5,
		 7,  8,  9,
		11, 12, 13,
	};
	VERIFY(m1[0] == vector3{ 3, -4,  5});
	VERIFY(m1[1] == vector3{ 7,  8,  9});
	VERIFY(m1[2] == vector3{11, 12, 13});

	// 自己代入
	m1 = m1;
	VERIFY(m1[0] == vector3{ 3, -4,  5});
	VERIFY(m1[1] == vector3{ 7,  8,  9});
	VERIFY(m1[2] == vector3{11, 12, 13});

	// 多重代入
	matrix3x3 m2;
	m2 = m1 = matrix3x3f
	{
		11,12,13,
		21,22,23,
		31,32,33,
	};
	VERIFY(m1[0] == vector3{11,12,13});
	VERIFY(m1[1] == vector3{21,22,23});
	VERIFY(m1[2] == vector3{31,32,33});
	VERIFY(m2[0] == vector3{11,12,13});
	VERIFY(m2[1] == vector3{21,22,23});
	VERIFY(m2[2] == vector3{31,32,33});

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix3x4CopyAssignTest()
{
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix3x4i = hamon::qvm::matrix<int, 3, 4>;
	using matrix3x4f = hamon::qvm::matrix<float, 3, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::is_copy_assignable<matrix3x4>::value, "");
	static_assert(hamon::is_nothrow_copy_assignable<matrix3x4>::value, "");
	static_assert(hamon::is_trivially_copy_assignable<matrix3x4>::value, "");

	matrix3x4 m1
	{
		0,  1,  2,  3,
		4,  5,  6,  7,
		8,  9, 10, 11,
	};
	VERIFY(m1[0] == vector4{ 0,  1,  2,  3});
	VERIFY(m1[1] == vector4{ 4,  5,  6,  7});
	VERIFY(m1[2] == vector4{ 8,  9, 10, 11});

	m1 = matrix3x4
	{
		-2, 3, -4, 5,
		-2, 3, -4, 5,
		-2, 3, -4, 5,
	};
	VERIFY(m1[0] == vector4{-2, 3, -4, 5});
	VERIFY(m1[1] == vector4{-2, 3, -4, 5});
	VERIFY(m1[2] == vector4{-2, 3, -4, 5});

	m1 = matrix3x4i
	{
		 3, -4,  5, -6,
		 7,  8,  9, 10,
		11, 12, 13, 14,
	};
	VERIFY(m1[0] == vector4{ 3, -4,  5, -6});
	VERIFY(m1[1] == vector4{ 7,  8,  9, 10});
	VERIFY(m1[2] == vector4{11, 12, 13, 14});

	// 自己代入
	m1 = m1;
	VERIFY(m1[0] == vector4{ 3, -4,  5, -6});
	VERIFY(m1[1] == vector4{ 7,  8,  9, 10});
	VERIFY(m1[2] == vector4{11, 12, 13, 14});

	// 多重代入
	matrix3x4 m2;
	m2 = m1 = matrix3x4f
	{
		11,12,13,14,
		21,22,23,24,
		31,32,33,34,
	};
	VERIFY(m1[0] == vector4{11,12,13,14});
	VERIFY(m1[1] == vector4{21,22,23,24});
	VERIFY(m1[2] == vector4{31,32,33,34});
	VERIFY(m2[0] == vector4{11,12,13,14});
	VERIFY(m2[1] == vector4{21,22,23,24});
	VERIFY(m2[2] == vector4{31,32,33,34});

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x3CopyAssignTest()
{
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x3i = hamon::qvm::matrix<int, 4, 3>;
	using matrix4x3f = hamon::qvm::matrix<float, 4, 3>;
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(hamon::is_copy_assignable<matrix4x3>::value, "");
	static_assert(hamon::is_nothrow_copy_assignable<matrix4x3>::value, "");
	static_assert(hamon::is_trivially_copy_assignable<matrix4x3>::value, "");

	matrix4x3 m1
	{
		 0,  1,  2,
		 4,  5,  6,
		 8,  9, 10,
		12, 13, 14,
	};
	VERIFY(m1[0] == vector3{ 0,  1,  2});
	VERIFY(m1[1] == vector3{ 4,  5,  6});
	VERIFY(m1[2] == vector3{ 8,  9, 10});
	VERIFY(m1[3] == vector3{12, 13, 14});

	m1 = matrix4x3
	{
		-2, 3, -4,
		-2, 3, -4,
		-2, 3, -4,
		-2, 3, -4,
	};
	VERIFY(m1[0] == vector3{-2, 3, -4});
	VERIFY(m1[1] == vector3{-2, 3, -4});
	VERIFY(m1[2] == vector3{-2, 3, -4});
	VERIFY(m1[3] == vector3{-2, 3, -4});

	m1 = matrix4x3i
	{
		 3, -4,  5,
		 7,  8,  9,
		11, 12, 13,
		15, 16, 17,
	};
	VERIFY(m1[0] == vector3{ 3, -4,  5});
	VERIFY(m1[1] == vector3{ 7,  8,  9});
	VERIFY(m1[2] == vector3{11, 12, 13});
	VERIFY(m1[3] == vector3{15, 16, 17});

	// 自己代入
	m1 = m1;
	VERIFY(m1[0] == vector3{ 3, -4,  5});
	VERIFY(m1[1] == vector3{ 7,  8,  9});
	VERIFY(m1[2] == vector3{11, 12, 13});
	VERIFY(m1[3] == vector3{15, 16, 17});

	// 多重代入
	matrix4x3 m2;
	m2 = m1 = matrix4x3f
	{
		11,12,13,
		21,22,23,
		31,32,33,
		41,42,43,
	};
	VERIFY(m1[0] == vector3{11,12,13});
	VERIFY(m1[1] == vector3{21,22,23});
	VERIFY(m1[2] == vector3{31,32,33});
	VERIFY(m1[3] == vector3{41,42,43});
	VERIFY(m2[0] == vector3{11,12,13});
	VERIFY(m2[1] == vector3{21,22,23});
	VERIFY(m2[2] == vector3{31,32,33});
	VERIFY(m2[3] == vector3{41,42,43});

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Matrix4x4CopyAssignTest()
{
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using matrix4x4i = hamon::qvm::matrix<int, 4, 4>;
	using matrix4x4f = hamon::qvm::matrix<float, 4, 4>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::is_copy_assignable<matrix4x4>::value, "");
	static_assert(hamon::is_nothrow_copy_assignable<matrix4x4>::value, "");
	static_assert(hamon::is_trivially_copy_assignable<matrix4x4>::value, "");

	matrix4x4 m1
	{
		 0,  1,  2,  3,
		 4,  5,  6,  7,
		 8,  9, 10, 11,
		12, 13, 14, 15,
	};
	VERIFY(m1[0] == vector4{ 0,  1,  2,  3});
	VERIFY(m1[1] == vector4{ 4,  5,  6,  7});
	VERIFY(m1[2] == vector4{ 8,  9, 10, 11});
	VERIFY(m1[3] == vector4{12, 13, 14, 15});

	m1 = matrix4x4
	{
		-2, 3, -4, 5,
		-2, 3, -4, 5,
		-2, 3, -4, 5,
		-2, 3, -4, 5,
	};
	VERIFY(m1[0] == vector4{-2, 3, -4, 5});
	VERIFY(m1[1] == vector4{-2, 3, -4, 5});
	VERIFY(m1[2] == vector4{-2, 3, -4, 5});
	VERIFY(m1[3] == vector4{-2, 3, -4, 5});

	m1 = matrix4x4i
	{
		 3, -4,  5, -6,
		 7,  8,  9, 10,
		11, 12, 13, 14,
		15, 16, 17, 18,
	};
	VERIFY(m1[0] == vector4{ 3, -4,  5, -6});
	VERIFY(m1[1] == vector4{ 7,  8,  9, 10});
	VERIFY(m1[2] == vector4{11, 12, 13, 14});
	VERIFY(m1[3] == vector4{15, 16, 17, 18});

	// 自己代入
	m1 = m1;
	VERIFY(m1[0] == vector4{ 3, -4,  5, -6});
	VERIFY(m1[1] == vector4{ 7,  8,  9, 10});
	VERIFY(m1[2] == vector4{11, 12, 13, 14});
	VERIFY(m1[3] == vector4{15, 16, 17, 18});

	// 多重代入
	matrix4x4 m2;
	m2 = m1 = matrix4x4f
	{
		11,12,13,14,
		21,22,23,24,
		31,32,33,34,
		41,42,43,44,
	};
	VERIFY(m1[0] == vector4{11,12,13,14});
	VERIFY(m1[1] == vector4{21,22,23,24});
	VERIFY(m1[2] == vector4{31,32,33,34});
	VERIFY(m1[3] == vector4{41,42,43,44});
	VERIFY(m2[0] == vector4{11,12,13,14});
	VERIFY(m2[1] == vector4{21,22,23,24});
	VERIFY(m2[2] == vector4{31,32,33,34});
	VERIFY(m2[3] == vector4{41,42,43,44});

	return true;
}

HAMON_WARNING_POP()

TYPED_TEST(MatrixTest, CopyAssignTest)
{
	using T = TypeParam;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x3CopyAssignTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix3x4CopyAssignTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x3CopyAssignTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Matrix4x4CopyAssignTest<T>());
}

#undef VERIFY

}	// namespace matrix_test

}	// namespace hamon_qvm_test
