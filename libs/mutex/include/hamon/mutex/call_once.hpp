/**
 *	@file	call_once.hpp
 *
 *	@brief	call_once の定義
 */

#ifndef HAMON_MUTEX_CALL_ONCE_HPP
#define HAMON_MUTEX_CALL_ONCE_HPP

#include <mutex>

namespace hamon
{

using std::call_once;

#if 0	// TODO

// 32.6.7.2 Function call_once[thread.once.callonce]
template<class Callable, class... Args>
void call_once(once_flag& flag, Callable&& func, Args&&... args);

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_CALL_ONCE_HPP
