/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_SHARED_MUTEX_CONFIG_HPP
#define HAMON_SHARED_MUTEX_CONFIG_HPP

#include <hamon/chrono/config.hpp>
#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 14) && HAMON_HAS_INCLUDE(<shared_mutex>)
#  include <shared_mutex>
#endif

#if defined(HAMON_USE_STD_CHRONO)  && \
	defined(__cpp_lib_shared_timed_mutex) && (__cpp_lib_shared_timed_mutex >= 201402L) && \
	defined(__cpp_lib_shared_mutex) && (__cpp_lib_shared_mutex >= 201505L)

#  define HAMON_USE_STD_SHARED_MUTEX

#endif

#endif // HAMON_SHARED_MUTEX_CONFIG_HPP
