/**
 *	@file	atomic_ref_base.hpp
 *
 *	@brief	atomic_ref_base の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_HPP

#include <hamon/atomic/detail/atomic_ref_base_floating_point.hpp>
#include <hamon/atomic/detail/atomic_ref_base_general.hpp>
#include <hamon/atomic/detail/atomic_ref_base_integral.hpp>
#include <hamon/atomic/detail/atomic_ref_base_pointer.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{
namespace detail
{

// [atomics.ref.int]
// [Note 1: The specialization atomic_ref<bool> uses the primary template ([atomics.ref.generic]). — end note]

template <typename T>
using atomic_ref_base =
	hamon::conditional_t<hamon::is_integral_v<T> && !hamon::is_same_v<bool, hamon::remove_cv_t<T>>,
		hamon::detail::atomic_ref_base_integral<T>,
	hamon::conditional_t<hamon::is_floating_point_v<T>,
		hamon::detail::atomic_ref_base_floating_point<T>,
	hamon::conditional_t<hamon::is_pointer_v<T>,
		hamon::detail::atomic_ref_base_pointer<T>,
		hamon::detail::atomic_ref_base_general<T>
	>>>;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_HPP
