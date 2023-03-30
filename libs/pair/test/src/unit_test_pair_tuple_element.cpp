/**
 *	@file	unit_test_pair_tuple_element.cpp
 *
 *	@brief	tuple_element のテスト
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace tuple_element_test
{

static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<int, float>>,
	int>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<int, float> const>,
	int const>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<int, float> volatile>,
	int volatile>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<int, float> const volatile>,
	int const volatile>::value, "");

static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<int, float>>,
	float>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<int, float> const>,
	float const>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<int, float> volatile>,
	float volatile>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<int, float> const volatile>,
	float const volatile>::value, "");

static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<long&, char*>>,
	long&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<long&, char*> const>,
	long&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<long&, char*> volatile>,
	long&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<long&, char*> const volatile>,
	long&>::value, "");

static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<long&, char*>>,
	char*>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<long&, char*> const>,
	char* const>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<long&, char*> volatile>,
	char* volatile>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<long&, char*> const volatile>,
	char* const volatile>::value, "");

static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<int const&, int const&&>>,
	int const&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<int const&, int const&&> const>,
	int const&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<int const&, int const&&> volatile>,
	int const&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<0, hamon::pair<int const&, int const&&> const volatile>,
	int const&>::value, "");

static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<int const&, int const&&>>,
	int const&&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<int const&, int const&&> const>,
	int const&&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<int const&, int const&&> volatile>,
	int const&&>::value, "");
static_assert(hamon::is_same<
	hamon::tuple_element_t<1, hamon::pair<int const&, int const&&> const volatile>,
	int const&&>::value, "");

}	// namespace tuple_element_test

}	// namespace hamon_pair_test
