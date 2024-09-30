/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_MEMORY_CONFIG_HPP
#define HAMON_MEMORY_CONFIG_HPP

#include <memory>

// P3037 constexpr std::shared_ptr が採用されるまで、
// unique_ptr, shared_ptr は自前実装を使う。

#if 0 && defined(__cpp_lib_constexpr_memory) && (__cpp_lib_constexpr_memory >= 202202L)

#define	HAMON_USE_STD_DEFAULT_DELETE
#define	HAMON_USE_STD_UNIQUE_PTR

#endif

#if defined(HAMON_USE_STD_UNIQUE_PTR) && \
	defined(__cpp_lib_transparent_operators) && (__cpp_lib_transparent_operators >= 201510L) &&	\
	defined(__cpp_lib_enable_shared_from_this) && (__cpp_lib_enable_shared_from_this >= 201603L) &&	\
	defined(__cpp_lib_shared_ptr_weak_type) && (__cpp_lib_shared_ptr_weak_type >= 201606L) &&	\
	defined(__cpp_lib_shared_ptr_arrays) && (__cpp_lib_shared_ptr_arrays >= 201611L) &&	\
	defined(__cpp_lib_smart_ptr_owner_equality) && (__cpp_lib_smart_ptr_owner_equality >= 202306L)

#define	HAMON_USE_STD_SHARED_PTR

#endif

#endif // HAMON_MEMORY_CONFIG_HPP
