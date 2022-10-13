/**
 *	@file	unit_test_qvm_vector_swap.cpp
 *
 *	@brief	swapのテスト
 */

#include <hamon/qvm/vector.hpp>
#include <hamon/concepts/swap.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector2SwapTest()
{
	using vector2 = hamon::qvm::vector<T, 2>;

	vector2 v1{1, 2};
	vector2 v2{5, 6};

	v1.swap(v2);

	VERIFY(v1 == vector2(5, 6));
	VERIFY(v2 == vector2(1, 2));

	swap(v1, v2);

	VERIFY(v1 == vector2(1, 2));
	VERIFY(v2 == vector2(5, 6));

	hamon::ranges::swap(v1, v2);

	VERIFY(v1 == vector2(5, 6));
	VERIFY(v2 == vector2(1, 2));

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector3SwapTest()
{
	using vector3 = hamon::qvm::vector<T, 3>;

	vector3 v1{1, 2, 3};
	vector3 v2{5, 6, 7};

	v1.swap(v2);

	VERIFY(v1 == vector3(5, 6, 7));
	VERIFY(v2 == vector3(1, 2, 3));

	swap(v1, v2);

	VERIFY(v1 == vector3(1, 2, 3));
	VERIFY(v2 == vector3(5, 6, 7));

	hamon::ranges::swap(v1, v2);

	VERIFY(v1 == vector3(5, 6, 7));
	VERIFY(v2 == vector3(1, 2, 3));

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool Vector4SwapTest()
{
	using vector4 = hamon::qvm::vector<T, 4>;

	vector4 v1{1, 2, 3, 4};
	vector4 v2{5, 6, 7, 8};

	v1.swap(v2);

	VERIFY(v1 == vector4(5, 6, 7, 8));
	VERIFY(v2 == vector4(1, 2, 3, 4));

	swap(v1, v2);

	VERIFY(v1 == vector4(1, 2, 3, 4));
	VERIFY(v2 == vector4(5, 6, 7, 8));

	hamon::ranges::swap(v1, v2);

	VERIFY(v1 == vector4(5, 6, 7, 8));
	VERIFY(v2 == vector4(1, 2, 3, 4));

	return true;
}

TYPED_TEST(VectorTest, SwapTest)
{
	using T = TypeParam;

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector2SwapTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector3SwapTest<T>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Vector4SwapTest<T>());
}

#undef VERIFY

}	// namespace vector_test

}	// namespace hamon_qvm_test
