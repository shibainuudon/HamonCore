/**
 *	@file	unit_test_qvm_matrix_hash.cpp
 *
 *	@brief	hashのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/functional/hash.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE EXPECT_TRUE
#endif

TYPED_TEST(MatrixTest, HashTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;

	{
		HAMON_CONSTEXPR matrix3x3 const m1 { 1, 2, 3, 4, 5, 6, 7, 8, 9, };
		HAMON_CONSTEXPR matrix3x3 const m2 { 1, 2, 3, 4, 5, 6, 7, 8, 9, };
		HAMON_CONSTEXPR matrix3x3 const m3 { 0, 2, 3, 4, 5, 6, 7, 8, 9, };
		HAMON_CONSTEXPR matrix3x3 const m4 { 1,-2, 3, 4, 5, 6, 7, 8, 9, };
		HAMON_CONSTEXPR matrix3x3 const m5 { 1, 2, 4, 4, 5, 6, 7, 8, 9, };
		HAMON_CONSTEXPR matrix3x3 const m6 { 1, 2, 3, 3, 5, 6, 7, 8, 9, };
		HAMON_CONSTEXPR matrix3x3 const m7 { 1, 2, 3, 4,-5, 6, 7, 8, 9, };
		HAMON_CONSTEXPR matrix3x3 const m8 { 1, 2, 3, 4, 5, 6, 7, 8,-9, };

		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) == hamon::hash(m1));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) == hamon::hash(m2));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m3));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m4));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m5));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m6));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m7));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m8));
	}
	{
		HAMON_CONSTEXPR matrix3x4 const m1 { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, };
		HAMON_CONSTEXPR matrix3x4 const m2 { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, };
		HAMON_CONSTEXPR matrix3x4 const m3 {-10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, };
		HAMON_CONSTEXPR matrix3x4 const m4 { 10, 11, 10, 13, 14, 15, 16, 17, 18, 19, 20, 21, };
		HAMON_CONSTEXPR matrix3x4 const m5 { 10, 11, 12, 13, 14,-15, 16, 17, 18, 19, 20, 21, };
		HAMON_CONSTEXPR matrix3x4 const m6 { 10, 11, 12, 13, 14, 15, 16, 17, 18,-19, 20, 21, };
		HAMON_CONSTEXPR matrix3x4 const m7 { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19, 21, };
		HAMON_CONSTEXPR matrix3x4 const m8 { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 10, };

		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) == hamon::hash(m1));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) == hamon::hash(m2));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m3));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m4));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m5));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m6));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m7));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(m1) != hamon::hash(m8));
	}
}

#undef HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE

}	// namespace matrix_test

}	// namespace hamon_qvm_test
