/**
 *	@file	atomic_is_always_lock_free.hpp
 *
 *	@brief	atomic_is_always_lock_free の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_IS_ALWAYS_LOCK_FREE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_IS_ALWAYS_LOCK_FREE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
struct atomic_is_always_lock_free
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__atomic_always_lock_free)
		__atomic_always_lock_free(sizeof(T), nullptr)
#else
		sizeof(T) <= 2 * sizeof(void*)
#endif
	>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_IS_ALWAYS_LOCK_FREE_HPP
