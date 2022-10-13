/**
 *	@file	unit_test_qvm_vector_ctor_copy.cpp
 *
 *	@brief	vector のコピーコンストラクタのテスト
 */

#include <hamon/qvm/vector.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector2CtorCopyTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	static_assert( std::is_copy_constructible<vector2>::value, "");
	static_assert( std::is_nothrow_copy_constructible<vector2>::value, "");
	static_assert( std::is_trivially_copy_constructible<vector2>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<vector2>::value, "");

	{
		HAMON_CONSTEXPR vector2 const v1{1, 2};
		HAMON_CONSTEXPR vector2 const v2{v1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2[1]);
	}
}

template <typename T>
void Vector3CtorCopyTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	static_assert( std::is_copy_constructible<vector3>::value, "");
	static_assert( std::is_nothrow_copy_constructible<vector3>::value, "");
	static_assert( std::is_trivially_copy_constructible<vector3>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<vector3>::value, "");

	{
		HAMON_CONSTEXPR vector3 const v1{1, 2, 3};
		HAMON_CONSTEXPR vector3 const v2{v1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2[2]);
	}
}

template <typename T>
void Vector4CtorCopyTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert( std::is_copy_constructible<vector4>::value, "");
	static_assert( std::is_nothrow_copy_constructible<vector4>::value, "");
	static_assert( std::is_trivially_copy_constructible<vector4>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<vector4>::value, "");

	{
		HAMON_CONSTEXPR vector4 const v1{1, 2, 3, 4};
		HAMON_CONSTEXPR vector4 const v2{v1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v2[3]);
	}
}

TYPED_TEST(VectorTest, CtorCopyTest)
{
	using T = TypeParam;
	Vector2CtorCopyTest<T>();
	Vector3CtorCopyTest<T>();
	Vector4CtorCopyTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
