/**
 *	@file	unit_test_qvm_quaternion_bracket.cpp
 *
 *	@brief	operator[]のテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool BracketTest()
{
	using quaternion = hamon::qvm::quaternion<T>;

	{
		quaternion q{1, 2, 3, 4};
		static_assert(hamon::is_same<decltype(q[0]), T&>::value, "");
		static_assert(hamon::is_same<decltype(q[1]), T&>::value, "");
		static_assert(hamon::is_same<decltype(q[2]), T&>::value, "");
		static_assert(hamon::is_same<decltype(q[3]), T&>::value, "");
		VERIFY(q[0] == 1);
		VERIFY(q[1] == 2);
		VERIFY(q[2] == 3);
		VERIFY(q[3] == 4);

		q[0] = -3;
		q[1] =  4;
		q[2] = -5;
		q[3] =  6;

		VERIFY(q[0] == -3);
		VERIFY(q[1] ==  4);
		VERIFY(q[2] == -5);
		VERIFY(q[3] ==  6);
	}

	return true;
}

TYPED_TEST(QuaternionTest, BracketTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		HAMON_CONSTEXPR quaternion const q{5, 6, 7, 8};
		static_assert(hamon::is_same<decltype(q[0]), T const&>::value, "");
		static_assert(hamon::is_same<decltype(q[1]), T const&>::value, "");
		static_assert(hamon::is_same<decltype(q[2]), T const&>::value, "");
		static_assert(hamon::is_same<decltype(q[3]), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q[0], 5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q[1], 6);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q[2], 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q[3], 8);
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BracketTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
