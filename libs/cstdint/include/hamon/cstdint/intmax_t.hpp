/**
 *	@file	intmax_t.hpp
 *
 *	@brief	intmax_t の定義
 */

#ifndef HAMON_CSTDINT_INTMAX_T_HPP
#define HAMON_CSTDINT_INTMAX_T_HPP

#if !defined(__STDC_CONSTANT_MACROS)
#define __STDC_CONSTANT_MACROS
#endif

#if !defined(__STDC_LIMIT_MACROS)
#define __STDC_LIMIT_MACROS
#endif

#include <cstdint>

namespace hamon
{

using std::intmax_t;

}	// namespace hamon

#endif // HAMON_CSTDINT_INTMAX_T_HPP
