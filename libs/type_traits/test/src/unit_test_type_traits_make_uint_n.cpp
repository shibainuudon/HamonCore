/**
 *	@file	unit_test_type_traits_make_uint_n.cpp
 *
 *	@brief	make_uint_n のテスト
 */

#include <hamon/type_traits/make_uint_n.hpp>
#include <type_traits>

static_assert(std::is_unsigned<hamon::make_uint_n_t< 8>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_n_t<16>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_n_t<32>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_n_t<64>>::value, "");

static_assert(sizeof(hamon::make_uint_n_t< 8>) == 1, "");
static_assert(sizeof(hamon::make_uint_n_t<16>) == 2, "");
static_assert(sizeof(hamon::make_uint_n_t<32>) == 4, "");
static_assert(sizeof(hamon::make_uint_n_t<64>) == 8, "");
