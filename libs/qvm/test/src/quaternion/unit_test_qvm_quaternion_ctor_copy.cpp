/**
 *	@file	unit_test_qvm_quaternion_ctor_copy.cpp
 *
 *	@brief	quaternion のコピーコンストラクタのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, CtorCopyTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert( hamon::is_copy_constructible<quaternion>::value, "");
	static_assert( hamon::is_nothrow_copy_constructible<quaternion>::value, "");
	static_assert( hamon::is_trivially_copy_constructible<quaternion>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<quaternion>::value, "");

	{
		HAMON_CONSTEXPR quaternion const q1{1, 2, 3, 4};
		HAMON_CONSTEXPR quaternion const q2{q1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, q2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, q2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q2[3]);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
