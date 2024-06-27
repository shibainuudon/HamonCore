/**
 *	@file	unit_test_span_ctor_initializer_list.cpp
 *
 *	@brief	span::span(std::initializer_list<value_type>) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace ctor_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
void test()
{
	static_assert(!hamon::is_constructible<hamon::span<T               >, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 3>, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 3>, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 3>, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 3>, std::initializer_list<T>>::value, "");

	static_assert(!hamon::is_nothrow_constructible<hamon::span<T const>, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::span<T const, 3>, std::initializer_list<T>>::value, "");

	static_assert( hamon::is_implicitly_constructible<hamon::span<T const>, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T const, 3>, std::initializer_list<T>>::value, "");
}

HAMON_CXX14_CONSTEXPR bool test1(hamon::span<const int> s)
{
	VERIFY(s.size() == 3);
	VERIFY(s[0] == 1);
	VERIFY(s[1] == 2);
	VERIFY(s[2] == 3);
	return true;
}

#undef VERIFY

GTEST_TEST(SpanTest, CtorInitializerListTest)
{
	test<int>();
	test<float>();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1({1,2,3}));
}

}	// namespace ctor_initializer_list_test

}	// namespace hamon_span_test
