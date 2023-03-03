/**
 *	@file	unit_test_qvm_quaternion_normalize.cpp
 *
 *	@brief	normalizeのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionFloatTest, NormalizeTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(hamon::is_same<decltype(normalize(quaternion{})), quaternion>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 0, 0, 1), normalize(quaternion(0, 0, 0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 1, 0, 0, 0), normalize(quaternion(  1,  0,  0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-1, 0, 0, 0), normalize(quaternion( -1,  0,  0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 1, 0, 0, 0), normalize(quaternion( 10,  0,  0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-1, 0, 0, 0), normalize(quaternion(-10,  0,  0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 1, 0, 0), normalize(quaternion(  0,  1,  0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0,-1, 0, 0), normalize(quaternion(  0, -1,  0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 1, 0, 0), normalize(quaternion(  0,  5,  0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0,-1, 0, 0), normalize(quaternion(  0, -5,  0, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 0, 1, 0), normalize(quaternion(  0,  0,  1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 0,-1, 0), normalize(quaternion(  0,  0, -1, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 0, 1, 0), normalize(quaternion(  0,  0, 42, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 0,-1, 0), normalize(quaternion(  0,  0,-42, 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 0, 0, 1), normalize(quaternion(  0,  0,  0, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion( 0, 0, 0,-1), normalize(quaternion(  0,  0,  0,-3)));
	{
		HAMON_CONSTEXPR auto const t = normalize(quaternion(1, 2, 3, 4));
		HAMON_CONSTEXPR double const error = 0.000001;
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.18257418583, (double)t[0], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.36514837167, (double)t[1], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.54772255750, (double)t[2], error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.73029674334, (double)t[3], error);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
