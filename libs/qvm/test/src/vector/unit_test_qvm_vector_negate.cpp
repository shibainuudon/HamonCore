/**
 *	@file	unit_test_qvm_vector_negate.cpp
 *
 *	@brief	unary operator-のテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/operators.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T>
void Vector2NegateTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	{
		HAMON_CONSTEXPR vector2 const v1(1, 2);
		HAMON_CONSTEXPR auto const v2 = +v1;
		HAMON_CONSTEXPR auto const v3 = -v1;
		static_assert(hamon::is_same<decltype(v2), vector2 const>::value, "");
		static_assert(hamon::is_same<decltype(v3), vector2 const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[0],  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[1],  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[0], -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[1], -2);
	}
}

template <typename T>
void Vector3NegateTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	{
		HAMON_CONSTEXPR vector3 const v1(-1, 2, 3);
		HAMON_CONSTEXPR auto const v2 = +v1;
		HAMON_CONSTEXPR auto const v3 = -v1;
		static_assert(hamon::is_same<decltype(v2), vector3 const>::value, "");
		static_assert(hamon::is_same<decltype(v3), vector3 const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[0], -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[1],  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[2],  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[0],  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[1], -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[2], -3);
	}
}

template <typename T>
void Vector4NegateTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		HAMON_CONSTEXPR vector4 const v1(-1, 2, -3, 4);
		HAMON_CONSTEXPR auto const v2 = +v1;
		HAMON_CONSTEXPR auto const v3 = -v1;
		static_assert(hamon::is_same<decltype(v2), vector4 const>::value, "");
		static_assert(hamon::is_same<decltype(v3), vector4 const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[0], -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[1],  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[2], -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2[3],  4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[0],  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[1], -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[2],  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v3[3], -4);
	}
}

TYPED_TEST(VectorTest, NegateTest)
{
	using T = TypeParam;
	Vector2NegateTest<T>();
	Vector3NegateTest<T>();
	Vector4NegateTest<T>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
