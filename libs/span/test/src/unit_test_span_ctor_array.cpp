/**
 *	@file	unit_test_span_ctor_array.cpp
 *
 *	@brief	span::span(element_type (&arr)[N]) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace ctor_array_test
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
cv_test()
{
	static_assert( std::is_constructible<hamon::span<T               >, T               (&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               >, T const         (&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               >, T       volatile(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               >, T const volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const         >, T               (&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const         >, T const         (&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         >, T       volatile(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         >, T const volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T       volatile>, T               (&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile>, T const         (&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T       volatile>, T       volatile(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile>, T const volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile>, T               (&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile>, T const         (&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile>, T       volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile>, T const volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T               >, T               (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               >, T const         (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               >, T       volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               >, T const volatile(&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const         >, T               (&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const         >, T const         (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         >, T       volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         >, T const volatile(&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T       volatile>, T               (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile>, T const         (&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T       volatile>, T       volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile>, T const volatile(&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile>, T               (&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile>, T const         (&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile>, T       volatile(&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile>, T const volatile(&)[3]>::value, "");
	static_assert( std::is_constructible<hamon::span<T               , 2>, T               (&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               , 2>, T const         (&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               , 2>, T       volatile(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               , 2>, T const volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const         , 2>, T               (&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const         , 2>, T const         (&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         , 2>, T       volatile(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         , 2>, T const volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T       volatile, 2>, T               (&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile, 2>, T const         (&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T       volatile, 2>, T       volatile(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile, 2>, T const volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile, 2>, T               (&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile, 2>, T const         (&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile, 2>, T       volatile(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T const volatile, 2>, T const volatile(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               , 2>, T               (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               , 2>, T const         (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               , 2>, T       volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T               , 2>, T const volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         , 2>, T               (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         , 2>, T const         (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         , 2>, T       volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const         , 2>, T const volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile, 2>, T               (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile, 2>, T const         (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile, 2>, T       volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T       volatile, 2>, T const volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const volatile, 2>, T               (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const volatile, 2>, T const         (&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const volatile, 2>, T       volatile(&)[3]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T const volatile, 2>, T const volatile(&)[3]>::value, "");

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test2()
{
	static_assert( std::is_constructible<hamon::span<T>   , T(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T, 0>, T(&)[2]>::value, "");
	static_assert(!std::is_constructible<hamon::span<T, 1>, T(&)[2]>::value, "");
	static_assert( std::is_constructible<hamon::span<T, 2>, T(&)[2]>::value, "");
	static_assert( std::is_nothrow_constructible<hamon::span<T>   , T(&)[2]>::value, "");
	static_assert(!std::is_nothrow_constructible<hamon::span<T, 0>, T(&)[2]>::value, "");
	static_assert(!std::is_nothrow_constructible<hamon::span<T, 1>, T(&)[2]>::value, "");
	static_assert( std::is_nothrow_constructible<hamon::span<T, 2>, T(&)[2]>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T>   , T(&)[2]>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 0>, T(&)[2]>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 1>, T(&)[2]>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T, 2>, T(&)[2]>::value, "");
	T arr[3] {};
	hamon::span<T>    s1{arr};
	hamon::span<T, 3> s2{arr};
	return
		s1.data() == &arr[0] && s1.size() == 3 &&
		s2.data() == &arr[0] && s2.size() == 3;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test()
{
	return
		test2<T      >() &&
		test2<T const>() &&
		cv_test<T>();
}

struct A{};

GTEST_TEST(SpanTest, CtorArrayTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_array_test

}	// namespace hamon_span_test
