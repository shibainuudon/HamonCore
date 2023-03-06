/**
 *	@file	unit_test_qvm_vector_ctor_convert.cpp
 *
 *	@brief	vector の変換コンストラクタのテスト
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
void Vector2CtorConvertTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;

	static_assert(hamon::is_constructible<vector2,  vector2i const&>::value, "");
	static_assert(hamon::is_constructible<vector2,  vector2f const&>::value, "");
	static_assert(hamon::is_constructible<vector2i, vector2  const&>::value, "");
	static_assert(hamon::is_constructible<vector2i, vector2f const&>::value, "");
	static_assert(hamon::is_constructible<vector2f, vector2  const&>::value, "");
	static_assert(hamon::is_constructible<vector2f, vector2i const&>::value, "");

	static_assert(hamon::is_nothrow_constructible<vector2,  vector2i const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector2,  vector2f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector2i, vector2  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector2i, vector2f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector2f, vector2  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector2f, vector2i const&>::value, "");

	static_assert(hamon::is_implicitly_constructible<vector2,  vector2i const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector2,  vector2f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector2i, vector2  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector2i, vector2f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector2f, vector2  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector2f, vector2i const&>::value, "");

	{
		HAMON_CONSTEXPR vector2  const v1{1, 2};
		HAMON_CONSTEXPR vector2i const v2{v1};
		HAMON_CONSTEXPR vector2f const v3{v1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v3[1]);
	}
}

template <typename T>
void Vector3CtorConvertTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(hamon::is_constructible<vector3,  vector3i const&>::value, "");
	static_assert(hamon::is_constructible<vector3,  vector3f const&>::value, "");
	static_assert(hamon::is_constructible<vector3i, vector3  const&>::value, "");
	static_assert(hamon::is_constructible<vector3i, vector3f const&>::value, "");
	static_assert(hamon::is_constructible<vector3f, vector3  const&>::value, "");
	static_assert(hamon::is_constructible<vector3f, vector3i const&>::value, "");

	static_assert(hamon::is_nothrow_constructible<vector3,  vector3i const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector3,  vector3f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector3i, vector3  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector3i, vector3f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector3f, vector3  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector3f, vector3i const&>::value, "");

	static_assert(hamon::is_implicitly_constructible<vector3,  vector3i const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector3,  vector3f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector3i, vector3  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector3i, vector3f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector3f, vector3  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector3f, vector3i const&>::value, "");

	{
		HAMON_CONSTEXPR vector3  const v1{3, 4, 5};
		HAMON_CONSTEXPR vector3i const v2{v1};
		HAMON_CONSTEXPR vector3f const v3{v1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v3[2]);
	}
}

template <typename T>
void Vector4CtorConvertTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(hamon::is_constructible<vector4,  vector4i const&>::value, "");
	static_assert(hamon::is_constructible<vector4,  vector4f const&>::value, "");
	static_assert(hamon::is_constructible<vector4i, vector4  const&>::value, "");
	static_assert(hamon::is_constructible<vector4i, vector4f const&>::value, "");
	static_assert(hamon::is_constructible<vector4f, vector4  const&>::value, "");
	static_assert(hamon::is_constructible<vector4f, vector4i const&>::value, "");

	static_assert(hamon::is_nothrow_constructible<vector4,  vector4i const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector4,  vector4f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector4i, vector4  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector4i, vector4f const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector4f, vector4  const&>::value, "");
	static_assert(hamon::is_nothrow_constructible<vector4f, vector4i const&>::value, "");

	static_assert(hamon::is_implicitly_constructible<vector4,  vector4i const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector4,  vector4f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector4i, vector4  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector4i, vector4f const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector4f, vector4  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<vector4f, vector4i const&>::value, "");

	{
		HAMON_CONSTEXPR vector4  const v1{1, 2, 3, 4};
		HAMON_CONSTEXPR vector4i const v2{v1};
		HAMON_CONSTEXPR vector4f const v3{v1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v2[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, v3[3]);
	}
}

TYPED_TEST(VectorTest, CtorConvertTest)
{
	using T = TypeParam;
	Vector2CtorConvertTest<T>();
	Vector3CtorConvertTest<T>();
	Vector4CtorConvertTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
