/**
 *	@file	unit_test_qvm_quaternion_negate.cpp
 *
 *	@brief	unary operator-のテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, NegateTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		HAMON_CONSTEXPR quaternion const v1(-1, 2, -3, 4);
		HAMON_CONSTEXPR auto const v2 = +v1;
		HAMON_CONSTEXPR auto const v3 = -v1;
		static_assert(hamon::is_same<decltype(v2), quaternion const>::value, "");
		static_assert(hamon::is_same<decltype(v3), quaternion const>::value, "");

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

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
