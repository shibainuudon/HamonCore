/**
 *	@file	unit_test_qvm_vector_ctor_compound.cpp
 *
 *	@brief	スカラー型とベクトル型を受け取る vector のコンストラクタのテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector3CtorCompoundTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!hamon::is_constructible<vector3, vector2>::value, "");

	static_assert( hamon::is_constructible<vector3, vector2, T>::value, "");
	static_assert( hamon::is_constructible<vector3, T, vector2>::value, "");

	static_assert(!hamon::is_constructible<vector3, vector2, T, T>::value, "");
	static_assert(!hamon::is_constructible<vector3, T, vector2, T>::value, "");
	static_assert(!hamon::is_constructible<vector3, T, T, vector2>::value, "");

	static_assert(!hamon::is_constructible<vector3, vector3, T>::value, "");
	static_assert(!hamon::is_constructible<vector3, T, vector3>::value, "");

	static_assert(!hamon::is_constructible<vector3, vector4>::value, "");

	static_assert( hamon::is_nothrow_constructible<vector3, vector2, T>::value, "");
	static_assert( hamon::is_nothrow_constructible<vector3, T, vector2>::value, "");

	static_assert(!hamon::is_implicitly_constructible<vector3, vector2, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector3, T, vector2>::value, "");

	{
		HAMON_CONSTEXPR vector2 const v1(1, 2);
		HAMON_CONSTEXPR vector3 const v2(v1, 4);
		HAMON_CONSTEXPR vector3 const v3(4, v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v3[2]);
	}
}

template <typename T>
void Vector4CtorCompoundTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!hamon::is_constructible<vector4, vector3>::value, "");

	static_assert( hamon::is_constructible<vector4, vector3, T>::value, "");
	static_assert( hamon::is_constructible<vector4, T, vector3>::value, "");

	static_assert(!hamon::is_constructible<vector4, vector3, T, T>::value, "");
	static_assert(!hamon::is_constructible<vector4, T, vector3, T>::value, "");
	static_assert(!hamon::is_constructible<vector4, T, T, vector3>::value, "");

	static_assert( hamon::is_constructible<vector4, vector2, T, T>::value, "");
	static_assert( hamon::is_constructible<vector4, T, vector2, T>::value, "");
	static_assert( hamon::is_constructible<vector4, T, T, vector2>::value, "");

	static_assert(!hamon::is_constructible<vector4, vector2, T, T, T>::value, "");
	static_assert(!hamon::is_constructible<vector4, T, vector2, T, T>::value, "");
	static_assert(!hamon::is_constructible<vector4, T, T, vector2, T>::value, "");
	static_assert(!hamon::is_constructible<vector4, T, T, T, vector2>::value, "");

	static_assert( hamon::is_constructible<vector4, vector2, vector2>::value, "");

	static_assert(!hamon::is_constructible<vector4, vector2, vector2, T>::value, "");
	static_assert(!hamon::is_constructible<vector4, vector2, T, vector2>::value, "");
	static_assert(!hamon::is_constructible<vector4, T, vector2, vector2>::value, "");

	static_assert( hamon::is_nothrow_constructible<vector4, vector3, T>::value, "");
	static_assert( hamon::is_nothrow_constructible<vector4, T, vector3>::value, "");
	static_assert( hamon::is_nothrow_constructible<vector4, vector2, T, T>::value, "");
	static_assert( hamon::is_nothrow_constructible<vector4, T, vector2, T>::value, "");
	static_assert( hamon::is_nothrow_constructible<vector4, T, T, vector2>::value, "");
	static_assert( hamon::is_nothrow_constructible<vector4, vector2, vector2>::value, "");

	static_assert(!hamon::is_implicitly_constructible<vector4, vector3, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector4, T, vector3>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector4, vector2, T, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector4, T, vector2, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector4, T, T, vector2>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector4, vector2, vector2>::value, "");

	{
		HAMON_CONSTEXPR vector3 const v1(1, 2, 3);
		HAMON_CONSTEXPR vector4 const v2(v1, 4);
		HAMON_CONSTEXPR vector4 const v3(4, v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v2[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v3[3]);
	}
	{
		HAMON_CONSTEXPR vector2 const v1(4, 5);
		HAMON_CONSTEXPR vector4 const v2(v1, 6, 7);
		HAMON_CONSTEXPR vector4 const v3(8, v1, 9);
		HAMON_CONSTEXPR vector4 const v4(10, 11, v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v2[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9, v3[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, v4[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v4[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, v4[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, v4[3]);
	}
	{
		HAMON_CONSTEXPR vector2 const v1(1, 2);
		HAMON_CONSTEXPR vector2 const v2(3, 4);
		HAMON_CONSTEXPR vector4 const v3(v1, v2);
		HAMON_CONSTEXPR vector4 const v4(v2, v1);
		HAMON_CONSTEXPR vector4 const v5(vector2{5, 6}, vector2{7, 8});
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v3[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v4[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v4[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v4[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v4[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v5[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v5[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v5[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, v5[3]);
	}
}

TYPED_TEST(VectorTest, CtorCompoundTest)
{
	using T = TypeParam;
	Vector3CtorCompoundTest<T>();
	Vector4CtorCompoundTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
