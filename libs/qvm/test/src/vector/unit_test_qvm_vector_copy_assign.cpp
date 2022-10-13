/**
 *	@file	unit_test_qvm_vector_copy_assign.cpp
 *
 *	@brief	vector のコピー代入のテスト
 */

#include <hamon/qvm/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector2CopyAssignTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector2i = hamon::qvm::vector<int, 2>;
	using vector2f = hamon::qvm::vector<float, 2>;

	static_assert(std::is_copy_assignable<vector2>::value, "");
	static_assert(std::is_nothrow_copy_assignable<vector2>::value, "");
	static_assert(std::is_trivially_copy_assignable<vector2>::value, "");

	vector2 v{0, 1};
	VERIFY(v[0] == 0);
	VERIFY(v[1] == 1);

	v = vector2(-2, 3);
	VERIFY(v[0] == -2);
	VERIFY(v[1] ==  3);

	v = vector2i(3, -4);
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);

	// 自己代入
	v = v;
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);

	// 多重代入
	vector2 v2;
	v2 = v = vector2f(4, 5);
	VERIFY(v[0] == 4);
	VERIFY(v[1] == 5);
	VERIFY(v2[0] == 4);
	VERIFY(v2[1] == 5);

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3CopyAssignTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector3i = hamon::qvm::vector<int, 3>;
	using vector3f = hamon::qvm::vector<float, 3>;

	static_assert(std::is_copy_assignable<vector3>::value, "");
	static_assert(std::is_nothrow_copy_assignable<vector3>::value, "");
	static_assert(std::is_trivially_copy_assignable<vector3>::value, "");

	vector3 v{0, 1, 2};
	VERIFY(v[0] == 0);
	VERIFY(v[1] == 1);
	VERIFY(v[2] == 2);

	v = vector3(-2, 3, -4);
	VERIFY(v[0] == -2);
	VERIFY(v[1] ==  3);
	VERIFY(v[2] == -4);

	v = vector3i(3, -4, 5);
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);

	// 自己代入
	v = v;
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);

	// 多重代入
	vector3 v2;
	v2 = v = vector3f(4, 5, 6);
	VERIFY(v[0] == 4);
	VERIFY(v[1] == 5);
	VERIFY(v[2] == 6);
	VERIFY(v2[0] == 4);
	VERIFY(v2[1] == 5);
	VERIFY(v2[2] == 6);

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4CopyAssignTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;
	using vector4i = hamon::qvm::vector<int, 4>;
	using vector4f = hamon::qvm::vector<float, 4>;

	static_assert(std::is_copy_assignable<vector4>::value, "");
	static_assert(std::is_nothrow_copy_assignable<vector4>::value, "");
	static_assert(std::is_trivially_copy_assignable<vector4>::value, "");

	vector4 v{0, 1, 2, 3};
	VERIFY(v[0] == 0);
	VERIFY(v[1] == 1);
	VERIFY(v[2] == 2);
	VERIFY(v[3] == 3);

	v = vector4(-2, 3, -4, 5);
	VERIFY(v[0] == -2);
	VERIFY(v[1] ==  3);
	VERIFY(v[2] == -4);
	VERIFY(v[3] ==  5);

	v = vector4i(3, -4, 5, -6);
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);
	VERIFY(v[3] == -6);

	// 自己代入
	v = v;
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);
	VERIFY(v[3] == -6);

	// 多重代入
	vector4 v2;
	v2 = v = vector4f(4, 5, 6, 7);
	VERIFY(v[0] == 4);
	VERIFY(v[1] == 5);
	VERIFY(v[2] == 6);
	VERIFY(v[3] == 7);
	VERIFY(v2[0] == 4);
	VERIFY(v2[1] == 5);
	VERIFY(v2[2] == 6);
	VERIFY(v2[3] == 7);

	return true;
}

HAMON_WARNING_POP()

TYPED_TEST(VectorTest, CopyAssignTest)
{
	using T = TypeParam;
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2CopyAssignTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3CopyAssignTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4CopyAssignTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
