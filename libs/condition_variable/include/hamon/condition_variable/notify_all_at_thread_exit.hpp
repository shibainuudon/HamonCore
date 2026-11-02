/**
 *	@file	notify_all_at_thread_exit.hpp
 *
 *	@brief	notify_all_at_thread_exit の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_NOTIFY_ALL_AT_THREAD_EXIT_HPP
#define HAMON_CONDITION_VARIABLE_NOTIFY_ALL_AT_THREAD_EXIT_HPP

#if 0	// TODO
#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/unique_lock.hpp>

#include <condition_variable>

namespace hamon
{

using std::notify_all_at_thread_exit;

#if 0

// 32.7.3 Non-member functions[thread.condition.nonmember]

void notify_all_at_thread_exit(hamon::condition_variable& cond, hamon::unique_lock<hamon::mutex> lk)
{
  auto& tl_ptr = __thread_local_data();
  // If this thread was not created using std::thread then it will not have
  // previously allocated.
  if (tl_ptr.get() == nullptr) {
    tl_ptr.set_pointer(new __thread_struct);
  }
  __thread_local_data()->notify_all_at_thread_exit(&cond, lk.release());
}

#endif

}	// namespace hamon
#endif

#endif // HAMON_CONDITION_VARIABLE_NOTIFY_ALL_AT_THREAD_EXIT_HPP
