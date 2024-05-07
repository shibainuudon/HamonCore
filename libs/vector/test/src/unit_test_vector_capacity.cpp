/**
 *	@file	unit_test_vector_capacity.cpp
 *
 *	@brief	capacity のテスト
 *
 *	constexpr size_type capacity() const noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace capacity_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector const&>().capacity()),
		SizeType
	>::value, "");
	static_assert(noexcept(
		hamon::declval<Vector const&>().capacity()), "");

	{
		Vector const v;
		VERIFY(v.capacity() == 0);
	}
	{
		Vector v{1};
		VERIFY(v.capacity() >= 1);
		v.push_back(10);
		VERIFY(v.capacity() >= 2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, CapacityTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace capacity_test

}	// namespace hamon_vector_test
