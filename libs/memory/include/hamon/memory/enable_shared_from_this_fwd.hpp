/**
 *	@file	enable_shared_from_this_fwd.hpp
 *
 *	@brief	enable_shared_from_this の前方宣言
 */

#ifndef HAMON_MEMORY_ENABLE_SHARED_FROM_THIS_FWD_HPP
#define HAMON_MEMORY_ENABLE_SHARED_FROM_THIS_FWD_HPP

#include <hamon/memory/config.hpp>

namespace hamon
{

#if defined(HAMON_USE_STD_SHARED_PTR)

using std::enable_shared_from_this;

#else

template <typename T>
class enable_shared_from_this;

#endif

}	// namespace hamon

#endif // HAMON_MEMORY_ENABLE_SHARED_FROM_THIS_FWD_HPP
