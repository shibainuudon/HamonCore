/**
 *	@file	adopt_lock_t.hpp
 *
 *	@brief	adopt_lock_t の定義
 */

#ifndef HAMON_MUTEX_ADOPT_LOCK_T_HPP
#define HAMON_MUTEX_ADOPT_LOCK_T_HPP

#include <mutex>

namespace hamon
{

using std::adopt_lock_t;
using std::adopt_lock;

#if 0	// TODO

struct adopt_lock_t { explicit adopt_lock_t() = default; };

inline constexpr adopt_lock_t  adopt_lock { };

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_ADOPT_LOCK_T_HPP
