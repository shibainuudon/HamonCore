﻿/**
 *	@file	unit_test_qvm_quaternion_identity.cpp
 *
 *	@brief	identityのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, IdentityTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(hamon::is_same<decltype(quaternion::identity()), quaternion>::value, "");
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(0, 0, 0, 1), quaternion::identity());
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
