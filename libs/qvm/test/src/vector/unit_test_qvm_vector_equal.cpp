/**
 *	@file	unit_test_qvm_vector_equal.cpp
 *
 *	@brief	equalのテスト
 */

#include <hamon/qvm/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

TYPED_TEST(VectorTest, EqualTest)
{
	using T = TypeParam;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;
	using vector2b = hamon::qvm::vector<bool, 2>;
	using vector3b = hamon::qvm::vector<bool, 3>;
	using vector4b = hamon::qvm::vector<bool, 4>;

	{
		HAMON_CONSTEXPR vector2 const v1{1, 2};
		HAMON_CONSTEXPR vector2 const v2{1, 2};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector2b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[1]);
	}
	{
		HAMON_CONSTEXPR vector2 const v1{1, 2};
		HAMON_CONSTEXPR vector2 const v2{0, 2};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector2b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[1]);
	}
	{
		HAMON_CONSTEXPR vector2 const v1{1, 2};
		HAMON_CONSTEXPR vector2 const v2{1, 3};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector2b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[1]);
	}
	{
		HAMON_CONSTEXPR vector2 const v1{1, 2};
		HAMON_CONSTEXPR vector2 const v2{2, 1};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector2b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[1]);
	}
	{
		HAMON_CONSTEXPR vector3 const v1{1, 2, 3};
		HAMON_CONSTEXPR vector3 const v2{1, 2, 3};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[2]);
	}
	{
		HAMON_CONSTEXPR vector3 const v1{0, 2, 3};
		HAMON_CONSTEXPR vector3 const v2{1, 2, 3};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[2]);
	}
	{
		HAMON_CONSTEXPR vector3 const v1{1, 2, 3};
		HAMON_CONSTEXPR vector3 const v2{1, 3, 3};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[2]);
	}
	{
		HAMON_CONSTEXPR vector3 const v1{1, 2, 3};
		HAMON_CONSTEXPR vector3 const v2{1, 2,-3};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[2]);
	}
	{
		HAMON_CONSTEXPR vector3 const v1{1, 2, 3};
		HAMON_CONSTEXPR vector3 const v2{0, 1, 2};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector3b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[2]);
	}
	{
		HAMON_CONSTEXPR vector4 const v1{ 1, 2, 3, 4};
		HAMON_CONSTEXPR vector4 const v2{ 1, 2, 3, 4};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector4b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[3]);
	}
	{
		HAMON_CONSTEXPR vector4 const v1{ 1, 2, 3, 4};
		HAMON_CONSTEXPR vector4 const v2{ 1,-2,-3,-4};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector4b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[3]);
	}
	{
		HAMON_CONSTEXPR vector4 const v1{ 1, 2, 3, 4};
		HAMON_CONSTEXPR vector4 const v2{-1, 2,-3,-4};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector4b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[3]);
	}
	{
		HAMON_CONSTEXPR vector4 const v1{ 1, 2, 3, 4};
		HAMON_CONSTEXPR vector4 const v2{-1,-2, 3,-4};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector4b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[3]);
	}
	{
		HAMON_CONSTEXPR vector4 const v1{ 1, 2, 3, 4};
		HAMON_CONSTEXPR vector4 const v2{-1,-2,-3, 4};
		HAMON_CONSTEXPR auto const v3 = hamon::qvm::equal(v1, v2);
		static_assert(std::is_same<decltype(v3), vector4b const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v3[3]);
	}
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
