/**
 *	@file	unit_test_qvm_quaternion_imag.cpp
 *
 *	@brief	imagのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, ImagTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;
	using vector3 = hamon::qvm::vector<T, 3>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 0, 0, 0), quaternion( 0, 0, 0, 0).imag());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1, 2, 3), quaternion( 1, 2, 3, 4).imag());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3(-1, 2, 3), quaternion(-1, 2, 3, 4).imag());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1,-2, 3), quaternion( 1,-2, 3, 4).imag());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1, 2,-3), quaternion( 1, 2,-3, 4).imag());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 1, 2, 3), quaternion( 1, 2, 3,-4).imag());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(vector3( 5, 6, 7), quaternion( 5, 6, 7, 8).imag());
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
