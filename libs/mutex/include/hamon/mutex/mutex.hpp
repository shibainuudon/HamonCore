/**
 *	@file	mutex.hpp
 *
 *	@brief	mutex の定義
 */

#ifndef HAMON_MUTEX_MUTEX_HPP
#define HAMON_MUTEX_MUTEX_HPP

#include <mutex>

namespace hamon
{

using std::mutex;

#if 0	// TODO

// 32.6.4.2.2 Class mutex[thread.mutex.class]

class mutex
{
public:
	constexpr mutex() noexcept;
	~mutex();

	mutex(const mutex&) = delete;
	mutex& operator=(const mutex&) = delete;

	void lock();
	bool try_lock();
	void unlock();

	using native_handle_type = implementation-defined;          // see [thread.req.native]
	native_handle_type native_handle();                         // see [thread.req.native]
};

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_MUTEX_HPP
