/**
 *	@file	unit_test_cstdint.cpp
 *
 *	@brief	cstdint のテスト
 */

#include <hamon/cstdint.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/is_integral.hpp>

static_assert(sizeof(hamon::intmax_t)		>= 8, "");
static_assert(sizeof(hamon::int8_t)			== 1, "");
static_assert(sizeof(hamon::int16_t)		== 2, "");
static_assert(sizeof(hamon::int32_t)		== 4, "");
static_assert(sizeof(hamon::int64_t)		== 8, "");
static_assert(sizeof(hamon::int_least8_t)	>= 1, "");
static_assert(sizeof(hamon::int_least16_t)	>= 2, "");
static_assert(sizeof(hamon::int_least32_t)	>= 4, "");
static_assert(sizeof(hamon::int_least64_t)	>= 8, "");
static_assert(sizeof(hamon::int_fast8_t)	>= 1, "");
static_assert(sizeof(hamon::int_fast16_t)	>= 2, "");
static_assert(sizeof(hamon::int_fast32_t)	>= 4, "");
static_assert(sizeof(hamon::int_fast64_t)	>= 8, "");
static_assert(sizeof(hamon::intptr_t)		>= sizeof(void*), "");
static_assert(sizeof(hamon::uintmax_t)		>= 8, "");
static_assert(sizeof(hamon::uint8_t)		== 1, "");
static_assert(sizeof(hamon::uint16_t)		== 2, "");
static_assert(sizeof(hamon::uint32_t)		== 4, "");
static_assert(sizeof(hamon::uint64_t)		== 8, "");
static_assert(sizeof(hamon::uint_least8_t)	>= 1, "");
static_assert(sizeof(hamon::uint_least16_t)	>= 2, "");
static_assert(sizeof(hamon::uint_least32_t)	>= 4, "");
static_assert(sizeof(hamon::uint_least64_t)	>= 8, "");
static_assert(sizeof(hamon::uint_fast8_t)	>= 1, "");
static_assert(sizeof(hamon::uint_fast16_t)	>= 2, "");
static_assert(sizeof(hamon::uint_fast32_t)	>= 4, "");
static_assert(sizeof(hamon::uint_fast64_t)	>= 8, "");
static_assert(sizeof(hamon::uintptr_t)		>= sizeof(void*), "");

static_assert(hamon::is_signed<hamon::intmax_t			>::value, "");
static_assert(hamon::is_signed<hamon::int8_t			>::value, "");
static_assert(hamon::is_signed<hamon::int16_t			>::value, "");
static_assert(hamon::is_signed<hamon::int32_t			>::value, "");
static_assert(hamon::is_signed<hamon::int64_t			>::value, "");
static_assert(hamon::is_signed<hamon::int_least8_t		>::value, "");
static_assert(hamon::is_signed<hamon::int_least16_t		>::value, "");
static_assert(hamon::is_signed<hamon::int_least32_t		>::value, "");
static_assert(hamon::is_signed<hamon::int_least64_t		>::value, "");
static_assert(hamon::is_signed<hamon::int_fast8_t		>::value, "");
static_assert(hamon::is_signed<hamon::int_fast16_t		>::value, "");
static_assert(hamon::is_signed<hamon::int_fast32_t		>::value, "");
static_assert(hamon::is_signed<hamon::int_fast64_t		>::value, "");
static_assert(hamon::is_signed<hamon::intptr_t			>::value, "");
static_assert(hamon::is_unsigned<hamon::uintmax_t		>::value, "");
static_assert(hamon::is_unsigned<hamon::uint8_t			>::value, "");
static_assert(hamon::is_unsigned<hamon::uint16_t		>::value, "");
static_assert(hamon::is_unsigned<hamon::uint32_t		>::value, "");
static_assert(hamon::is_unsigned<hamon::uint64_t		>::value, "");
static_assert(hamon::is_unsigned<hamon::uint_least8_t	>::value, "");
static_assert(hamon::is_unsigned<hamon::uint_least16_t	>::value, "");
static_assert(hamon::is_unsigned<hamon::uint_least32_t	>::value, "");
static_assert(hamon::is_unsigned<hamon::uint_least64_t	>::value, "");
static_assert(hamon::is_unsigned<hamon::uint_fast8_t	>::value, "");
static_assert(hamon::is_unsigned<hamon::uint_fast16_t	>::value, "");
static_assert(hamon::is_unsigned<hamon::uint_fast32_t	>::value, "");
static_assert(hamon::is_unsigned<hamon::uint_fast64_t	>::value, "");
static_assert(hamon::is_unsigned<hamon::uintptr_t		>::value, "");

static_assert(hamon::is_integral<hamon::intmax_t		>::value, "");
static_assert(hamon::is_integral<hamon::int8_t			>::value, "");
static_assert(hamon::is_integral<hamon::int16_t			>::value, "");
static_assert(hamon::is_integral<hamon::int32_t			>::value, "");
static_assert(hamon::is_integral<hamon::int64_t			>::value, "");
static_assert(hamon::is_integral<hamon::int_least8_t	>::value, "");
static_assert(hamon::is_integral<hamon::int_least16_t	>::value, "");
static_assert(hamon::is_integral<hamon::int_least32_t	>::value, "");
static_assert(hamon::is_integral<hamon::int_least64_t	>::value, "");
static_assert(hamon::is_integral<hamon::int_fast8_t		>::value, "");
static_assert(hamon::is_integral<hamon::int_fast16_t	>::value, "");
static_assert(hamon::is_integral<hamon::int_fast32_t	>::value, "");
static_assert(hamon::is_integral<hamon::int_fast64_t	>::value, "");
static_assert(hamon::is_integral<hamon::intptr_t		>::value, "");
static_assert(hamon::is_integral<hamon::uintmax_t		>::value, "");
static_assert(hamon::is_integral<hamon::uint8_t			>::value, "");
static_assert(hamon::is_integral<hamon::uint16_t		>::value, "");
static_assert(hamon::is_integral<hamon::uint32_t		>::value, "");
static_assert(hamon::is_integral<hamon::uint64_t		>::value, "");
static_assert(hamon::is_integral<hamon::uint_least8_t	>::value, "");
static_assert(hamon::is_integral<hamon::uint_least16_t	>::value, "");
static_assert(hamon::is_integral<hamon::uint_least32_t	>::value, "");
static_assert(hamon::is_integral<hamon::uint_least64_t	>::value, "");
static_assert(hamon::is_integral<hamon::uint_fast8_t	>::value, "");
static_assert(hamon::is_integral<hamon::uint_fast16_t	>::value, "");
static_assert(hamon::is_integral<hamon::uint_fast32_t	>::value, "");
static_assert(hamon::is_integral<hamon::uint_fast64_t	>::value, "");
static_assert(hamon::is_integral<hamon::uintptr_t		>::value, "");
