/**
 *	@file	unit_test_expected_types.cpp
 *
 *	@brief
 */

#include <hamon/expected.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_expected_test
{

namespace types_test
{

template <typename T, typename E>
void test()
{
	using Expected = hamon::expected<T, E>;
	static_assert(hamon::is_same<typename Expected::value_type, T>::value, "");
	static_assert(hamon::is_same<typename Expected::error_type, E>::value, "");
	static_assert(hamon::is_same<typename Expected::unexpected_type, hamon::unexpected<E>>::value, "");

	using Expected2 = typename Expected::template rebind<int>;
	static_assert(hamon::is_same<Expected2, hamon::expected<int, E>>::value, "");

	using Expected3 = typename Expected::template rebind<long>;
	static_assert(hamon::is_same<Expected3, hamon::expected<long, E>>::value, "");
}

GTEST_TEST(ExpectedTest, TypesTest)
{
	test<int, int>();
	test<int, float>();
	test<char, hamon::string>();
}

}	// namespace types_test

}	// namespace hamon_expected_test
