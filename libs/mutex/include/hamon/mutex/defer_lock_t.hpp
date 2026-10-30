/**
 *	@file	defer_lock_t.hpp
 *
 *	@brief	defer_lock_t の定義
 */

#ifndef HAMON_MUTEX_DEFER_LOCK_T_HPP
#define HAMON_MUTEX_DEFER_LOCK_T_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 32.6.5.1 General[thread.lock.general]

struct defer_lock_t { explicit defer_lock_t() = default; };

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR defer_lock_t defer_lock{};

}	// namespace hamon

#endif // HAMON_MUTEX_DEFER_LOCK_T_HPP
