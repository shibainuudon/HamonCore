/**
 *	@file	jthread.hpp
 *
 *	@brief	jthread の定義
 */

#ifndef HAMON_THREAD_JTHREAD_HPP
#define HAMON_THREAD_JTHREAD_HPP

#include <hamon/thread/thread.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/stop_token.hpp>

namespace hamon
{

// 32.4.4 Class jthread[thread.jthread.class]

class jthread
{
public:
	// types
	using id = thread::id;

//	using native_handle_type = thread::native_handle_type;

	template <typename T>
	using name_hint = thread::name_hint<T>;

	using stack_size_hint = thread::stack_size_hint;

	// [thread.jthread.cons], constructors, move, and assignment
	jthread() noexcept;

	template <typename... Args>
	explicit jthread(Args&&... args);

	~jthread();

	jthread(jthread const&) = delete;
	jthread(jthread&&) noexcept;
	jthread& operator=(jthread const&) = delete;
	jthread& operator=(jthread&&) noexcept;

	// [thread.jthread.mem], members
	void swap(jthread&) noexcept;
	bool joinable() const noexcept;
	void join();
	void detach();
	id get_id() const noexcept;

//	native_handle_type native_handle();                 // see [thread.req.native]

	// [thread.jthread.stop], stop token handling
	hamon::stop_source get_stop_source() noexcept;
	hamon::stop_token get_stop_token() const noexcept;
	bool request_stop() noexcept;

	// [thread.jthread.special], specialized algorithms
	friend void swap(jthread& lhs, jthread& rhs) noexcept;

	// [thread.jthread.static], static members
	static unsigned int hardware_concurrency() noexcept;

private:
	hamon::stop_source ssource;
};

}	// namespace hamon

#endif // HAMON_THREAD_JTHREAD_HPP
