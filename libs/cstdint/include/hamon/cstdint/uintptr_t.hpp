/**
 *	@file	uintptr_t.hpp
 *
 *	@brief	uintptr_t の定義
 */

#ifndef HAMON_CSTDINT_UINTPTR_T_HPP
#define HAMON_CSTDINT_UINTPTR_T_HPP

#include <hamon/cstdint/detail/exact_width_type.hpp>

namespace hamon
{

using uintptr_t = hamon::detail::exact_width_type_t<sizeof(void*),
	unsigned char,
	unsigned short,
	unsigned int,
	unsigned long,
	unsigned long long>;

}	// namespace hamon

#endif // HAMON_CSTDINT_UINTPTR_T_HPP
