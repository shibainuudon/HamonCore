/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_MEMORY_RESOURCE_CONFIG_HPP
#define HAMON_MEMORY_RESOURCE_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17) && HAMON_HAS_INCLUDE(<memory_resource>)
#  include <memory_resource>
#  define HAMON_HAS_STD_MEMORY_RESOURCE
#endif

#if defined(HAMON_HAS_STD_MEMORY_RESOURCE) && \
	defined(__cpp_lib_memory_resource)       && (__cpp_lib_memory_resource       >= 201603L) &&	\
	defined(__cpp_lib_polymorphic_allocator) && (__cpp_lib_polymorphic_allocator >= 201902L) && \
	!defined(HAMON_APPLE_CLANG)	// AppleClangなら標準ライブラリを使わない
// aligned_allocにおいて、POSIXの実装ではアラインメントが2の累乗およびsizeof(void*)の倍数である必要があるが、
// AppleClangのpolymorphic_allocatorではこの対策がされていないようなので、
// std::polymorphic_allocatorは使わない(常に独自実装を使う)

#  define HAMON_USE_STD_MEMORY_RESOURCE

#endif

#endif // HAMON_MEMORY_RESOURCE_CONFIG_HPP
