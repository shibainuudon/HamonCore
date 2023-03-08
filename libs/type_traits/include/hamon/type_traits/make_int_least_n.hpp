/**
 *	@file	make_int_least_n.hpp
 *
 *	@brief	make_int_least_n
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_INT_LEAST_N_HPP
#define HAMON_TYPE_TRAITS_MAKE_INT_LEAST_N_HPP

#include <hamon/type_traits/conditional.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint.hpp>

namespace hamon
{

template <hamon::size_t N>
struct make_int_least_n
{
private:
	struct incomplete;
public:
	using type =
		hamon::conditional_t<N <=  8, hamon::int_least8_t,
		hamon::conditional_t<N <= 16, hamon::int_least16_t,
		hamon::conditional_t<N <= 32, hamon::int_least32_t,
		hamon::conditional_t<N <= 64, hamon::int_least64_t,
		incomplete
	>>>>;
};

template <hamon::size_t N>
using make_int_least_n_t = typename make_int_least_n<N>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_INT_LEAST_N_HPP
