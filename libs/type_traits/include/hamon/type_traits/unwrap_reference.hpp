/**
 *	@file	unwrap_reference.hpp
 *
 *	@brief	unwrap_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_UNWRAP_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_UNWRAP_REFERENCE_HPP

#include <hamon/functional/fwd/reference_wrapper_fwd.hpp>

namespace hamon
{

template <typename T>
struct unwrap_reference { using type = T; };

template <typename T>
struct unwrap_reference<hamon::reference_wrapper<T>> { using type = T&; };

template <typename T>
using unwrap_reference_t = typename unwrap_reference<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_UNWRAP_REFERENCE_HPP
