/**
 *	@file	unit_test_qvm_quaternion_conjugate.cpp
 *
 *	@brief	conjugateのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, ConjugateTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(std::is_same<decltype(conjugate(quaternion{})), quaternion>::value, "");
	HAMON_CONSTEXPR quaternion q1(1, 2, 3, 4);
	HAMON_CONSTEXPR auto const q2 = conjugate(q1);
	HAMON_CONSTEXPR auto const q3 = conjugate(q2);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q1, q3);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 1,  2,  3, 4), q1);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-1, -2, -3, 4), q2);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 1,  2,  3, 4), q3);

	{
		// 四元数 q = ix + jy + kz + w の共役をq'としたとき、
		// q * q' = q' * q = x^2 + y^2 + z^2 + w^2
		// となる。
		HAMON_CONSTEXPR quaternion expected{ 0, 0, 0, 1*1 + 2*2 + 3*3 + 4*4 };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, q1 * q2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, q2 * q1);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
