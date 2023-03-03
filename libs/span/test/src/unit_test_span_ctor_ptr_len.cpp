/**
 *	@file	unit_test_span_ctor_ptr_len.cpp
 *
 *	@brief	span::span(pointer ptr, index_type count) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <string>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace ctor_ptr_len_test
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
cv_test()
{
//	constexpr bool b = !hamon::is_class<T>::value;
	static_assert(     std::is_constructible<hamon::span<T               >, T               *, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T               >, T const         *, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T               >, T       volatile*, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T               >, T const volatile*, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T const         >, T               *, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T const         >, T const         *, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T const         >, T       volatile*, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T const         >, T const volatile*, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T       volatile>, T               *, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T       volatile>, T const         *, std::size_t>::value, "");
//	static_assert(b == std::is_constructible<hamon::span<T       volatile>, T       volatile*, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T       volatile>, T const volatile*, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T const volatile>, T               *, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T const volatile>, T const         *, std::size_t>::value, "");
//	static_assert(b == std::is_constructible<hamon::span<T const volatile>, T       volatile*, std::size_t>::value, "");
//	static_assert(b == std::is_constructible<hamon::span<T const volatile>, T const volatile*, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T               , 0>, T               *, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T               , 0>, T const         *, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T               , 0>, T       volatile*, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T               , 0>, T const volatile*, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T const         , 0>, T               *, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T const         , 0>, T const         *, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T const         , 0>, T       volatile*, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T const         , 0>, T const volatile*, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T       volatile, 0>, T               *, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T       volatile, 0>, T const         *, std::size_t>::value, "");
//	static_assert(b == std::is_constructible<hamon::span<T       volatile, 0>, T       volatile*, std::size_t>::value, "");
	static_assert(    !std::is_constructible<hamon::span<T       volatile, 0>, T const volatile*, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T const volatile, 0>, T               *, std::size_t>::value, "");
	static_assert(     std::is_constructible<hamon::span<T const volatile, 0>, T const         *, std::size_t>::value, "");
//	static_assert(b == std::is_constructible<hamon::span<T const volatile, 0>, T       volatile*, std::size_t>::value, "");
//	static_assert(b == std::is_constructible<hamon::span<T const volatile, 0>, T const volatile*, std::size_t>::value, "");

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test2()
{
	static_assert( std::is_constructible<hamon::span<T>   , T*, std::size_t>::value, "");
	static_assert( std::is_constructible<hamon::span<T, 0>, T*, std::size_t>::value, "");
	static_assert( std::is_constructible<hamon::span<T, 1>, T*, std::size_t>::value, "");
	static_assert( std::is_constructible<hamon::span<T, 2>, T*, std::size_t>::value, "");
	static_assert( std::is_nothrow_constructible<hamon::span<T>   , T*, std::size_t>::value, "");
	static_assert( std::is_nothrow_constructible<hamon::span<T, 0>, T*, std::size_t>::value, "");
	static_assert( std::is_nothrow_constructible<hamon::span<T, 1>, T*, std::size_t>::value, "");
	static_assert( std::is_nothrow_constructible<hamon::span<T, 2>, T*, std::size_t>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T>   , T*, std::size_t>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 0>, T*, std::size_t>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 1>, T*, std::size_t>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 2>, T*, std::size_t>::value, "");
	T arr[4] {};
	hamon::span<T>    s1{arr, 3};
	hamon::span<T, 4> s2{arr, 4};
	return
		s1.data() == &arr[0] && s1.size() == 3 &&
		s2.data() == &arr[0] && s2.size() == 4;
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

GTEST_TEST(SpanTest, CtorPtrLenTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_ptr_len_test

}	// namespace hamon_span_test
