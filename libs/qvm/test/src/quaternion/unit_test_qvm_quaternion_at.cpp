/**
 *	@file	unit_test_qvm_quaternion_at.cpp
 *
 *	@brief	atのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool AtTest()
{
	using quaternion = hamon::qvm::quaternion<T>;

	{
		quaternion q{1, 2, 3, 4};
		static_assert(hamon::is_same<decltype(q.at(0)), T&>::value, "");
		static_assert(hamon::is_same<decltype(q.at(1)), T&>::value, "");
		static_assert(hamon::is_same<decltype(q.at(2)), T&>::value, "");
		static_assert(hamon::is_same<decltype(q.at(3)), T&>::value, "");
		VERIFY(q.at(0) == 1);
		VERIFY(q.at(1) == 2);
		VERIFY(q.at(2) == 3);
		VERIFY(q.at(3) == 4);

		q.at(0) = -3;
		q.at(1) =  4;
		q.at(2) = -5;
		q.at(3) =  6;

		VERIFY(q.at(0) == -3);
		VERIFY(q.at(1) ==  4);
		VERIFY(q.at(2) == -5);
		VERIFY(q.at(3) ==  6);
	}

	return true;
}

TYPED_TEST(QuaternionTest, AtTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		HAMON_CONSTEXPR quaternion const q{5, 6, 7, 8};
		static_assert(hamon::is_same<decltype(q.at(0)), T const&>::value, "");
		static_assert(hamon::is_same<decltype(q.at(1)), T const&>::value, "");
		static_assert(hamon::is_same<decltype(q.at(2)), T const&>::value, "");
		static_assert(hamon::is_same<decltype(q.at(3)), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q.at(0), 5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q.at(1), 6);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q.at(2), 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q.at(3), 8);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		quaternion q{1, 2, 3, 4};
		EXPECT_THROW((void)q.at(4), hamon::out_of_range);
	}
	{
		quaternion const q{5, 6, 7, 8};
		EXPECT_THROW((void)q.at(4), hamon::out_of_range);
	}
#endif

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
