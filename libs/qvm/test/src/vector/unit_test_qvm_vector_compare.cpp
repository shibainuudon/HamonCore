/**
 *	@file	unit_test_qvm_vector_compare.cpp
 *
 *	@brief	operator==のテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/operators.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector2CompareTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;

	HAMON_CONSTEXPR vector2 const v1(1, 2);
	HAMON_CONSTEXPR vector2 const v2(1, 2);
	HAMON_CONSTEXPR vector2 const v3(2, 2);
	HAMON_CONSTEXPR vector2 const v4(1, 0);
	HAMON_CONSTEXPR vector2i const v5(1, 2);
	HAMON_CONSTEXPR vector2i const v6(2, 2);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v6);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v6);
}

template <typename T>
void Vector3CompareTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;

	HAMON_CONSTEXPR vector3 const v1(1, 2, 3);
	HAMON_CONSTEXPR vector3 const v2(1, 2, 3);
	HAMON_CONSTEXPR vector3 const v3(2, 2, 3);
	HAMON_CONSTEXPR vector3 const v4(1, 0, 3);
	HAMON_CONSTEXPR vector3 const v5(1, 2, 2);
	HAMON_CONSTEXPR vector3i const v6(1, 2, 3);
	HAMON_CONSTEXPR vector3i const v7(1, 2, 2);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v6);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v7);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v6);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v7);
}

template <typename T>
void Vector4CompareTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;

	HAMON_CONSTEXPR vector4 const v1(1, 2, 3, 4);
	HAMON_CONSTEXPR vector4 const v2(1, 2, 3, 4);
	HAMON_CONSTEXPR vector4 const v3(2, 2, 3, 4);
	HAMON_CONSTEXPR vector4 const v4(1, 0, 3, 4);
	HAMON_CONSTEXPR vector4 const v5(1, 2, 2, 4);
	HAMON_CONSTEXPR vector4 const v6(1, 2, 3, 5);
	HAMON_CONSTEXPR vector4i const v7(1, 2, 3, 4);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 == v6);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 == v7);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v1 != v6);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v1 != v7);
}

TYPED_TEST(VectorTest, CompareTest)
{
	using T = TypeParam;
	Vector2CompareTest<T>();
	Vector3CompareTest<T>();
	Vector4CompareTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
