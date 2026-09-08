/**
 *	@file	recursive_mutex.hpp
 *
 *	@brief	recursive_mutex の定義
 */

#ifndef HAMON_MUTEX_RECURSIVE_MUTEX_HPP
#define HAMON_MUTEX_RECURSIVE_MUTEX_HPP

#include <mutex>

namespace hamon
{

using std::recursive_mutex;

#if 0	// TODO

// 32.6.4.2.3 Class recursive_mutex[thread.mutex.recursive]

class recursive_mutex
{
public:
	recursive_mutex();
	~recursive_mutex();

	recursive_mutex(const recursive_mutex&) = delete;
	recursive_mutex& operator=(const recursive_mutex&) = delete;

	void lock();
	bool try_lock() noexcept;
	void unlock();

	using native_handle_type = implementation-defined;          // see [thread.req.native]
	native_handle_type native_handle();                         // see [thread.req.native]
};

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_RECURSIVE_MUTEX_HPP
