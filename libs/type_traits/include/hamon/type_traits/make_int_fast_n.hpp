/**
 *	@file	make_int_fast_n.hpp
 *
 *	@brief	make_int_fast_n
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_INT_FAST_N_HPP
#define HAMON_TYPE_TRAITS_MAKE_INT_FAST_N_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace hamon
{

template <std::size_t N>
struct make_int_fast_n
{
private:
	struct incomplete;
public:
	using type =
		std::conditional_t<N <=  8, std::int_fast8_t,
		std::conditional_t<N <= 16, std::int_fast16_t,
		std::conditional_t<N <= 32, std::int_fast32_t,
		std::conditional_t<N <= 64, std::int_fast64_t,
		incomplete
	>>>>;
};

template <std::size_t N>
using make_int_fast_n_t = typename make_int_fast_n<N>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_INT_FAST_N_HPP
