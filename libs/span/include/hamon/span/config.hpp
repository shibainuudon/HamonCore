/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_SPAN_CONFIG_HPP
#define HAMON_SPAN_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<span>)
#include <span>
#endif

#if defined(__cpp_lib_span) && (__cpp_lib_span >= 202002) && \
	defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002) && \
	defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)
#  define HAMON_USE_STD_SPAN
#endif

#endif // HAMON_SPAN_CONFIG_HPP
