/**
 *	@file	unit_test_vector_back.cpp
 *
 *	@brief	back のテスト
 *
 *	constexpr reference       back();
 *	constexpr const_reference back() const;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using Reference = typename Vector::reference;
	using ConstReference = typename Vector::const_reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().back()),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().back()),
		ConstReference
	>::value, "");

#if !defined(HAMON_USE_STD_VECTOR)
	static_assert(!noexcept(
		hamon::declval<Vector&>().back()), "");
	static_assert(!noexcept(
		hamon::declval<Vector const&>().back()), "");
#endif

	{
		Vector v{1,2,3};
		VERIFY(v.back() == 3);

		v.back() = 42;

		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 42);
	}
	{
		Vector const v{1,2,3};
		VERIFY(v.back() == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, BackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace back_test

}	// namespace hamon_vector_test
