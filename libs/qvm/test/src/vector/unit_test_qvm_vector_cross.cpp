/**
 *	@file	unit_test_qvm_vector_cross.cpp
 *
 *	@brief	crossのテスト
 */

#include <hamon/qvm/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

TYPED_TEST(VectorTest, CrossTest)
{
	using T = TypeParam;
	using vector3  = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;

	static_assert(std::is_same<decltype(cross(vector3 {}, vector3 {})), vector3>::value, "");
	static_assert(std::is_same<decltype(cross(vector3i{}, vector3 {})), vector3>::value, "");
	static_assert(std::is_same<decltype(cross(vector3 {}, vector3i{})), vector3>::value, "");
	static_assert(std::is_same<decltype(cross(vector3i{}, vector3i{})), vector3i>::value, "");

	{
		HAMON_CONSTEXPR vector3 v { 0, 0, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3(-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector3 v { 1, 0, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3(-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 1), cross(v, vector3( 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0,-1), cross(v, vector3( 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0,-1, 0), cross(v, vector3( 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 1, 0), cross(v, vector3( 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector3 v { -2, 0, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3(-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0,-2), cross(v, vector3( 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 2), cross(v, vector3( 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 2, 0), cross(v, vector3( 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0,-2, 0), cross(v, vector3( 0, 0,-1)));
	}
	{
		HAMON_CONSTEXPR vector3 v { 0, 1, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0,-3), cross(v, vector3( 3, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 3), cross(v, vector3(-3, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 3, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0,-3, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 3, 0, 0), cross(v, vector3( 0, 0, 3)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-3, 0, 0), cross(v, vector3( 0, 0,-3)));
	}
	{
		HAMON_CONSTEXPR vector3 v { 0, -2, 0 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 6), cross(v, vector3( 3, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0,-6), cross(v, vector3(-3, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 3, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0,-3, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-6, 0, 0), cross(v, vector3( 0, 0, 3)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 6, 0, 0), cross(v, vector3( 0, 0,-3)));
	}
	{
		HAMON_CONSTEXPR vector3 v { 0, 0, 3 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 9, 0), cross(v, vector3( 3, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0,-9, 0), cross(v, vector3(-3, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-9, 0, 0), cross(v, vector3( 0, 3, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 9, 0, 0), cross(v, vector3( 0,-3, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 3)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0,-3)));
	}
	{
		HAMON_CONSTEXPR vector3 v { 0, 0, -1 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0,-1, 0), cross(v, vector3( 1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 1, 0), cross(v, vector3(-1, 0, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1, 0, 0), cross(v, vector3( 0, 1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-1, 0, 0), cross(v, vector3( 0,-1, 0)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0, 1)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), cross(v, vector3( 0, 0,-1)));
	}
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
