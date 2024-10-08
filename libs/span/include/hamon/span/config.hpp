﻿/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_SPAN_CONFIG_HPP
#define HAMON_SPAN_CONFIG_HPP

#include <hamon/config.hpp>
#include <hamon/ranges/config.hpp>
#include <hamon/concepts/config.hpp>

#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<span>)
#include <span>
#endif

#if defined(__cpp_lib_span) && (__cpp_lib_span >= 202311L) && \
	defined(__cpp_lib_span_initializer_list) && (__cpp_lib_span_initializer_list >= 202311L) && \
	defined(HAMON_USE_STD_CONCEPTS) && \
	defined(HAMON_USE_STD_RANGES)
#  define HAMON_USE_STD_SPAN
#endif

#endif // HAMON_SPAN_CONFIG_HPP
