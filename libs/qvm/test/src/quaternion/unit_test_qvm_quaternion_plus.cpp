/**
 *	@file	unit_test_qvm_quaternion_plus.cpp
 *
 *	@brief	operator+のテスト
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
inline HAMON_CXX14_CONSTEXPR bool PlusTest()
{
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(std::is_same<decltype(std::declval<quaternion&>()  += quaternion{}),  quaternion&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternion&>()  += quaternioni{}), quaternion&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternion&>()  += quaternionf{}), quaternion&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternioni&>() += quaternion{}),  quaternioni&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternioni&>() += quaternioni{}), quaternioni&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternioni&>() += quaternionf{}), quaternioni&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternionf&>() += quaternion{}),  quaternionf&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternionf&>() += quaternioni{}), quaternionf&>::value, "");
	static_assert(std::is_same<decltype(std::declval<quaternionf&>() += quaternionf{}), quaternionf&>::value, "");

	// quaternion += quaternion
	{
		quaternion v;
		VERIFY(v == quaternion(0, 0, 0, 0));
		{
			auto t = (v += quaternion(2, 3, -4, 5));
			static_assert(std::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(2, 3, -4, 5));
			VERIFY(v == t);
		}
		{
			auto t = (v += quaternionf(3, 1, 4, 1));
			static_assert(std::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(5, 4, 0, 6));
			VERIFY(v == t);
		}
		{
			auto t = (v += quaternioni(4, 3, 2, -1));
			static_assert(std::is_same<decltype(t), quaternion>::value, "");
			VERIFY(v == quaternion(9, 7, 2, 5));
			VERIFY(v == t);
		}
	}

	return true;
}

TYPED_TEST(QuaternionTest, PlusTest)
{
	using T = TypeParam;
	using quaternion  = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(std::is_same<decltype(quaternion{}  + quaternion{}),  quaternion>::value, "");
	static_assert(std::is_same<decltype(quaternion{}  + quaternioni{}), quaternion>::value, "");
	static_assert(std::is_same<decltype(quaternioni{} + quaternioni{}), quaternioni>::value, "");
	static_assert(std::is_same<decltype(quaternioni{} + quaternionf{}), quaternionf>::value, "");
	static_assert(std::is_same<decltype(quaternionf{} + quaternioni{}), quaternionf>::value, "");
	static_assert(std::is_same<decltype(quaternionf{} + quaternionf{}), quaternionf>::value, "");

	// quaternion + quaternion -> quaternion
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion (-3, 4, 5, 6) + quaternion (0, 2, -1, 3), quaternion(-3, 6, 4, 9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternionf(-3, 4, 5, 6) + quaternion (0, 2, -1, 3), quaternion(-3, 6, 4, 9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion (-3, 4, 5, 6) + quaternionf(0, 2, -1, 3), quaternion(-3, 6, 4, 9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternioni(-3, 4, 5, 6) + quaternion (0, 2, -1, 3), quaternion(-3, 6, 4, 9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(quaternion (-3, 4, 5, 6) + quaternioni(0, 2, -1, 3), quaternion(-3, 6, 4, 9));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PlusTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
