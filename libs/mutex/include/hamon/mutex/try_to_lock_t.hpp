/**
 *	@file	try_to_lock_t.hpp
 *
 *	@brief	try_to_lock_t の定義
 */

#ifndef HAMON_MUTEX_TRY_TO_LOCK_T_HPP
#define HAMON_MUTEX_TRY_TO_LOCK_T_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 32.6.5.1 General[thread.lock.general]

struct try_to_lock_t { explicit try_to_lock_t() = default; };

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR try_to_lock_t try_to_lock{};

}	// namespace hamon

#endif // HAMON_MUTEX_TRY_TO_LOCK_T_HPP
