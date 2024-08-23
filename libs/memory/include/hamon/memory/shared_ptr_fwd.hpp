/**
 *	@file	shared_ptr_fwd.hpp
 *
 *	@brief	shared_ptr の前方宣言
 */

#ifndef HAMON_MEMORY_SHARED_PTR_FWD_HPP
#define HAMON_MEMORY_SHARED_PTR_FWD_HPP

#include <hamon/memory/config.hpp>

namespace hamon
{

#if defined(HAMON_USE_STD_SHARED_PTR)

using std::shared_ptr;

#else

template <typename T>
class shared_ptr;

#endif

}	// namespace hamon

#endif // HAMON_MEMORY_SHARED_PTR_FWD_HPP
