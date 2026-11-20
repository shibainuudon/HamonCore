/**
 *	@file	int_fast16_t.hpp
 *
 *	@brief	int_fast16_t の定義
 */

#ifndef HAMON_CSTDINT_INT_FAST16_T_HPP
#define HAMON_CSTDINT_INT_FAST16_T_HPP

#include <hamon/cstdint/detail/exact_width_type.hpp>

namespace hamon
{

using int_fast16_t = hamon::detail::exact_width_type_t<2,
	signed char,
	signed short,
	signed int,
	signed long,
	signed long long>;

}	// namespace hamon

#endif // HAMON_CSTDINT_INT_FAST16_T_HPP
