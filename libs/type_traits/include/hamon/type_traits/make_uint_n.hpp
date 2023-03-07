/**
 *	@file	make_uint_n.hpp
 *
 *	@brief	make_uint_n
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_UINT_N_HPP
#define HAMON_TYPE_TRAITS_MAKE_UINT_N_HPP

#include <hamon/cstddef/size_t.hpp>
#include <cstdint>

namespace hamon
{

template <hamon::size_t N>
struct make_uint_n;

template <> struct make_uint_n< 8> { using type = std::uint8_t; };
template <> struct make_uint_n<16> { using type = std::uint16_t; };
template <> struct make_uint_n<32> { using type = std::uint32_t; };
template <> struct make_uint_n<64> { using type = std::uint64_t; };

template <hamon::size_t N>
using make_uint_n_t = typename make_uint_n<N>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_UINT_N_HPP
