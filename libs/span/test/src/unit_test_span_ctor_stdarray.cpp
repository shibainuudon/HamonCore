/**
 *	@file	unit_test_span_ctor_stdarray.cpp
 *
 *	@brief	span::span(array<value_type, N>& arr) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <gtest/gtest.h>
#include <array>
#include <string>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace ctor_stdarray_test
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
cv_test()
{
	static_assert( hamon::is_constructible<hamon::span<T               >, std::array<T, 2>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, std::array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, std::array<T, 2>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, std::array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, std::array<T, 2>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, std::array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, std::array<T, 2>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, std::array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T               >, std::array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, std::array<T, 3> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, std::array<T, 3>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, std::array<T, 3> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, std::array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, std::array<T, 3> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, std::array<T, 3>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, std::array<T, 3> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T               , 2>, std::array<T, 2>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 2>, std::array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 2>, std::array<T, 2>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 2>, std::array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile, 2>, std::array<T, 2>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 2>, std::array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 2>, std::array<T, 2>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 2>, std::array<T, 2> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 2>, std::array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 2>, std::array<T, 3> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 2>, std::array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 2>, std::array<T, 3> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 2>, std::array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 2>, std::array<T, 3> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const volatile, 2>, std::array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const volatile, 2>, std::array<T, 3> const&>::value, "");

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test2()
{
	using U = hamon::remove_cv_t<T>;
	static_assert( hamon::is_constructible<hamon::span<T>   , std::array<U, 2>&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T, 0>, std::array<U, 2>&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T, 1>, std::array<U, 2>&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 2>, std::array<U, 2>&>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T>   , std::array<U, 2>&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::span<T, 0>, std::array<U, 2>&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::span<T, 1>, std::array<U, 2>&>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 2>, std::array<U, 2>&>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T>   , std::array<U, 2>&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 0>, std::array<U, 2>&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 1>, std::array<U, 2>&>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T, 2>, std::array<U, 2>&>::value, "");
	std::array<U, 3>       arr{};
	std::array<U, 4> const carr{};
	hamon::span<U>          s1{arr};
	hamon::span<U const, 4> s2{carr};
	return
		s1.data() == &arr[0]  && s1.size() == 3 &&
		s2.data() == &carr[0] && s2.size() == 4;
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

GTEST_TEST(SpanTest, CtorStdArrayTest)
{
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE((test<long>()));
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE((test<double>()));
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_stdarray_test

}	// namespace hamon_span_test
