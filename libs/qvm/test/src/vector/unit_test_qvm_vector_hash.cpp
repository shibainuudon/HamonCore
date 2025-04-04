﻿/**
 *	@file	unit_test_qvm_vector_hash.cpp
 *
 *	@brief	hashのテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/functional/ranges/hash.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE HAMON_CXX11_CONSTEXPR_EXPECT_TRUE
#else
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE EXPECT_TRUE
#endif

TYPED_TEST(VectorTest, HashTest)
{
	using T = TypeParam;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	{
		HAMON_CONSTEXPR vector2 const v1(1, 2);
		HAMON_CONSTEXPR vector2 const v2(1, 2);
		HAMON_CONSTEXPR vector2 const v3(0, 2);
		HAMON_CONSTEXPR vector2 const v4(1, 3);

		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) == hamon::ranges::hash(v1));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) == hamon::ranges::hash(v2));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v3));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v4));
	}

	{
		HAMON_CONSTEXPR vector3 const v1(1, 2, 3);
		HAMON_CONSTEXPR vector3 const v2(1, 2, 3);
		HAMON_CONSTEXPR vector3 const v3(0, 2, 3);
		HAMON_CONSTEXPR vector3 const v4(1, 3, 3);
		HAMON_CONSTEXPR vector3 const v5(1, 2,-3);

		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) == hamon::ranges::hash(v1));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) == hamon::ranges::hash(v2));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v3));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v4));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v5));
	}

	{
		HAMON_CONSTEXPR vector4 const v1(1, 2, 3, 4);
		HAMON_CONSTEXPR vector4 const v2(1, 2, 3, 4);
		HAMON_CONSTEXPR vector4 const v3(0, 2, 3, 4);
		HAMON_CONSTEXPR vector4 const v4(1, 3, 3, 4);
		HAMON_CONSTEXPR vector4 const v5(1, 2,-3, 4);
		HAMON_CONSTEXPR vector4 const v6(1, 2, 3, 1);

		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) == hamon::ranges::hash(v1));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) == hamon::ranges::hash(v2));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v3));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v4));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v5));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::ranges::hash(v1) != hamon::ranges::hash(v6));
	}
}

#undef HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE

}	// namespace vector_test

}	// namespace hamon_qvm_test
