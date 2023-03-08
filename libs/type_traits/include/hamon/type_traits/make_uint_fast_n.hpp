﻿/**
 *	@file	make_uint_fast_n.hpp
 *
 *	@brief	make_uint_fast_n
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_UINT_FAST_N_HPP
#define HAMON_TYPE_TRAITS_MAKE_UINT_FAST_N_HPP

#include <hamon/type_traits/conditional.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint.hpp>

namespace hamon
{

template <hamon::size_t N>
struct make_uint_fast_n
{
private:
	struct incomplete;
public:
	using type =
		hamon::conditional_t<N <=  8, hamon::uint_fast8_t,
		hamon::conditional_t<N <= 16, hamon::uint_fast16_t,
		hamon::conditional_t<N <= 32, hamon::uint_fast32_t,
		hamon::conditional_t<N <= 64, hamon::uint_fast64_t,
		incomplete
	>>>>;
};

template <hamon::size_t N>
using make_uint_fast_n_t = typename make_uint_fast_n<N>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_UINT_FAST_N_HPP
