/**
 *	@file	uintmax_t.hpp
 *
 *	@brief	uintmax_t の定義
 */

#ifndef HAMON_CSTDINT_UINTMAX_T_HPP
#define HAMON_CSTDINT_UINTMAX_T_HPP

#if !defined(__STDC_CONSTANT_MACROS)
#define __STDC_CONSTANT_MACROS
#endif

#if !defined(__STDC_LIMIT_MACROS)
#define __STDC_LIMIT_MACROS
#endif

#include <cstdint>

namespace hamon
{

using std::uintmax_t;

}	// namespace hamon

#endif // HAMON_CSTDINT_UINTMAX_T_HPP
