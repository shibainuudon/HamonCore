/**
 *	@file	ptrdiff_t.hpp
 *
 *	@brief	ptrdiff_t の定義
 */

#ifndef HAMON_CSTDDEF_PTRDIFF_T_HPP
#define HAMON_CSTDDEF_PTRDIFF_T_HPP

namespace hamon
{

// [support.types.layout]/2
// [support.types.layout]/4
using ptrdiff_t = decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));

}	// namespace hamon

#endif // HAMON_CSTDDEF_PTRDIFF_T_HPP
