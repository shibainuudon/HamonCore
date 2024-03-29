﻿/**
 *	@file	unit_test_qvm_quaternion_max_size.cpp
 *
 *	@brief	max_sizeのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, MaxSizeTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		HAMON_CONSTEXPR quaternion const q{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, q.max_size());
	}
	{
		HAMON_CONSTEXPR quaternion const q{1,2,3,4};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, q.max_size());
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
