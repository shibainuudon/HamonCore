/**
 *	@file	unit_test_qvm_quaternion_div_scalar.cpp
 *
 *	@brief	スカラー商のテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool DivScalarTest()
{
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(std::is_same<decltype(std::declval<quaternion&>()  /= T{}),     quaternion&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternion&>()  /= int{}),   quaternion&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternion&>()  /= float{}), quaternion&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternioni&>() /= T{}),     quaternioni&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternioni&>() /= int{}),   quaternioni&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternioni&>() /= float{}), quaternioni&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternionf&>() /= T{}),     quaternionf&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternionf&>() /= int{}),   quaternionf&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternionf&>() /= float{}), quaternionf&>::value, "");

	// quaternion /= スカラー
	{
		quaternion v(2, 4, 6, 8);
		{
			auto t = (v /= 2);
			static_assert(std::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(1, 2, 3, 4));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(std::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(2, 4, 6, 8));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5f);
			static_assert(std::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(4, 8, 12, 16));
			VERIFY(t == v);
		}
	}

	return true;
}

TYPED_TEST(QuaternionTest, DivScalarTest)
{
	using T = TypeParam;
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(std::is_same<decltype(quaternion{}  / T{}),     quaternion>::value, "");
	static_assert(std::is_same<decltype(quaternion{}  / int{}),   quaternion>::value, "");
	static_assert(std::is_same<decltype(quaternioni{} / int{}),   quaternioni>::value, "");
	static_assert(std::is_same<decltype(quaternioni{} / float{}), quaternionf>::value, "");
	static_assert(std::is_same<decltype(quaternionf{} / int{}),   quaternionf>::value, "");
	static_assert(std::is_same<decltype(quaternionf{} / float{}), quaternionf>::value, "");

	// quaternion / スカラー -> quaternion
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-4, 8, -12, 16) / -4, quaternion(1, -2, 3, -4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-4, 8, -12, 16) / 0.25f, quaternion(-16, 32, -48, 64));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-4, 8, -12, 16) / 0.25,  quaternion(-16, 32, -48, 64));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion(-4, 8, -12, 16) / 0.25l, quaternion(-16, 32, -48, 64));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
