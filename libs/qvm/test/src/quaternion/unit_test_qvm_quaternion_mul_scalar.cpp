/**
 *	@file	unit_test_qvm_quaternion_mul_scalar.cpp
 *
 *	@brief	スカラー積のテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool MulScalarTest()
{
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(hamon::is_same<decltype(hamon::declval<quaternion&>()  *= T{}),     quaternion&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<quaternion&>()  *= int{}),   quaternion&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<quaternion&>()  *= float{}), quaternion&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<quaternioni&>() *= T{}),     quaternioni&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<quaternioni&>() *= int{}),   quaternioni&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<quaternioni&>() *= float{}), quaternioni&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<quaternionf&>() *= T{}),     quaternionf&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<quaternionf&>() *= int{}),   quaternionf&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<quaternionf&>() *= float{}), quaternionf&>::value, "");

	// quaternion *= スカラー
	{
		quaternion v(2, 3, 4, 5);
		{
			auto t = (v *= 4);
			static_assert(hamon::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(8, 12, 16, 20));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(hamon::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(4, 6, 8, 10));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5f);
			static_assert(hamon::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(2, 3, 4, 5));
			VERIFY(t == v);
		}
	}

	return true;
}

TYPED_TEST(QuaternionTest, MulScalarTest)
{
	using T = TypeParam;
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(hamon::is_same<decltype(quaternion{}  * T{}),     quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternion{}  * int{}),   quaternion>::value, "");
	static_assert(hamon::is_same<decltype(quaternioni{} * int{}),   quaternioni>::value, "");
	static_assert(hamon::is_same<decltype(quaternioni{} * float{}), quaternionf>::value, "");
	static_assert(hamon::is_same<decltype(quaternionf{} * int{}),   quaternionf>::value, "");
	static_assert(hamon::is_same<decltype(quaternionf{} * float{}), quaternionf>::value, "");

	static_assert(hamon::is_same<decltype(T{}     * quaternion{}),  quaternion>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * quaternion{}),  quaternion>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * quaternioni{}), quaternioni>::value, "");
	static_assert(hamon::is_same<decltype(float{} * quaternioni{}), quaternionf>::value, "");
	static_assert(hamon::is_same<decltype(int{}   * quaternionf{}), quaternionf>::value, "");
	static_assert(hamon::is_same<decltype(float{} * quaternionf{}), quaternionf>::value, "");

	// quaternion * スカラー -> quaternion
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-3, 42, 5, 4) * -4, quaternion(12, -168, -20, -16));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(4, 6, 2, -10) * 2.5f, quaternion(10, 15, 5, -25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(4, 6, 2, -10) * 2.5,  quaternion(10, 15, 5, -25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(4, 6, 2, -10) * 2.5l, quaternion(10, 15, 5, -25));

	// スカラー * quaternion -> quaternion
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5    * quaternion(7, -8,  9, 2), quaternion(35, -40, 45, 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5f * quaternion(4, -6, -2, 8), quaternion(-6, 9, 3, -12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5  * quaternion(4, -6, -2, 8), quaternion(-6, 9, 3, -12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5l * quaternion(4, -6, -2, 8), quaternion(-6, 9, 3, -12));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
