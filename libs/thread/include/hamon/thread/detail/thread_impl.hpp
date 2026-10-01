/**
 *	@file	thread_impl.hpp
 *
 *	@brief
 */

#ifndef HAMON_THREAD_DETAIL_THREAD_IMPL_HPP
#define HAMON_THREAD_DETAIL_THREAD_IMPL_HPP

#if !defined(HAMON_THREAD_IMPL_HEADER)

#  if defined(__FreeBSD__) ||   \
	defined(__wasi__)    ||   \
	defined(__NetBSD__)  ||   \
	defined(__OpenBSD__) ||   \
	defined(__NuttX__)   ||   \
	defined(__linux__)   ||   \
	defined(__GNU__)     ||   \
	defined(__APPLE__)   ||   \
	defined(__MVS__)     ||   \
	defined(_AIX)        ||   \
	defined(__EMSCRIPTEN__)

// pthread
#    define HAMON_THREAD_IMPL_HEADER "hamon/thread/detail/thread_impl_pthread.hpp"

#  elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)

// win32
#    define HAMON_THREAD_IMPL_HEADER "hamon/thread/detail/thread_impl_win32.hpp"

#  else

#    error "Unknown platform"

#  endif

#endif

#include HAMON_THREAD_IMPL_HEADER

#endif // HAMON_THREAD_DETAIL_THREAD_IMPL_HPP
