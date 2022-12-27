/**
 *	@file	unwrap_reference.hpp
 *
 *	@brief	unwrap_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_UNWRAP_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_UNWRAP_REFERENCE_HPP

#include <hamon/functional/fwd/reference_wrapper_fwd.hpp>
#include <hamon/functional/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_unwrap_ref) && (__cpp_lib_unwrap_ref >= 201811L) && \
	defined(HAMON_USE_STD_REFERENCE_WRAPPER)

using std::unwrap_reference;

#else

template <typename T>
struct unwrap_reference { using type = T; };

template <typename T>
struct unwrap_reference<hamon::reference_wrapper<T>> { using type = T&; };

#endif

template <typename T>
using unwrap_reference_t = typename unwrap_reference<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_UNWRAP_REFERENCE_HPP
