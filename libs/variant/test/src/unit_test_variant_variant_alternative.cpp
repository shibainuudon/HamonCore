/**
 *	@file	unit_test_variant_variant_alternative.cpp
 *
 *	@brief	variant_alternative のテスト
 */

#include <hamon/variant/variant_alternative.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_variant_test
{

namespace variant_alternative_test
{

template <typename V, hamon::size_t I, typename T>
void test()
{
	static_assert(hamon::is_same<
		typename hamon::variant_alternative<I, V>::type,
		T
	>::value, "");
	
	static_assert(hamon::is_same<
		typename hamon::variant_alternative<I, V const>::type,
		T const
	>::value, "");

	static_assert(hamon::is_same<
		hamon::variant_alternative_t<I, V>,
		T
	>::value, "");
	
	static_assert(hamon::is_same<
		hamon::variant_alternative_t<I, V const>,
		T const
	>::value, "");
}

GTEST_TEST(VariantTest, VariantAlternativeTest)
{
	{
		using V = hamon::variant<int>;
		test<V, 0, int>();
	}
	{
		using V = hamon::variant<float>;
		test<V, 0, float>();
	}
	{
		using V = hamon::variant<char, short const>;
		test<V, 0, char>();
		test<V, 1, short const>();
	}
	{
		using V = hamon::variant<float const, double*, long>;
		test<V, 0, float const>();
		test<V, 1, double*>();
		test<V, 2, long>();
	}
	{
		using V = hamon::variant<int, void *, const void *, long double>;
		test<V, 0, int>();
		test<V, 1, void *>();
		test<V, 2, const void *>();
		test<V, 3, long double>();
	}
}

}	// namespace variant_alternative_test

}	// namespace hamon_variant_test
