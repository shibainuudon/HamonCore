﻿/**
 *	@file	unit_test_qvm_vector_empty.cpp
 *
 *	@brief	emptyのテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

TYPED_TEST(VectorTest, EmptyTest)
{
	using T = TypeParam;
	using vector0 = hamon::qvm::vector<T, 0>;
	using vector1 = hamon::qvm::vector<T, 1>;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		HAMON_CONSTEXPR vector0 const v{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( v.empty());
	}
	{
		HAMON_CONSTEXPR vector1 const v{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!v.empty());
	}
	{
		HAMON_CONSTEXPR vector1 const v{1};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!v.empty());
	}
	{
		HAMON_CONSTEXPR vector2 const v{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!v.empty());
	}
	{
		HAMON_CONSTEXPR vector2 const v{1,2};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!v.empty());
	}
	{
		HAMON_CONSTEXPR vector3 const v{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!v.empty());
	}
	{
		HAMON_CONSTEXPR vector3 const v{1,2,3};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!v.empty());
	}
	{
		HAMON_CONSTEXPR vector4 const v{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!v.empty());
	}
	{
		HAMON_CONSTEXPR vector4 const v{1,2,3,4};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!v.empty());
	}
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
