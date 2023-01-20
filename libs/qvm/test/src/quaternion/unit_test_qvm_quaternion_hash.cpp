/**
 *	@file	unit_test_qvm_quaternion_hash.cpp
 *
 *	@brief	hashのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/functional/hash.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE HAMON_CXX11_CONSTEXPR_EXPECT_TRUE
#else
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE EXPECT_TRUE
#endif

TYPED_TEST(QuaternionTest, HashTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		HAMON_CONSTEXPR quaternion const q1(1, 2, 3, 4);
		HAMON_CONSTEXPR quaternion const q2(1, 2, 3, 4);
		HAMON_CONSTEXPR quaternion const q3(0, 2, 3, 4);
		HAMON_CONSTEXPR quaternion const q4(1, 3, 3, 4);
		HAMON_CONSTEXPR quaternion const q5(1, 2,-3, 4);
		HAMON_CONSTEXPR quaternion const q6(1, 2, 3, 1);

		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(q1) == hamon::hash(q1));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(q1) == hamon::hash(q2));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(q1) != hamon::hash(q3));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(q1) != hamon::hash(q4));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(q1) != hamon::hash(q5));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE(hamon::hash(q1) != hamon::hash(q6));
	}
}

#undef HAMON_BIT_CAST_CONSTEXPR_EXPECT_TRUE

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
