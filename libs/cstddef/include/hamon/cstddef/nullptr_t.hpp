/**
 *	@file	nullptr_t.hpp
 *
 *	@brief	nullptr_t の定義
 */

#ifndef HAMON_CSTDDEF_NULLPTR_T_HPP
#define HAMON_CSTDDEF_NULLPTR_T_HPP

namespace hamon
{

// 17.2.1 Header <cstddef> synopsis[cstddef.syn]
using nullptr_t = decltype(nullptr);

}	// namespace hamon

#endif // HAMON_CSTDDEF_NULLPTR_T_HPP
