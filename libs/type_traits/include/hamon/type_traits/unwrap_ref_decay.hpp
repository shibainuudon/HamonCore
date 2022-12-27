/**
 *	@file	unwrap_ref_decay.hpp
 *
 *	@brief	unwrap_ref_decay の定義
 */

#ifndef HAMON_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP
#define HAMON_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP

#include <hamon/type_traits/unwrap_reference.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/functional/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_unwrap_ref) && (__cpp_lib_unwrap_ref >= 201811L) && \
	defined(HAMON_USE_STD_REFERENCE_WRAPPER)

using std::unwrap_ref_decay;

#else

template <typename T>
struct unwrap_ref_decay
{
	using type = hamon::unwrap_reference_t<hamon::decay_t<T>>;
};

#endif

template <typename T>
using unwrap_ref_decay_t = typename unwrap_ref_decay<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP
