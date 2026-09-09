/**
 *	@file	notify_all_at_thread_exit.hpp
 *
 *	@brief	notify_all_at_thread_exit の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_NOTIFY_ALL_AT_THREAD_EXIT_HPP
#define HAMON_CONDITION_VARIABLE_NOTIFY_ALL_AT_THREAD_EXIT_HPP

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/unique_lock.hpp>

namespace hamon
{

// 32.7.3 Non-member functions[thread.condition.nonmember]

void notify_all_at_thread_exit(hamon::condition_variable& cond, hamon::unique_lock<hamon::mutex> lk);

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_NOTIFY_ALL_AT_THREAD_EXIT_HPP
