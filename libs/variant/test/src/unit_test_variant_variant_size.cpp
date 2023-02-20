/**
 *	@file	unit_test_variant_variant_size.cpp
 *
 *	@brief	variant_size のテスト
 */

#include <hamon/variant/variant_size.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_base_of.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <gtest/gtest.h>

namespace hamon_variant_test
{

namespace variant_size_test
{

template <hamon::size_t N, typename V>
void test()
{
	static_assert(hamon::variant_size<V>::value == N, "");
	static_assert(hamon::variant_size<V const>::value == N, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	static_assert(hamon::variant_size_v<V> == N, "");
	static_assert(hamon::variant_size_v<V const> == N, "");
#endif
	static_assert(hamon::is_base_of<
		hamon::integral_constant<hamon::size_t, N>,
		hamon::variant_size<V>
	>::value, "");
	static_assert(hamon::is_base_of<
		hamon::integral_constant<hamon::size_t, N>,
		hamon::variant_size<V const>
	>::value, "");
}

GTEST_TEST(VariantTest, VariantSizeTest)
{
	test<0, hamon::variant<>>();
	test<1, hamon::variant<int>>();
	test<1, hamon::variant<void*>>();
	test<2, hamon::variant<int,  void*>>();
	test<2, hamon::variant<char, float>>();
	test<2, hamon::variant<int,  int>>();
	test<3, hamon::variant<int, const int, float>>();
	test<4, hamon::variant<long, void*, char, double>>();
}

}	// namespace variant_size_test

}	// namespace hamon_variant_test
