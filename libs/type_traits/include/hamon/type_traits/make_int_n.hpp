/**
 *	@file	make_int_n.hpp
 *
 *	@brief	make_int_n
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_INT_N_HPP
#define HAMON_TYPE_TRAITS_MAKE_INT_N_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/int8_t.hpp>
#include <hamon/cstdint/int16_t.hpp>
#include <hamon/cstdint/int32_t.hpp>
#include <hamon/cstdint/int64_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <hamon::size_t N>
struct make_int_n;

template <> struct make_int_n< 8> { using type = hamon::int8_t; };
template <> struct make_int_n<16> { using type = hamon::int16_t; };
template <> struct make_int_n<32> { using type = hamon::int32_t; };
template <> struct make_int_n<64> { using type = hamon::int64_t; };

#if defined(HAMON_HAS_INT128)
template <> struct make_int_n<128> { using type = __int128_t; };
#endif

template <hamon::size_t N>
using make_int_n_t = typename make_int_n<N>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_INT_N_HPP
