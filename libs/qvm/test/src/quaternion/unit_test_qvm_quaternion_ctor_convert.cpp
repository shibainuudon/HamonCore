/**
 *	@file	unit_test_qvm_quaternion_ctor_convert.cpp
 *
 *	@brief	quaternion の変換コンストラクタのテスト
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

TYPED_TEST(QuaternionTest, CtorConvertTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(std::is_constructible<quaternion,  quaternioni const&>::value, "");
	static_assert(std::is_constructible<quaternion,  quaternionf const&>::value, "");
	static_assert(std::is_constructible<quaternioni, quaternion  const&>::value, "");
	static_assert(std::is_constructible<quaternioni, quaternionf const&>::value, "");
	static_assert(std::is_constructible<quaternionf, quaternion  const&>::value, "");
	static_assert(std::is_constructible<quaternionf, quaternioni const&>::value, "");

	static_assert(std::is_nothrow_constructible<quaternion,  quaternioni const&>::value, "");
	static_assert(std::is_nothrow_constructible<quaternion,  quaternionf const&>::value, "");
	static_assert(std::is_nothrow_constructible<quaternioni, quaternion  const&>::value, "");
	static_assert(std::is_nothrow_constructible<quaternioni, quaternionf const&>::value, "");
	static_assert(std::is_nothrow_constructible<quaternionf, quaternion  const&>::value, "");
	static_assert(std::is_nothrow_constructible<quaternionf, quaternioni const&>::value, "");

	static_assert(hamon::is_implicitly_constructible<quaternion,  quaternioni const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<quaternion,  quaternionf const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<quaternioni, quaternion  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<quaternioni, quaternionf const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<quaternionf, quaternion  const&>::value, "");
	static_assert(hamon::is_implicitly_constructible<quaternionf, quaternioni const&>::value, "");

	{
		HAMON_CONSTEXPR quaternion  const q1{1, 2, 3, 4};
		HAMON_CONSTEXPR quaternioni const q2{q1};
		HAMON_CONSTEXPR quaternionf const q3{q1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, q2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, q2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q2[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, q3[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, q3[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, q3[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, q3[3]);
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
