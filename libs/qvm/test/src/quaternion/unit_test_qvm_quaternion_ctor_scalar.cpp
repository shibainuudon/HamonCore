/**
 *	@file	unit_test_qvm_quaternion_ctor_scalar.cpp
 *
 *	@brief	スカラー型を受け取る quaternion のコンストラクタのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, CtorScalarTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(!std::is_constructible<quaternion, T, T, T, T, T>::value, "");
	static_assert( std::is_constructible<quaternion, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T, T, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T, T>::value, "");
	static_assert(!std::is_constructible<quaternion, T>::value, "");

	static_assert( std::is_nothrow_constructible<quaternion, T, T, T, T>::value, "");

	static_assert( hamon::is_implicitly_constructible<quaternion, T, T, T, T>::value, "");

	{
		HAMON_CONSTEXPR quaternion const q(1, 2, 3, 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, q[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, q[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q[3]);
	}
	{
		HAMON_CONSTEXPR quaternion const q{5, 6, 7, 8};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, q[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, q[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, q[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, q[3]);
	}
	{
		HAMON_CONSTEXPR quaternion const q = {9, 10, 11, 12};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, q[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, q[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, q[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, q[3]);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
