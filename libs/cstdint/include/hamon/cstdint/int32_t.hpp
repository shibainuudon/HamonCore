/**
 *	@file	int32_t.hpp
 *
 *	@brief	int32_t の定義
 */

#ifndef HAMON_CSTDINT_INT32_T_HPP
#define HAMON_CSTDINT_INT32_T_HPP

#include <hamon/cstdint/detail/exact_width_type.hpp>

namespace hamon
{

using int32_t = hamon::detail::exact_width_type_t<4,
	signed char,
	signed short,
	signed int,
	signed long,
	signed long long>;

}	// namespace hamon

#endif // HAMON_CSTDINT_INT32_T_HPP
