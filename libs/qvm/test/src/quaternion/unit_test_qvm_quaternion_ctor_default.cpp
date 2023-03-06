/**
 *	@file	unit_test_qvm_quaternion_ctor_default.cpp
 *
 *	@brief	quaternion のデフォルトコンストラクタのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, CtorDefaultTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(sizeof(quaternion) == sizeof(T) * 4, "");
	static_assert(hamon::is_default_constructible<quaternion>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<quaternion>::value, "");
	static_assert(hamon::is_implicitly_default_constructible<quaternion>::value, "");
	static_assert(hamon::is_destructible<quaternion>::value, "");
	static_assert(hamon::is_nothrow_destructible<quaternion>::value, "");
	static_assert(hamon::is_trivially_destructible<quaternion>::value, "");

	{
		HAMON_CONSTEXPR quaternion const q;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[3]);
	}
	{
		HAMON_CONSTEXPR quaternion const q{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[3]);
	}
	{
		HAMON_CONSTEXPR quaternion const q = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, q[3]);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
