/**
 *	@file	make_uint_n.hpp
 *
 *	@brief	make_uint_n
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_UINT_N_HPP
#define HAMON_TYPE_TRAITS_MAKE_UINT_N_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint8_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>

namespace hamon
{

template <hamon::size_t N>
struct make_uint_n;

template <> struct make_uint_n< 8> { using type = hamon::uint8_t; };
template <> struct make_uint_n<16> { using type = hamon::uint16_t; };
template <> struct make_uint_n<32> { using type = hamon::uint32_t; };
template <> struct make_uint_n<64> { using type = hamon::uint64_t; };

template <hamon::size_t N>
using make_uint_n_t = typename make_uint_n<N>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_UINT_N_HPP
