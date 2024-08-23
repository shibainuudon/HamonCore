/**
 *	@file	weak_ptr_fwd.hpp
 *
 *	@brief	weak_ptr の前方宣言
 */

#ifndef HAMON_MEMORY_WEAK_PTR_FWD_HPP
#define HAMON_MEMORY_WEAK_PTR_FWD_HPP

#include <hamon/memory/config.hpp>

namespace hamon
{

#if defined(HAMON_USE_STD_SHARED_PTR)

using std::weak_ptr;

#else

template <typename T>
class weak_ptr;

#endif

}	// namespace hamon

#endif // HAMON_MEMORY_WEAK_PTR_FWD_HPP
