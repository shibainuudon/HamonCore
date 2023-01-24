/**
 *	@file	unit_test_span_ctor_default.cpp
 *
 *	@brief	span::span() のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace ctor_default_test
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test2()
{
	static_assert( std::is_default_constructible<hamon::span<T, hamon::dynamic_extent>>::value, "");
	static_assert( std::is_default_constructible<hamon::span<T, 0>>::value, "");
	static_assert(!std::is_default_constructible<hamon::span<T, 1>>::value, "");
	static_assert(!std::is_default_constructible<hamon::span<T, 2>>::value, "");
	static_assert( std::is_nothrow_default_constructible<hamon::span<T, hamon::dynamic_extent>>::value, "");
	static_assert( std::is_nothrow_default_constructible<hamon::span<T, 0>>::value, "");
	static_assert(!std::is_nothrow_default_constructible<hamon::span<T, 1>>::value, "");
	static_assert(!std::is_nothrow_default_constructible<hamon::span<T, 2>>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<hamon::span<T, hamon::dynamic_extent>>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<hamon::span<T, 0>>::value, "");
	static_assert(!hamon::is_implicitly_default_constructible<hamon::span<T, 1>>::value, "");
	static_assert(!hamon::is_implicitly_default_constructible<hamon::span<T, 2>>::value, "");
	hamon::span<T>    s1;
	hamon::span<T, 0> s2;
	return
		s1.data() == nullptr && s1.size() == 0 &&
		s2.data() == nullptr && s2.size() == 0;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test()
{
	return
		test2<T               >() &&
		test2<T const         >() &&
		test2<T       volatile>() &&
		test2<T const volatile>();
}

struct A{};

GTEST_TEST(SpanTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_default_test

}	// namespace hamon_span_test
