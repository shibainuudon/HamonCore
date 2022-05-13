/**
 *	@file	make_uint_fast_n.hpp
 *
 *	@brief	make_uint_fast_n
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_UINT_FAST_N_HPP
#define HAMON_TYPE_TRAITS_MAKE_UINT_FAST_N_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace hamon
{

template <std::size_t N>
struct make_uint_fast_n
{
private:
	struct incomplete;
public:
	using type =
		typename std::conditional<N <=  8, std::uint_fast8_t,
		typename std::conditional<N <= 16, std::uint_fast16_t,
		typename std::conditional<N <= 32, std::uint_fast32_t,
		typename std::conditional<N <= 64, std::uint_fast64_t,
		incomplete
	>::type>::type>::type>::type;
};

template <std::size_t N>
using make_uint_fast_n_t = typename make_uint_fast_n<N>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_UINT_FAST_N_HPP
