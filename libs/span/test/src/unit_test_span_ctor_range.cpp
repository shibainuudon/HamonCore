/**
 *	@file	unit_test_span_ctor_range.cpp
 *
 *	@brief	span::span(Range&&) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace ctor_range_test
{

template <typename T>
struct MyRange
{
	HAMON_CXX14_CONSTEXPR MyRange() : m_value{} {}
	HAMON_CXX14_CONSTEXPR hamon::size_t size() const noexcept { return 1; }
	HAMON_CXX14_CONSTEXPR T      * data()        noexcept { return &m_value; }
	HAMON_CXX14_CONSTEXPR T const* data()  const noexcept { return &m_value; }
	HAMON_CXX14_CONSTEXPR T      * begin()       noexcept { return &m_value; }
	HAMON_CXX14_CONSTEXPR T const* begin() const noexcept { return &m_value; }
	HAMON_CXX14_CONSTEXPR T      * end()         noexcept { return &m_value + 1; }
	HAMON_CXX14_CONSTEXPR T const* end()   const noexcept { return &m_value + 1; }

	HAMON_CXX14_CONSTEXPR T const* getV() const noexcept { return &m_value; } // for checking
	T m_value;
};

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool cv_test()
{
	static_assert(!hamon::is_constructible<hamon::span<T               >, MyRange<T>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, MyRange<T>>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, MyRange<T>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, MyRange<T>>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T               >, MyRange<T>&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, MyRange<T>&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T       volatile>, MyRange<T>&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, MyRange<T>&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, MyRange<T>&&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, MyRange<T>&&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, MyRange<T>&&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, MyRange<T>&&>::value, "");

	static_assert(!hamon::is_constructible<hamon::span<T               >, MyRange<T> const>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, MyRange<T> const>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, MyRange<T> const>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, MyRange<T> const>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, MyRange<T> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, MyRange<T> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, MyRange<T> const&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, MyRange<T> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T               >, MyRange<T> const&&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const         >, MyRange<T> const&&>::value, "");
	static_assert(!hamon::is_constructible<hamon::span<T       volatile>, MyRange<T> const&&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T const volatile>, MyRange<T> const&&>::value, "");

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool test2()
{
	static_assert( hamon::is_constructible<hamon::span<T>   , MyRange<T>&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 0>, MyRange<T>&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 1>, MyRange<T>&>::value, "");
	static_assert( hamon::is_constructible<hamon::span<T, 2>, MyRange<T>&>::value, "");
#if 0
	static_assert( hamon::is_nothrow_constructible<hamon::span<T>   , MyRange<T>&>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 0>, MyRange<T>&>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 1>, MyRange<T>&>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::span<T, 2>, MyRange<T>&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<hamon::span<T>   , MyRange<T>&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 0>, MyRange<T>&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 1>, MyRange<T>&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::span<T, 2>, MyRange<T>&>::value, "");

	MyRange<T>       val1{};
	MyRange<T> const val2{};
	hamon::span<T>          s1{ val1 };
	hamon::span<T, 1>       s2{ val1 };
	hamon::span<T const>    s3{ val2 };
	hamon::span<T const, 1> s4{ val2 };
	return
		s1.data() == val1.getV() && s1.size() == 1 &&
		s2.data() == val1.getV() && s2.size() == 1 &&
		s3.data() == val2.getV() && s3.size() == 1 &&
		s4.data() == val2.getV() && s4.size() == 1;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool test()
{
	return
		test2<T>() &&
		cv_test<T>();
}

struct A {};

GTEST_TEST(SpanTest, CtorRangeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_range_test

}	// namespace hamon_span_test
