/**
 *	@file	unit_test_qvm_quaternion_empty.cpp
 *
 *	@brief	emptyのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, EmptyTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		HAMON_CONSTEXPR quaternion const q{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!q.empty());
	}
	{
		HAMON_CONSTEXPR quaternion const q{1,2,3,4};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!q.empty());
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
