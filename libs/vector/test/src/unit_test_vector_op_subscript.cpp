/**
 *	@file	unit_test_vector_op_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr reference       operator[](size_type n);
 *	constexpr const_reference operator[](size_type n) const;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace op_subscript_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;
	using Reference = typename Vector::reference;
	using ConstReference = typename Vector::const_reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>()[hamon::declval<SizeType>()]),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>()[hamon::declval<SizeType>()]),
		ConstReference
	>::value, "");

#if !defined(HAMON_USE_STD_VECTOR)
	static_assert(!noexcept(
		hamon::declval<Vector&>()[hamon::declval<SizeType>()]), "");
	static_assert(!noexcept(
		hamon::declval<Vector const&>()[hamon::declval<SizeType>()]), "");
#endif

	{
		Vector v{1,2,3};
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);

		v[0] = 10;
		v[2] = 20;

		VERIFY(v[0] == 10);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
	}
	{
		Vector const v{1,2,3};
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, OpSubscriptTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace op_subscript_test

}	// namespace hamon_vector_test
