/**
 *	@file	hardware_destructive_interference_size.hpp
 *
 *	@brief	hardware_destructive_interference_size の定義
 */

#ifndef HAMON_NEW_HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE_HPP
#define HAMON_NEW_HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <new>

namespace hamon
{

#if defined(__cpp_lib_hardware_interference_size) && (__cpp_lib_hardware_interference_size >= 201703L)

using std::hardware_destructive_interference_size;

#elif defined(__GCC_DESTRUCTIVE_SIZE)

HAMON_INLINE_VAR constexpr hamon::size_t hardware_destructive_interference_size = __GCC_DESTRUCTIVE_SIZE;

#else

HAMON_INLINE_VAR constexpr hamon::size_t hardware_destructive_interference_size = 64;

#endif

}	// namespace hamon

#endif // HAMON_NEW_HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE_HPP
