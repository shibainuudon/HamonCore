/**
 *	@file	unit_test_qvm_quaternion_copy_assign.cpp
 *
 *	@brief	quaternion のコピー代入のテスト
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

HAMON_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using quaternion = hamon::qvm::quaternion<T>;
	using quaternioni = hamon::qvm::quaternion<int>;
	using quaternionf = hamon::qvm::quaternion<float>;

	static_assert(std::is_copy_assignable<quaternion>::value, "");
	static_assert(std::is_nothrow_copy_assignable<quaternion>::value, "");
	static_assert(std::is_trivially_copy_assignable<quaternion>::value, "");

	quaternion q{0, 1, 2, 3};
	VERIFY(q[0] == 0);
	VERIFY(q[1] == 1);
	VERIFY(q[2] == 2);
	VERIFY(q[3] == 3);

	q = quaternion(-2, 3, -4, 5);
	VERIFY(q[0] == -2);
	VERIFY(q[1] ==  3);
	VERIFY(q[2] == -4);
	VERIFY(q[3] ==  5);

	q = quaternioni(3, -4, 5, -6);
	VERIFY(q[0] ==  3);
	VERIFY(q[1] == -4);
	VERIFY(q[2] ==  5);
	VERIFY(q[3] == -6);

	// 自己代入
	q = q;
	VERIFY(q[0] ==  3);
	VERIFY(q[1] == -4);
	VERIFY(q[2] ==  5);
	VERIFY(q[3] == -6);

	// 多重代入
	quaternion q2;
	q2 = q = quaternionf(4, 5, 6, 7);
	VERIFY(q[0] == 4);
	VERIFY(q[1] == 5);
	VERIFY(q[2] == 6);
	VERIFY(q[3] == 7);
	VERIFY(q2[0] == 4);
	VERIFY(q2[1] == 5);
	VERIFY(q2[2] == 6);
	VERIFY(q2[3] == 7);

	return true;
}

HAMON_WARNING_POP()

TYPED_TEST(QuaternionTest, CopyAssignTest)
{
	using T = TypeParam;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<T>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
