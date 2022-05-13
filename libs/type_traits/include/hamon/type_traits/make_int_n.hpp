/**
 *	@file	make_int_n.hpp
 *
 *	@brief	make_int_n
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_INT_N_HPP
#define HAMON_TYPE_TRAITS_MAKE_INT_N_HPP

#include <cstddef>
#include <cstdint>

namespace hamon
{

template <std::size_t N>
struct make_int_n;

template <> struct make_int_n< 8> { using type = std::int8_t; };
template <> struct make_int_n<16> { using type = std::int16_t; };
template <> struct make_int_n<32> { using type = std::int32_t; };
template <> struct make_int_n<64> { using type = std::int64_t; };

template <std::size_t N>
using make_int_n_t = typename make_int_n<N>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_INT_N_HPP
