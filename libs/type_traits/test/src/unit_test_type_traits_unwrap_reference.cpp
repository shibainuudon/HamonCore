/**
 *	@file	unit_test_type_traits_unwrap_reference.cpp
 *
 *	@brief	unwrap_reference のテスト
 */

#include <hamon/type_traits/unwrap_reference.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/functional/reference_wrapper.hpp>
#include <gtest/gtest.h>

namespace hamon_type_traits_test
{

namespace unwrap_reference_test
{

#define HAMON_UNWRAP_REFERENCE_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::unwrap_reference<T1>::type, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::unwrap_reference_t<T1>, T2>::value, "")

HAMON_UNWRAP_REFERENCE_TEST(int,   int);
HAMON_UNWRAP_REFERENCE_TEST(int&,  int&);
HAMON_UNWRAP_REFERENCE_TEST(int&&, int&&);
HAMON_UNWRAP_REFERENCE_TEST(int*,  int*);
HAMON_UNWRAP_REFERENCE_TEST(int const,   int const);
HAMON_UNWRAP_REFERENCE_TEST(int const&,  int const&);
HAMON_UNWRAP_REFERENCE_TEST(int const&&, int const&&);
HAMON_UNWRAP_REFERENCE_TEST(int const*,  int const*);

HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int>,   int&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int&>,  int&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int&&>, int&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int*>,  int*&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int const>,   int const&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int const&>,  int const&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int const&&>, int const&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int const*>,  int const*&);

HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int> const, hamon::reference_wrapper<int> const);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int> volatile, hamon::reference_wrapper<int> volatile);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int> const volatile, hamon::reference_wrapper<int> const volatile);

HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int>&,  hamon::reference_wrapper<int>&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int>&&, hamon::reference_wrapper<int>&&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int>*,  hamon::reference_wrapper<int>*);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int> const&,  hamon::reference_wrapper<int> const&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int> const&&, hamon::reference_wrapper<int> const&&);
HAMON_UNWRAP_REFERENCE_TEST(hamon::reference_wrapper<int> const*,  hamon::reference_wrapper<int> const*);

#undef HAMON_UNWRAP_REFERENCE_TEST

}	// namespace unwrap_reference_test

}	// namespace hamon_type_traits_test
