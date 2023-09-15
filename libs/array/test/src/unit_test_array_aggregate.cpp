/**
 *	@file	unit_test_array_aggregate.cpp
 *
 *	@brief
 */

#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_aggregate.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

namespace hamon_array_test
{

namespace aggregate_test
{

struct Empty {};

struct Trivial { int i; int j; };

struct NonTrivial
{
	int i;
	int j;
	HAMON_CXX11_CONSTEXPR NonTrivial()
		: i(42), j(13) {}
};

template <typename T>
void AggregateTest()
{
#if defined(HAMON_HAS_IS_AGGREGATE)
	static_assert(hamon::is_aggregate<hamon::array<T, 0>>::value, "");
	static_assert(hamon::is_aggregate<hamon::array<T, 1>>::value, "");
	static_assert(hamon::is_aggregate<hamon::array<T, 2>>::value, "");
	static_assert(hamon::is_aggregate<hamon::array<T, 3>>::value, "");
	static_assert(hamon::is_aggregate<hamon::array<T, 4>>::value, "");
#endif
}

GTEST_TEST(ArrayTest, AggregateTest)
{
	AggregateTest<char>();
	AggregateTest<int>();
	AggregateTest<float>();
	AggregateTest<double>();
	AggregateTest<Empty>();
	AggregateTest<Trivial>();
	AggregateTest<NonTrivial>();
	AggregateTest<hamon::string>();
}

}	// namespace aggregate_test

}	// namespace hamon_array_test
