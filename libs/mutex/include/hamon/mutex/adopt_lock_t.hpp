/**
 *	@file	adopt_lock_t.hpp
 *
 *	@brief	adopt_lock_t の定義
 */

#ifndef HAMON_MUTEX_ADOPT_LOCK_T_HPP
#define HAMON_MUTEX_ADOPT_LOCK_T_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 32.6.5.1 General[thread.lock.general]

struct adopt_lock_t { explicit adopt_lock_t() = default; };

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR adopt_lock_t adopt_lock{};

}	// namespace hamon

#endif // HAMON_MUTEX_ADOPT_LOCK_T_HPP
