/**
 *	@file	unit_test_qvm_quaternion_data.cpp
 *
 *	@brief	dataのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, DataTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		quaternion const q;
		auto p = q.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(p == &q[0]);
		static_assert(std::is_same<decltype(p), T const*>::value, "");
	}
	{
		quaternion q;
		auto p = q.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(p == &q[0]);
		static_assert(std::is_same<decltype(p), T*>::value, "");
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
