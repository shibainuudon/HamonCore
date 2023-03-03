/**
 *	@file	unit_test_qvm_vector_lerp.cpp
 *
 *	@brief	lerpのテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/operators.hpp>
#include <hamon/qvm/common/lerp.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

TYPED_TEST(VectorFloatTest, LerpTest)
{
	using T = TypeParam;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::is_same<decltype(lerp(vector2{}, vector2{}, T{})),  vector2>::value, "");
	static_assert(hamon::is_same<decltype(lerp(vector2{}, vector2{}, 0.0f)), vector2>::value, "");
	static_assert(hamon::is_same<decltype(lerp(vector2{}, vector2{}, 0.0L)), hamon::qvm::vector<long double, 2>>::value, "");
	static_assert(hamon::is_same<decltype(lerp(vector3{}, vector3{}, T{})),  vector3>::value, "");
	static_assert(hamon::is_same<decltype(lerp(vector3{}, vector3{}, 0.0f)), vector3>::value, "");
	static_assert(hamon::is_same<decltype(lerp(vector3{}, vector3{}, 0.0L)), hamon::qvm::vector<long double, 3>>::value, "");
	static_assert(hamon::is_same<decltype(lerp(vector4{}, vector4{}, T{})),  vector4>::value, "");
	static_assert(hamon::is_same<decltype(lerp(vector4{}, vector4{}, 0.0f)), vector4>::value, "");
	static_assert(hamon::is_same<decltype(lerp(vector4{}, vector4{}, 0.0L)), hamon::qvm::vector<long double, 4>>::value, "");

	// vector2
	{
		HAMON_CONSTEXPR vector2 v1 {  0,  0 };
		HAMON_CONSTEXPR vector2 v2 { 10, 20 };

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 0.0,  0.0), lerp(v1, v2, T(0.00)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 2.5,  5.0), lerp(v1, v2, T(0.25)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 5.0, 10.0), lerp(v1, v2, T(0.50)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 7.5, 15.0), lerp(v1, v2, T(0.75)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(10.0, 20.0), lerp(v1, v2, T(1.00)));
	}
	{
		HAMON_CONSTEXPR vector2 v1 { -10,  10 };
		HAMON_CONSTEXPR vector2 v2 {  10, -20 };

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(-10.0,  10.0), lerp(v1, v2, 0.00));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( -5.0,   2.5), lerp(v1, v2, 0.25));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(  0.0,  -5.0), lerp(v1, v2, 0.50));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2(  5.0, -12.5), lerp(v1, v2, 0.75));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector2( 10.0, -20.0), lerp(v1, v2, 1.00));
	}

	// vector3
	{
		HAMON_CONSTEXPR vector3 v1 {  0,  0,  0 };
		HAMON_CONSTEXPR vector3 v2 { 10, 20, 30 };

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0.0,  0.0,  0.0), lerp(v1, v2, T(0.00)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 2.5,  5.0,  7.5), lerp(v1, v2, T(0.25)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 5.0, 10.0, 15.0), lerp(v1, v2, T(0.50)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 7.5, 15.0, 22.5), lerp(v1, v2, T(0.75)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(10.0, 20.0, 30.0), lerp(v1, v2, T(1.00)));
	}
	{
		HAMON_CONSTEXPR vector3 v1 { -10,  10,  20 };
		HAMON_CONSTEXPR vector3 v2 {  10, -20, -30 };

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-10.0,  10.0,  20.0), lerp(v1, v2, 0.00f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( -5.0,   2.5,   7.5), lerp(v1, v2, 0.25f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(  0.0,  -5.0,  -5.0), lerp(v1, v2, 0.50f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(  5.0, -12.5, -17.5), lerp(v1, v2, 0.75f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 10.0, -20.0, -30.0), lerp(v1, v2, 1.00f));
	}

	// vector4
	{
		HAMON_CONSTEXPR vector4 v1 {  0,  0,  0,  0 };
		HAMON_CONSTEXPR vector4 v2 { 10, 20, 30, 40 };

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 0.0,  0.0,  0.0,  0.0), lerp(v1, v2, T(0.00)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 2.5,  5.0,  7.5, 10.0), lerp(v1, v2, T(0.25)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 5.0, 10.0, 15.0, 20.0), lerp(v1, v2, T(0.50)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 7.5, 15.0, 22.5, 30.0), lerp(v1, v2, T(0.75)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(10.0, 20.0, 30.0, 40.0), lerp(v1, v2, T(1.00)));
	}
	{
		HAMON_CONSTEXPR vector4 v1 { -10,  10,  20, -30 };
		HAMON_CONSTEXPR vector4 v2 {  10, -20, -30,  40 };

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(-10.0,  10.0,  20.0, -30.0), lerp(v1, v2, T(0.00)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( -5.0,   2.5,   7.5, -12.5), lerp(v1, v2, T(0.25)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  0.0,  -5.0,  -5.0,   5.0), lerp(v1, v2, T(0.50)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4(  5.0, -12.5, -17.5,  22.5), lerp(v1, v2, T(0.75)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector4( 10.0, -20.0, -30.0,  40.0), lerp(v1, v2, T(1.00)));
	}
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
