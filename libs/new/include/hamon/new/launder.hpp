/**
 *	@file	launder.hpp
 *
 *	@brief	launder の定義
 */

#ifndef HAMON_NEW_LAUNDER_HPP
#define HAMON_NEW_LAUNDER_HPP

#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/config.hpp>
#include <new>

namespace hamon
{

#if defined(__cpp_lib_launder) && (__cpp_lib_launder >= 201606L)

using std::launder;

#elif HAMON_HAS_BUILTIN(__builtin_launder)

// 17.6.5 Pointer optimization barrier[ptr.launder]

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
T* launder(T* p) HAMON_NOEXCEPT
{
	static_assert(!hamon::is_function<T>::value && !hamon::is_void<T>::value, "[ptr.launder]/1");
	return __builtin_launder(p);
}

#else
#  define HAMON_NO_LAUNDER
#endif

#if !defined(HAMON_NO_LAUNDER)
#  define HAMON_HAS_LAUNDER
#endif

}	// namespace hamon

#endif // HAMON_NEW_LAUNDER_HPP
