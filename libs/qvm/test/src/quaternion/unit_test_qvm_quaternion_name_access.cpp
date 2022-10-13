/**
 *	@file	unit_test_qvm_quaternion_name_access.cpp
 *
 *	@brief	名前でのアクセスのテスト
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
inline HAMON_CXX14_CONSTEXPR bool NameAccessTest()
{
	using quaternion = hamon::qvm::quaternion<T>;

	{
		quaternion q{1, 2, 3, 4};
		static_assert(std::is_same<decltype(q.x()), T&>::value, "");
		static_assert(std::is_same<decltype(q.y()), T&>::value, "");
		static_assert(std::is_same<decltype(q.z()), T&>::value, "");
		static_assert(std::is_same<decltype(q.w()), T&>::value, "");
		VERIFY(q.x() == 1);
		VERIFY(q.y() == 2);
		VERIFY(q.z() == 3);
		VERIFY(q.w() == 4);

		q.x() = -3;
		q.y() =  4;
		q.z() = -5;
		q.w() =  6;

		VERIFY(q.x() == -3);
		VERIFY(q.y() ==  4);
		VERIFY(q.z() == -5);
		VERIFY(q.w() ==  6);
	}

	return true;
}

TYPED_TEST(QuaternionTest, NameAccessTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	{
		HAMON_CONSTEXPR quaternion const q{5, 6, 7, 8};
		static_assert(std::is_same<decltype(q.x()), T const&>::value, "");
		static_assert(std::is_same<decltype(q.y()), T const&>::value, "");
		static_assert(std::is_same<decltype(q.z()), T const&>::value, "");
		static_assert(std::is_same<decltype(q.w()), T const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q.x(), 5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q.y(), 6);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q.z(), 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(q.w(), 8);
	}

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
