/**
 *	@file	atomic_is_lock_free.hpp
 *
 *	@brief	atomic_is_lock_free の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_IS_LOCK_FREE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_IS_LOCK_FREE_HPP

#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
bool atomic_is_lock_free()
{
#if HAMON_HAS_BUILTIN(__atomic_is_lock_free)
	return __atomic_is_lock_free(sizeof(T), nullptr);
#else
	return hamon::detail::atomic_is_always_lock_free<T>::value;
#endif
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_IS_LOCK_FREE_HPP
