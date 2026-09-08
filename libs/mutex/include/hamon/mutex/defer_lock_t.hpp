/**
 *	@file	defer_lock_t.hpp
 *
 *	@brief	defer_lock_t の定義
 */

#ifndef HAMON_MUTEX_DEFER_LOCK_T_HPP
#define HAMON_MUTEX_DEFER_LOCK_T_HPP

#include <mutex>

namespace hamon
{

using std::defer_lock_t;
using std::defer_lock;

#if 0	// TODO

struct defer_lock_t { explicit defer_lock_t() = default; };

inline constexpr defer_lock_t  defer_lock { };

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_DEFER_LOCK_T_HPP
