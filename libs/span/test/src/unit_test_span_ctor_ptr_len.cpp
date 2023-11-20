/**
 *	@file	unit_test_span_ctor_ptr_len.cpp
 *
 *	@brief	span::span(pointer ptr, index_type count) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace ctor_ptr_len_test
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
cv_test()
{
	static_assert( hamon::is_constructible<hamon::span<T               >, T               *, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, T const         *, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, T       volatile*, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, T const volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, T               *, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, T const         *, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         >, T       volatile*, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         >, T const volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, T               *, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, T const         *, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, T       volatile*, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, T const volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, T               *, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, T const         *, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, T       volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, T const volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T               , 0>, T               *, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, T const         *, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, T       volatile*, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, T const volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 0>, T               *, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 0>, T const         *, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 0>, T       volatile*, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 0>, T const volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile, 0>, T               *, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 0>, T const         *, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile, 0>, T       volatile*, hamon::size_t>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 0>, T const volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, T               *, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, T const         *, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, T       volatile*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, T const volatile*, hamon::size_t>::value, "");
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test2()
{
	static_assert( hamon::is_constructible<hamon::span<T>   , T*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 0>, T*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 1>, T*, hamon::size_t>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 2>, T*, hamon::size_t>::value, "");
#if !defined(HAMON_USE_STD_SPAN)
	static_assert( hamon::is_nothrow_constructible<hamon::span<T>   , T*, hamon::size_t>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 0>, T*, hamon::size_t>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 1>, T*, hamon::size_t>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 2>, T*, hamon::size_t>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<hamon::span<T>   , T*, hamon::size_t>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 0>, T*, hamon::size_t>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 1>, T*, hamon::size_t>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 2>, T*, hamon::size_t>::value, "");
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
	return test2<T>() && test2<T const>();
}

struct A{};

GTEST_TEST(SpanTest, CtorPtrLenTest)
{
	cv_test<int>();
	cv_test<long>();
	cv_test<double>();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<hamon::string>()));
}

}	// namespace ctor_ptr_len_test

}	// namespace hamon_span_test
