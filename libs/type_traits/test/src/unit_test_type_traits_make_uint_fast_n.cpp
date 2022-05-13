/**
 *	@file	unit_test_type_traits_make_uint_fast_n.cpp
 *
 *	@brief	make_uint_fast_n のテスト
 */

#include <hamon/type_traits/make_uint_fast_n.hpp>
#include <type_traits>

static_assert(std::is_unsigned<hamon::make_uint_fast_n_t< 0>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t< 1>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t< 7>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t< 8>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t< 9>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t<15>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t<16>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t<17>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t<31>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t<32>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t<33>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t<63>>::value, "");
static_assert(std::is_unsigned<hamon::make_uint_fast_n_t<64>>::value, "");

static_assert(sizeof(hamon::make_uint_fast_n_t< 0>) >= 1, "");
static_assert(sizeof(hamon::make_uint_fast_n_t< 1>) >= 1, "");
static_assert(sizeof(hamon::make_uint_fast_n_t< 7>) >= 1, "");
static_assert(sizeof(hamon::make_uint_fast_n_t< 8>) >= 1, "");
static_assert(sizeof(hamon::make_uint_fast_n_t< 9>) >= 2, "");
static_assert(sizeof(hamon::make_uint_fast_n_t<15>) >= 2, "");
static_assert(sizeof(hamon::make_uint_fast_n_t<16>) >= 2, "");
static_assert(sizeof(hamon::make_uint_fast_n_t<17>) >= 4, "");
static_assert(sizeof(hamon::make_uint_fast_n_t<31>) >= 4, "");
static_assert(sizeof(hamon::make_uint_fast_n_t<32>) >= 4, "");
static_assert(sizeof(hamon::make_uint_fast_n_t<33>) >= 8, "");
static_assert(sizeof(hamon::make_uint_fast_n_t<63>) >= 8, "");
static_assert(sizeof(hamon::make_uint_fast_n_t<64>) >= 8, "");
