/**
 *	@file	unit_test_expected_void_types.cpp
 *
 *	@brief
 */

#include <hamon/expected.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <gtest/gtest.h>

namespace hamon_expected_void_test
{

namespace types_test
{

template <typename Void, typename E>
void test()
{
	static_assert(hamon::is_void<Void>::value, "");

	using Expected = hamon::expected<Void, E>;
	static_assert(hamon::is_same<typename Expected::value_type, Void>::value, "");
	static_assert(hamon::is_same<typename Expected::error_type, E>::value, "");
	static_assert(hamon::is_same<typename Expected::unexpected_type, hamon::unexpected<E>>::value, "");

	using Expected2 = typename Expected::template rebind<int>;
	static_assert(hamon::is_same<Expected2, hamon::expected<int, E>>::value, "");

	using Expected3 = typename Expected::template rebind<long>;
	static_assert(hamon::is_same<Expected3, hamon::expected<long, E>>::value, "");
}

GTEST_TEST(ExpectedVoidTest, TypesTest)
{
	test<void, int>();
	test<void const, float>();
	test<void volatile, hamon::string>();
	test<void const volatile, char>();
}

}	// namespace types_test

}	// namespace hamon_expected_void_test
