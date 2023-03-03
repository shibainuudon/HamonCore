/**
 *	@file	unit_test_type_traits_unwrap_ref_decay.cpp
 *
 *	@brief	unwrap_ref_decay のテスト
 */

#include <hamon/type_traits/unwrap_ref_decay.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/functional/reference_wrapper.hpp>
#include <gtest/gtest.h>

namespace hamon_type_traits_test
{

namespace unwrap_ref_decay_test
{

#define HAMON_UNWRAP_REF_DECAY_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::unwrap_ref_decay<T1>::type, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::unwrap_ref_decay_t<T1>, T2>::value, "")

HAMON_UNWRAP_REF_DECAY_TEST(int,   int);
HAMON_UNWRAP_REF_DECAY_TEST(int&,  int);
HAMON_UNWRAP_REF_DECAY_TEST(int&&, int);
HAMON_UNWRAP_REF_DECAY_TEST(int*,  int*);
HAMON_UNWRAP_REF_DECAY_TEST(int const,   int);
HAMON_UNWRAP_REF_DECAY_TEST(int const&,  int);
HAMON_UNWRAP_REF_DECAY_TEST(int const&&, int);
HAMON_UNWRAP_REF_DECAY_TEST(int const*,  int const*);

HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int>,   int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int&>,  int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int&&>, int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int*>,  int*&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int const>,   int const&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int const&>,  int const&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int const&&>, int const&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int const*>,  int const*&);

HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int> const,          int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int>       volatile, int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int> const volatile, int&);

HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int>&,  int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int>&&, int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int>*,  hamon::reference_wrapper<int>*);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int> const&,  int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int> const&&, int&);
HAMON_UNWRAP_REF_DECAY_TEST(hamon::reference_wrapper<int> const*,  hamon::reference_wrapper<int> const*);

#undef HAMON_UNWRAP_REF_DECAY_TEST

}	// namespace unwrap_ref_decay_test

}	// namespace hamon_type_traits_test
