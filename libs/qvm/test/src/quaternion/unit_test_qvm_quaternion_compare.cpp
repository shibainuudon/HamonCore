/**
 *	@file	unit_test_qvm_quaternion_compare.cpp
 *
 *	@brief	operator==のテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, CompareTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;

	HAMON_CONSTEXPR quaternion  const q1(1, 2, 3, 4);
	HAMON_CONSTEXPR quaternion  const q2(1, 2, 3, 4);
	HAMON_CONSTEXPR quaternion  const q3(2, 2, 3, 4);
	HAMON_CONSTEXPR quaternion  const q4(1, 0, 3, 4);
	HAMON_CONSTEXPR quaternion  const q5(1, 2, 2, 4);
	HAMON_CONSTEXPR quaternion  const q6(1, 2, 3, 5);
	HAMON_CONSTEXPR quaternioni const q7(1, 2, 3, 4);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (q1 == q1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (q1 == q2);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(q1 == q3);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(q1 == q4);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(q1 == q5);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(q1 == q6);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (q1 == q7);

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(q1 != q1);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(q1 != q2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (q1 != q3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (q1 != q4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (q1 != q5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (q1 != q6);
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(q1 != q7);
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
