/**
 *	@file	thread_impl_win32.hpp
 *
 *	@brief
 */

#ifndef HAMON_THREAD_DETAIL_THREAD_IMPL_WIN32_HPP
#define HAMON_THREAD_DETAIL_THREAD_IMPL_WIN32_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>

#include <hamon/detail/windows.hpp>
#include <process.h>
#include <fibersapi.h>

namespace hamon
{
namespace detail
{

//
// Thread id
//
using thread_id = long;

inline bool thread_id_equal(thread_id lhs, thread_id rhs)
{
	return lhs == rhs;
}

inline bool thread_id_less(thread_id lhs, thread_id rhs)
{
	return lhs < rhs;
}

//
// Thread attribute
//
struct thread_attr_t
{
	hamon::size_t stacksize;
};

inline int thread_attr_init(thread_attr_t* attr)
{
	attr->stacksize = 0;
	return 0;
}

inline int thread_attr_setstacksize(thread_attr_t* attr, hamon::size_t stacksize)
{
	attr->stacksize = stacksize;
	return 0;
}

//
// Thread
//
using thread_t = void*;

inline bool thread_isnull(thread_t const* t)
{
	return *t == 0;
}

using thread_proc_return_type = unsigned int;
#define HAMON_THREAD_PROC_RETURN()	return 0u
#define HAMON_THREAD_PROC_CALLING_CONVENTION	__stdcall

inline int thread_create(thread_t* t, thread_attr_t* attr, unsigned int (__stdcall *func)(void*), void* arg)
{
	*t = reinterpret_cast<HANDLE>(::_beginthreadex(nullptr, static_cast<unsigned int>(attr->stacksize), func, arg, 0, nullptr));

	if (*t)
	{
		return 0;
	}

	return ::GetLastError();
}

inline int thread_setname(thread_t* t, char const* name)
{
	// TODO: utf16に変換する
	// 今はとりあえずwchar_tにコピーするだけ(ascii限定)
	wchar_t buf[256]{};
	char const* src = name;
	wchar_t* dst = buf;
	while (*src != 0)
	{
		*dst++ = static_cast<wchar_t>(*src++);
	}

	HRESULT hr = ::SetThreadDescription(*t, buf);
	if (FAILED(hr))
	{
		// TODO
	}
	return 0;
}

inline thread_id thread_get_current_id()
{
	return ::GetCurrentThreadId();
}

inline thread_id thread_get_id(thread_t const* t)
{
	return ::GetThreadId(*t);
}

inline int thread_join(thread_t* t)
{
	if (::WaitForSingleObjectEx(*t, INFINITE, FALSE) == WAIT_FAILED)
	{
		return ::GetLastError();
	}

	if (!::CloseHandle(*t))
	{
		return ::GetLastError();
	}

	return 0;
}

inline int thread_detach(thread_t* t)
{
	if (!::CloseHandle(*t))
	{
		return ::GetLastError();
	}

	return 0;
}

inline void thread_yield()
{
	::SwitchToThread();
}

inline void thread_sleep_for(hamon::uint64_t ns)
{
	hamon::uint64_t const mega = 1000 * 1000;
	hamon::uint64_t ms = (ns + mega - 1) / mega;	// round up to milliseconds

	hamon::uint64_t const max_sleep = INFINITE - 1;
	while (ms > max_sleep)
	{
		::Sleep(static_cast<DWORD>(max_sleep));
		ms -= max_sleep;
	}
	::Sleep(static_cast<DWORD>(ms));
}

inline unsigned int thread_hardware_concurrency()
{
	return static_cast<unsigned int>(::GetActiveProcessorCount(ALL_PROCESSOR_GROUPS));
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_THREAD_DETAIL_THREAD_IMPL_WIN32_HPP
