/**
 *	@file	unit_test_qvm_vector_ctor_sclar.cpp
 *
 *	@brief	スカラー型を受け取る vector のコンストラクタのテスト
 */

#include <hamon/qvm/vector.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector2CtorScalarTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	static_assert(!std::is_constructible<vector2, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<vector2, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<vector2, T, T, T>::value, "");
	static_assert( std::is_constructible<vector2, T, T>::value, "");
	static_assert( std::is_constructible<vector2, T>::value, "");

	static_assert( std::is_nothrow_constructible<vector2, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<vector2, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<vector2, T, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector2, T>::value, "");

	// スカラー型を2つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR vector2 const v(1, 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
	}
	{
		HAMON_CONSTEXPR vector2 const v{6, 7};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v[1]);
	}
	{
		HAMON_CONSTEXPR vector2 const v = {11, 12};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v[1]);
	}

	// スカラー型を1つ受け取った場合
	// →全ての要素に値をコピー
	{
		HAMON_CONSTEXPR vector2 const v(10);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, v[1]);
	}
	{
		HAMON_CONSTEXPR vector2 const v{11};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v[1]);
	}
	{
		//HAMON_CONSTEXPR vector2 const v = {12};	// explicit なのでこう書くことはできない
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v[0]);
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v[1]);
	}
}

template <typename T>
void Vector3CtorScalarTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert(!std::is_constructible<vector3, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<vector3, T, T, T, T>::value, "");
	static_assert( std::is_constructible<vector3, T, T, T>::value, "");
	static_assert(!std::is_constructible<vector3, T, T>::value, "");
	static_assert( std::is_constructible<vector3, T>::value, "");

	static_assert( std::is_nothrow_constructible<vector3, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<vector3, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<vector3, T, T, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector3, T>::value, "");

	// スカラー型を3つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR vector3 const v(1, 2, 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[2]);
	}
	{
		HAMON_CONSTEXPR vector3 const v{5, 6, 7};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v[2]);
	}
	{
		HAMON_CONSTEXPR vector3 const v = {9, 10, 11};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v[2]);
	}

	// スカラー型を1つ受け取った場合
	// →全ての要素に値をコピー
	{
		HAMON_CONSTEXPR vector3 const v(13);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, v[2]);
	}
	{
		HAMON_CONSTEXPR vector3 const v{14};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, v[2]);
	}
	{
		//HAMON_CONSTEXPR vector3 const v = {15};	// explicit なのでこう書くことはできない
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, v[0]);
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, v[1]);
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, v[2]);
	}
}

template <typename T>
void Vector4CtorScalarTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!std::is_constructible<vector4, T, T, T, T, T>::value, "");
	static_assert( std::is_constructible<vector4, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<vector4, T, T, T>::value, "");
	static_assert(!std::is_constructible<vector4, T, T>::value, "");
	static_assert( std::is_constructible<vector4, T>::value, "");

	static_assert( std::is_nothrow_constructible<vector4, T, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<vector4, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<vector4, T, T, T, T>::value, "");
	static_assert(!hamon::is_implicitly_constructible<vector4, T>::value, "");

	// スカラー型を4つ受け取るコンストラクタ
	{
		HAMON_CONSTEXPR vector4 const v(1, 2, 3, 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v[3]);
	}
	{
		HAMON_CONSTEXPR vector4 const v{5, 6, 7, 8};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, v[3]);
	}
	{
		HAMON_CONSTEXPR vector4 const v = {9, 10, 11, 12};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v[3]);
	}

	// スカラー型を1つ受け取った場合
	// →全ての要素に値をコピー
	{
		HAMON_CONSTEXPR vector4 const v(16);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, v[3]);
	}
	{
		HAMON_CONSTEXPR vector4 const v{17};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, v[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, v[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, v[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, v[3]);
	}
	{
		//HAMON_CONSTEXPR vector4 const v = {18};	// explicit なのでこう書くことはできない
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, v[0]);
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, v[1]);
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, v[2]);
		//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, v[3]);
	}
}

TYPED_TEST(VectorTest, CtorScalarTest)
{
	using T = TypeParam;
	Vector2CtorScalarTest<T>();
	Vector3CtorScalarTest<T>();
	Vector4CtorScalarTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
