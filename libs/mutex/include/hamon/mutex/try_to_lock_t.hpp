/**
 *	@file	try_to_lock_t.hpp
 *
 *	@brief	try_to_lock_t の定義
 */

#ifndef HAMON_MUTEX_TRY_TO_LOCK_T_HPP
#define HAMON_MUTEX_TRY_TO_LOCK_T_HPP

#include <mutex>

namespace hamon
{

using std::try_to_lock_t;
using std::try_to_lock;

#if 0	// TODO

struct try_to_lock_t { explicit try_to_lock_t() = default; };

inline constexpr try_to_lock_t try_to_lock { };

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_TRY_TO_LOCK_T_HPP
