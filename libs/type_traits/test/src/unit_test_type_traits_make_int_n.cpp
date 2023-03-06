/**
 *	@file	unit_test_type_traits_make_int_n.cpp
 *
 *	@brief	make_int_n のテスト
 */

#include <hamon/type_traits/make_int_n.hpp>
#include <hamon/type_traits/is_signed.hpp>

static_assert(hamon::is_signed<hamon::make_int_n_t< 8>>::value, "");
static_assert(hamon::is_signed<hamon::make_int_n_t<16>>::value, "");
static_assert(hamon::is_signed<hamon::make_int_n_t<32>>::value, "");
static_assert(hamon::is_signed<hamon::make_int_n_t<64>>::value, "");

static_assert(sizeof(hamon::make_int_n_t< 8>) == 1, "");
static_assert(sizeof(hamon::make_int_n_t<16>) == 2, "");
static_assert(sizeof(hamon::make_int_n_t<32>) == 4, "");
static_assert(sizeof(hamon::make_int_n_t<64>) == 8, "");
