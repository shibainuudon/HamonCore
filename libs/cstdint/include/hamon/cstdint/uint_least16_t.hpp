/**
 *	@file	uint_least16_t.hpp
 *
 *	@brief	uint_least16_t の定義
 */

#ifndef HAMON_CSTDINT_UINT_LEAST16_T_HPP
#define HAMON_CSTDINT_UINT_LEAST16_T_HPP

#include <hamon/cstdint/detail/exact_width_type.hpp>

namespace hamon
{

using uint_least16_t = hamon::detail::exact_width_type_t<2,
	unsigned char,
	unsigned short,
	unsigned int,
	unsigned long,
	unsigned long long>;

}	// namespace hamon

#endif // HAMON_CSTDINT_UINT_LEAST16_T_HPP
