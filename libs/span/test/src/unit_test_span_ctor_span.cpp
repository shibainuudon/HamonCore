/**
 *	@file	unit_test_span_ctor_span.cpp
 *
 *	@brief	span::span(const span<OtherElementType, OtherExtent>&) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace ctor_span_test
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool cv_test()
{
	static_assert( hamon::is_constructible<hamon::span<T               >, hamon::span<T               >>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, hamon::span<T const         >>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, hamon::span<T       volatile>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, hamon::span<T const volatile>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, hamon::span<T               >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, hamon::span<T const         >>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         >, hamon::span<T       volatile>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         >, hamon::span<T const volatile>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, hamon::span<T               >>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, hamon::span<T const         >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, hamon::span<T       volatile>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, hamon::span<T const volatile>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, hamon::span<T               >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, hamon::span<T const         >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, hamon::span<T       volatile>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, hamon::span<T const volatile>>::value, "");

	static_assert( hamon::is_constructible<hamon::span<T               >, hamon::span<T               , 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, hamon::span<T const         , 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, hamon::span<T       volatile, 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, hamon::span<T const volatile, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, hamon::span<T               , 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, hamon::span<T const         , 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         >, hamon::span<T       volatile, 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         >, hamon::span<T const volatile, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, hamon::span<T               , 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, hamon::span<T const         , 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, hamon::span<T       volatile, 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, hamon::span<T const volatile, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, hamon::span<T               , 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, hamon::span<T const         , 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, hamon::span<T       volatile, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, hamon::span<T const volatile, 0>>::value, "");

	static_assert( hamon::is_constructible<hamon::span<T               , 0>, hamon::span<T               >>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, hamon::span<T const         >>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, hamon::span<T       volatile>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, hamon::span<T const volatile>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 0>, hamon::span<T               >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 0>, hamon::span<T const         >>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 0>, hamon::span<T       volatile>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 0>, hamon::span<T const volatile>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile, 0>, hamon::span<T               >>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 0>, hamon::span<T const         >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile, 0>, hamon::span<T       volatile>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 0>, hamon::span<T const volatile>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, hamon::span<T               >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, hamon::span<T const         >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, hamon::span<T       volatile>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, hamon::span<T const volatile>>::value, "");

	static_assert( hamon::is_constructible<hamon::span<T               , 0>, hamon::span<T               , 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, hamon::span<T const         , 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, hamon::span<T       volatile, 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 0>, hamon::span<T const volatile, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 0>, hamon::span<T               , 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 0>, hamon::span<T const         , 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 0>, hamon::span<T       volatile, 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 0>, hamon::span<T const volatile, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile, 0>, hamon::span<T               , 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 0>, hamon::span<T const         , 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile, 0>, hamon::span<T       volatile, 0>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 0>, hamon::span<T const volatile, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, hamon::span<T               , 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, hamon::span<T const         , 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, hamon::span<T       volatile, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 0>, hamon::span<T const volatile, 0>>::value, "");

	static_assert(!hamon::is_constructible<hamon::span<T               , 1>, hamon::span<T               , 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 1>, hamon::span<T const         , 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 1>, hamon::span<T       volatile, 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 1>, hamon::span<T const volatile, 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 1>, hamon::span<T               , 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 1>, hamon::span<T const         , 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 1>, hamon::span<T       volatile, 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 1>, hamon::span<T const volatile, 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 1>, hamon::span<T               , 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 1>, hamon::span<T const         , 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 1>, hamon::span<T       volatile, 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 1>, hamon::span<T const volatile, 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const volatile, 1>, hamon::span<T               , 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const volatile, 1>, hamon::span<T const         , 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const volatile, 1>, hamon::span<T       volatile, 2>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const volatile, 1>, hamon::span<T const volatile, 2>>::value, "");

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool test2()
{
	static_assert( hamon::is_constructible<hamon::span<T>   , hamon::span<T   >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T>   , hamon::span<T, 0>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 0>, hamon::span<T   >>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 0>, hamon::span<T, 0>>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T>   , hamon::span<T   >>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T>   , hamon::span<T, 0>>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 0>, hamon::span<T   >>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 0>, hamon::span<T, 0>>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T>   , hamon::span<T   >>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T>   , hamon::span<T, 0>>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 0>, hamon::span<T   >>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T, 0>, hamon::span<T, 0>>::value, "");

	hamon::span<T>    s0{};
	hamon::span<T, 0> s1{ s0 };
	hamon::span<T>    s2{ s1 };

	T arr[3] {};
	hamon::span<T>    s3{arr, 3};
	hamon::span<T, 3> s4{s3};
	hamon::span<T>    s5{s4};

	return
		s1.data() == nullptr && s1.size() == 0 &&
		s2.data() == nullptr && s2.size() == 0 &&
		s3.data() == &arr[0] && s3.size() == 3 &&
		s4.data() == &arr[0] && s4.size() == 3;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool test()
{
	return
		test2<T      >() &&
		test2<T const>() &&
		cv_test<T>();
}

struct A{};

GTEST_TEST(SpanTest, CtorSpanTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<hamon::string>()));
}

}	// namespace ctor_span_test

}	// namespace hamon_span_test
