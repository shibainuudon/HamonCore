/**
 *	@file	unwrap_ref_decay.hpp
 *
 *	@brief	unwrap_ref_decay の定義
 */

#ifndef HAMON_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP
#define HAMON_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP

#include <hamon/type_traits/unwrap_reference.hpp>
#include <hamon/type_traits/decay.hpp>

namespace hamon
{

template <typename T>
struct unwrap_ref_decay
{
	using type = hamon::unwrap_reference_t<hamon::decay_t<T>>;
};

template <typename T>
using unwrap_ref_decay_t = typename unwrap_ref_decay<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP
