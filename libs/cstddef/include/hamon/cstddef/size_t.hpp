/**
 *	@file	size_t.hpp
 *
 *	@brief	size_t の定義
 */

#ifndef HAMON_CSTDDEF_SIZE_T_HPP
#define HAMON_CSTDDEF_SIZE_T_HPP

namespace hamon
{

// [support.types.layout]/3
// [support.types.layout]/4
using size_t = decltype(sizeof(int));

}	// namespace hamon

#endif // HAMON_CSTDDEF_SIZE_T_HPP
