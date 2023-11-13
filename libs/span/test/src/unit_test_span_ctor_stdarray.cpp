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
#include <hamon/array.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace ctor_stdarray_test
{

template <template <typename, hamon::size_t> class Array, typename T>
inline HAMON_CXX14_CONSTEXPR bool
cv_test()
{
	static_assert( hamon::is_constructible<hamon::span<T               >, Array<T, 2>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, Array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, Array<T, 2>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, Array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, Array<T, 2>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, Array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, Array<T, 2>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, Array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T               >, Array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, Array<T, 3> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, Array<T, 3>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, Array<T, 3> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, Array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, Array<T, 3> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, Array<T, 3>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, Array<T, 3> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T               , 2>, Array<T, 2>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 2>, Array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 2>, Array<T, 2>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         , 2>, Array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile, 2>, Array<T, 2>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 2>, Array<T, 2> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 2>, Array<T, 2>      &>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile, 2>, Array<T, 2> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 2>, Array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               , 2>, Array<T, 3> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 2>, Array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const         , 2>, Array<T, 3> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 2>, Array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile, 2>, Array<T, 3> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const volatile, 2>, Array<T, 3>      &>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T const volatile, 2>, Array<T, 3> const&>::value, "");

	return true;
}

template <template <typename, hamon::size_t> class Array, typename T>
inline HAMON_CXX14_CONSTEXPR bool
test2()
{
	using U = hamon::remove_cv_t<T>;
	static_assert( hamon::is_constructible<hamon::span<T>   , Array<U, 2>&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T, 0>, Array<U, 2>&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T, 1>, Array<U, 2>&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 2>, Array<U, 2>&>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T>   , Array<U, 2>&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::span<T, 0>, Array<U, 2>&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::span<T, 1>, Array<U, 2>&>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 2>, Array<U, 2>&>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T>   , Array<U, 2>&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 0>, Array<U, 2>&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 1>, Array<U, 2>&>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::span<T, 2>, Array<U, 2>&>::value, "");
	Array<U, 3>       arr{};
	Array<U, 4> const carr{};
	hamon::span<U>          s1{arr};
	hamon::span<U const, 4> s2{carr};
	return
		s1.data() == &arr[0]  && s1.size() == 3 &&
		s2.data() == &carr[0] && s2.size() == 4;
}

template <template <typename, hamon::size_t> class Array, typename T>
inline HAMON_CXX14_CONSTEXPR bool
test()
{
	return test2<Array, T>() && test2<Array, T const>();
}

struct A{};

GTEST_TEST(SpanTest, CtorStdArrayTest)
{
	cv_test<std::array, int>();
	cv_test<std::array, long>();
	cv_test<std::array, double>();

	cv_test<hamon::array, int>();
	cv_test<hamon::array, long>();
	cv_test<hamon::array, double>();

	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE((test<std::array, int>()));
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE((test<std::array, long>()));
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE((test<std::array, double>()));
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE((test<std::array, A>()));
	                      EXPECT_TRUE((test<std::array, hamon::string>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<hamon::array, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<hamon::array, long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<hamon::array, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<hamon::array, A>()));
	                      EXPECT_TRUE((test<hamon::array, hamon::string>()));
}

}	// namespace ctor_stdarray_test

}	// namespace hamon_span_test
